/**
\file       rgb2hsl_neon.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "rgb_to_hsl_int.hpp"

#ifdef U3_CPU_ARM

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
U3_SET_TARGET_CPU (+simd)
void
rgb24_to_hsl_neon (::libs::optim::io::MCallInfo& info)
{
  RGB2HSL_PREFIX (4);

  uint8x8x3_t       vrgb24;
  const float32x4_t const_0        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  const float32x4_t const_1        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1);
  const float32x4_t const_2        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d2);
  const float32x4_t const_255      = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d255);
  const float32x4_t const_1_to_2   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d2);
  const float32x4_t const_1_to_3   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d3);
  const float32x4_t const_1_to_6   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d6);
  const float32x4_t const_1_to_255 = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d255);
  const float32x4_t const_2_to_3   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d2_to_d3);
  float32x4_t       h8;
  float32x4_t       s8;
  float32x4_t       l8;
  float32x4_t       temp_r;
  float32x4_t       temp_g;
  float32x4_t       temp_b;
  float32x4_t       delta_r;
  float32x4_t       delta_g;
  float32x4_t       delta_b;
  float32x4_t       max;
  float32x4_t       max_min;

  float32x4_t delta_max;
  float32x4_t inv_delta_max;
  float32x4_t old_delta_max;
  float32x4_t ymm0;
  uint32x4_t  iymm0;
  float32x4_t ymm1;
  uint32x4_t  iymm1;
  float32x4_t ymm2;
  uint32x4_t  iymm2;
  float32x4_t ymm3;
  uint32x4_t  iymm3;
  float32x4_t ymm4;
  float32x4_t ymm5;
  float32x4_t ymm6;
  float32x4_t ymm7;
  uint32x4_t  iymm7;

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      vrgb24 = vld3_u8 (::libs::helpers::casts::reinterpret_cast_helper< const std::uint8_t* > (rgb24));

      uint16x8_t  r16;
      uint16x8_t  g16;
      uint16x8_t  b16;
      uint32x4_t  r32_low;
      uint32x4_t  g32_low;
      uint32x4_t  b32_low;
      float32x4_t fr32_low;
      float32x4_t fg32_low;
      float32x4_t fb32_low;

      r16 = vsubl_u8 (vrgb24.val[2], vreinterpret_u8_f32 (vget_low_f32 (const_0)));
      g16 = vsubl_u8 (vrgb24.val[1], vreinterpret_u8_f32 (vget_low_f32 (const_0)));
      b16 = vsubl_u8 (vrgb24.val[0], vreinterpret_u8_f32 (vget_low_f32 (const_0)));

      r32_low = vsubl_u16 (vget_low_u16 (r16), vget_low_u16 (vreinterpretq_u16_f32 (const_0)));
      g32_low = vsubl_u16 (vget_low_u16 (g16), vget_low_u16 (vreinterpretq_u16_f32 (const_0)));
      b32_low = vsubl_u16 (vget_low_u16 (b16), vget_low_u16 (vreinterpretq_u16_f32 (const_0)));

      // convert RGB double word from 8 pixel to float;
      fr32_low = vcvtq_f32_u32 (r32_low);
      fg32_low = vcvtq_f32_u32 (g32_low);
      fb32_low = vcvtq_f32_u32 (b32_low);

      // normalization from 0..255 to 0.0F..1.0F;
      ymm5 = vmulq_f32 (fr32_low, const_1_to_255);
      ymm6 = vmulq_f32 (fg32_low, const_1_to_255);
      ymm7 = vmulq_f32 (fb32_low, const_1_to_255);

      temp_r = ymm5;
      temp_g = ymm6;
      temp_b = ymm7;

      rgb24 += 3;

      // float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
      ymm4 = vminq_f32 (ymm6, ymm5);
      ymm4 = vminq_f32 (ymm7, ymm4);

      // float max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
      ymm3 = vmaxq_f32 (ymm6, ymm5);
      ymm3 = vmaxq_f32 (ymm7, ymm3);
      max  = ymm3;

      // max_min = max + var_Min;
      max_min = vaddq_f32 (ymm4, ymm3);

      // L = ( max + var_Min ) / 2.0F;
      l8 = vmulq_f32 (const_1_to_2, max_min);

      // float delta_max = max - var_Min; Delta RGB value
      old_delta_max = vsubq_f32 (ymm3, ymm4);

      // if ( delta_max == 0 )              This is a gray, no chroma...
      //{
      //   H = 0.0F;                   HSL results = 0 ? 1
      //   S = 0.0F;
      // }
      // else                        Chromatic data...
      iymm0 = vceqq_f32 (const_0, old_delta_max);
      ymm1  = vreinterpretq_f32_u32 (vandq_u32 (iymm0, vreinterpretq_u32_f32 (const_1)));

      // add 1.0F for distance from 0.0;
      delta_max = vaddq_f32 (old_delta_max, ymm1);

      // if ( L < 0.5f ) S = delta_max / ( max + var_Min );
      // else            S = delta_max / ( 2.0F - ( max + var_Min) );
      ymm3 = vrecpeq_f32 (max_min);
      ymm3 = vmulq_f32 (vrecpsq_f32 (max_min, ymm3), ymm3);
      ymm3 = vmulq_f32 (vrecpsq_f32 (max_min, ymm3), ymm3);
      ymm3 = vmulq_f32 (delta_max, ymm3);   // RES S
      ymm4 = vsubq_f32 (const_2, max_min);
      ymm5 = vrecpeq_f32 (ymm4);
      ymm5 = vmulq_f32 (vrecpsq_f32 (ymm4, ymm5), ymm5);
      ymm5 = vmulq_f32 (vrecpsq_f32 (ymm4, ymm5), ymm5);
      ymm5 = vmulq_f32 (delta_max, ymm5);   // RES S

#  if 0
        {
          float deb[ 32 ];
          vst1q_f32( deb, l8 );
          ULOGI( "l8= %f, %f, %f, %f", deb[ 0 ], deb[ 1 ], deb[ 2 ], deb[ 3 ] );
        }
#  endif

      iymm0 = vcltq_f32 (l8, const_1_to_2);
      ymm3  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (ymm3), iymm0));
      iymm1 = vceqq_f32 (const_1_to_2, const_1_to_2);
      iymm1 = veorq_u32 (iymm1, iymm0);
      ymm5  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (ymm5), iymm1));
      ymm5  = vreinterpretq_f32_u32 (vorrq_u32 (vreinterpretq_u32_f32 (ymm5), vreinterpretq_u32_f32 (ymm3)));
      s8    = ymm5;
      // s8     = vdupq_n_f32(1.0F );//debug

      // inverse delta_max;
      inv_delta_max = vrecpeq_f32 (delta_max);
      inv_delta_max = vmulq_f32 (vrecpsq_f32 (delta_max, inv_delta_max), inv_delta_max);
      inv_delta_max = vmulq_f32 (vrecpsq_f32 (delta_max, inv_delta_max), inv_delta_max);

      ymm0 = max;
      ymm2 = inv_delta_max;
      ymm4 = temp_r;

      // float delta_r = ( ( ( max - var_R ) / 6.0F ) + ( delta_max / 2.0F ) ) / delta_max;
      //  1.( max - var_R );
      ymm3 = vsubq_f32 (ymm0, ymm4);
      // 2.( max - var_R ) / 6.0F;
      ymm3 = vmulq_f32 (ymm3, const_1_to_6);
      // 3.( delta_max / 2.0F )
      ymm5 = vmulq_f32 (const_1_to_2, delta_max);
      // 4.( ( max - var_R ) / 6.0F ) + ( delta_max / 2.0F ) )
      ymm3 = vaddq_f32 (ymm3, ymm5);
      // 5.end
      ymm3    = vmulq_f32 (ymm3, ymm2);
      delta_r = ymm3;

      // float delta_g = ( ( ( max - var_G ) / 6.0F ) + ( delta_max / 2.0F ) ) / delta_max;
      ymm4 = temp_g;
      // 1.( max - var_G )
      ymm3 = vsubq_f32 (ymm0, ymm4);
      // 2.( max - var_G ) / 6.0F
      ymm3 = vmulq_f32 (ymm3, const_1_to_6);
      // 3.( delta_max / 2.0F )
      ymm5 = vmulq_f32 (const_1_to_2, delta_max);
      // 4.( ( max - var_G ) / 6.0F ) + ( delta_max / 2.0F ) )
      ymm3 = vaddq_f32 (ymm3, ymm5);
      // 5.end
      ymm3    = vmulq_f32 (ymm3, ymm2);
      delta_g = ymm3;

      // float delta_b = ( ( ( max - var_B ) / 6.0F ) + ( delta_max / 2.0F ) ) / delta_max;
      ymm4 = temp_b;
      // 1.( max - var_B )
      ymm3 = vsubq_f32 (ymm0, ymm4);
      // 2.( max - var_B ) / 6.0F
      ymm3 = vmulq_f32 (ymm3, const_1_to_6);
      // 3.( delta_max / 2.0F )
      ymm5 = vmulq_f32 (const_1_to_2, delta_max);
      // 4.( ( max - var_B ) / 6.0F ) + ( delta_max / 2.0F ) )
      ymm3 = vaddq_f32 (ymm3, ymm5);
      // 5.end
      ymm3    = vmulq_f32 (ymm3, ymm2);
      delta_b = ymm3;

      // if      ( var_R == max ) H = delta_b - delta_g;
      // else if ( var_G == max ) H = ( 1.0F / 3.0F ) + delta_r - delta_b;
      // else if ( var_B == max ) H = ( 2.0F / 3.0F ) + delta_g - delta_r;
      // ymm1 = const_2_to_3;//fuke
      ymm3 = delta_g;
      ymm2 = delta_r;
      // else if ( var_B == max ) H = ( 2.0F / 3.0F ) + delta_g - delta_r;
      ymm7 = vaddq_f32 (const_2_to_3, ymm3);
      ymm7 = vsubq_f32 (ymm7, ymm2);
      // else if ( var_G == max ) H = ( 1.0F / 3.0F ) + delta_r - delta_b;
      // ymm1 = const_1_to_3;//fuke
      ymm4  = delta_b;
      ymm6  = vaddq_f32 (const_1_to_3, ymm2);
      ymm6  = vsubq_f32 (ymm6, ymm4);   // RES H
      ymm0  = max;
      ymm1  = temp_g;
      ymm2  = ymm1;
      iymm1 = vceqq_f32 (ymm1, ymm0);
      ymm6  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (ymm6), iymm1));
      iymm2 = vceqq_f32 (ymm2, ymm0);
      iymm2 = vmvnq_u32 (iymm2);
      iymm7 = vandq_u32 (vreinterpretq_u32_f32 (ymm7), iymm2);
      ymm7  = vreinterpretq_f32_u32 (vorrq_u32 (iymm7, vreinterpretq_u32_f32 (ymm6)));
      // if      ( var_R == max ) H = delta_b - delta_g;
      ymm6  = delta_b;
      ymm1  = delta_g;
      ymm6  = vsubq_f32 (ymm6, ymm1);
      ymm1  = temp_r;
      ymm2  = ymm1;
      iymm1 = vceqq_f32 (ymm1, ymm0);
      iymm2 = vceqq_f32 (ymm2, ymm0);

      iymm2 = vmvnq_u32 (iymm2);
      ymm6  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (ymm6), iymm1));
      ymm7  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (ymm7), iymm2));
      ymm7  = vreinterpretq_f32_u32 (vorrq_u32 (vreinterpretq_u32_f32 (ymm7), vreinterpretq_u32_f32 (ymm6)));

      // if ( H < 0 ) H += 1.0F;
      ymm3  = ymm7;
      iymm3 = vcltq_f32 (ymm3, const_0);
      ymm2  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (const_1), iymm3));
      ymm7  = vaddq_f32 (ymm7, ymm2);
      // if ( H > 1 ) H -= 1.0F;
      ymm3  = ymm7;
      iymm2 = vcltq_f32 (const_1, ymm3);
      ymm1  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (const_1), iymm2));
      ymm7  = vsubq_f32 (ymm7, ymm1);
      h8    = ymm7;
      // h8 = vdupq_n_f32(0.5f );//debug

      // if ( delta_max == 0 )      This is a gray, no chroma...
      //{
      //   H = 0.0F;                 HSL results = 0 ? 1
      //   S = 0.0F;
      // }
      // else                        Chromatic data...
      iymm0 = vceqq_f32 (old_delta_max, const_0);
      iymm0 = vmvnq_u32 (iymm0);

      h8 = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (h8), iymm0));
      s8 = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (s8), iymm0));

      // converting from float HSL to word HSL and saved to bufs
      // h8 = vdupq_n_f32(0.33f );//debug
      h8              = vmulq_f32 (h8, const_255);
      int32x4_t h_i32 = vcvtq_s32_f32 (h8);
      int16x4_t h_i16 = vreinterpret_s16_u16 (vqmovun_s32 (h_i32));
      vst1_s16 (h, h_i16);
      h += ppc;

      // s8 = vdupq_n_f32(0.5f );//debug
      s8              = vmulq_f32 (s8, const_255);
      int32x4_t s_i32 = vcvtq_s32_f32 (s8);
      int16x4_t s_i16 = vreinterpret_s16_u16 (vqmovun_s32 (s_i32));
      vst1_s16 (s, s_i16);
      s += ppc;

      l8              = vmulq_f32 (l8, const_255);
      int32x4_t l_i32 = vcvtq_s32_f32 (l8);
      int16x4_t l_i16 = vreinterpret_s16_u16 (vqmovun_s32 (l_i32));
      vst1_s16 (l, l_i16);
      l += ppc;
    }

    rgb24 = ::libs::helpers::mem::move_cptr (rgb24, leak_rgb);
    h     = ::libs::helpers::mem::move_ptr (h, leak_hsl);
    s     = ::libs::helpers::mem::move_ptr (s, leak_hsl);
    l     = ::libs::helpers::mem::move_ptr (l, leak_hsl);
  }
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
