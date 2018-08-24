//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       rgb2hsl_neon.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "rgb_to_hsl_int.hpp"

#if defined(UUU_CPU_ARM)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

UUU_SET_TARGET_CPU (neon)
void
rgb24_to_hsl_neon (::libs::optim::MCallInfo& _info)
{
  RGB2HSL_PREFIX (4);

  uint8x8x3_t       _vrgb24;
  const float32x4_t _const_0        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  const float32x4_t _const_1        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1);
  const float32x4_t _const_2        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d2);
  const float32x4_t _const_3        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d3);
  const float32x4_t _const_6        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d6);
  const float32x4_t _const_255      = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d255);
  const float32x4_t _const_1_to_2   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d2);
  const float32x4_t _const_1_to_3   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d3);
  const float32x4_t _const_1_to_6   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d6);
  const float32x4_t _const_1_to_255 = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d255);
  const float32x4_t _const_2_to_3   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d2_to_d3);
  float32x4_t       _h8;
  float32x4_t       _s8;
  float32x4_t       _l8;
  float32x4_t       _temp_r;
  float32x4_t       _temp_g;
  float32x4_t       _temp_b;
  float32x4_t       _delta_r;
  float32x4_t       _delta_g;
  float32x4_t       _delta_b;
  float32x4_t       _max;
  float32x4_t       _max_min;

  float32x4_t _delta_max;
  float32x4_t _inv_delta_max;
  float32x4_t _old_delta_max;
  float32x4_t _ymm0;
  uint32x4_t  _iymm0;
  float32x4_t _ymm1;
  uint32x4_t  _iymm1;
  float32x4_t _ymm2;
  uint32x4_t  _iymm2;
  float32x4_t _ymm3;
  uint32x4_t  _iymm3;
  float32x4_t _ymm4;
  uint32x4_t  _iymm4;
  float32x4_t _ymm5;
  uint32x4_t  _iymm5;
  float32x4_t _ymm6;
  uint32x4_t  _iymm6;
  float32x4_t _ymm7;
  uint32x4_t  _iymm7;

  //unsigned char   _deb1[ 32 ];
  //short           _sdeb1[ 32 ];
  //int             _ideb1[ 32 ];
  //float           _fdeb1[ 32 ];

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
#if 0
        for( std::size_t _indx = 0; _indx < 4; ++_indx )
        {
          const_cast<unsigned char*>( _rgb24 )[ 3 * _indx + 0 ] = UUU_ICAST_UCHAR( 0 );
          const_cast<unsigned char*>( _rgb24 )[ 3 * _indx + 1 ] = UUU_ICAST_UCHAR( 255 );
          const_cast<unsigned char*>( _rgb24 )[ 3 * _indx + 2 ] = UUU_ICAST_UCHAR( 0 );
        }
#endif

          _vrgb24 = vld3_u8 (UUU_MEM_CAST<const unsigned char*> (_rgb24));

          uint16x8_t  _r16;
          uint16x8_t  _g16;
          uint16x8_t  _b16;
          uint32x4_t  _r32_low;
          uint32x4_t  _g32_low;
          uint32x4_t  _b32_low;
          float32x4_t _fr32_low;
          float32x4_t _fg32_low;
          float32x4_t _fb32_low;

          _r16 = vsubl_u8 (_vrgb24.val[2], vreinterpret_u8_f32 (vget_low_f32 (_const_0)));
          _g16 = vsubl_u8 (_vrgb24.val[1], vreinterpret_u8_f32 (vget_low_f32 (_const_0)));
          _b16 = vsubl_u8 (_vrgb24.val[0], vreinterpret_u8_f32 (vget_low_f32 (_const_0)));

          _r32_low = vsubl_u16 (vget_low_u16 (_r16), vget_low_u16 (vreinterpretq_u16_f32 (_const_0)));
          _g32_low = vsubl_u16 (vget_low_u16 (_g16), vget_low_u16 (vreinterpretq_u16_f32 (_const_0)));
          _b32_low = vsubl_u16 (vget_low_u16 (_b16), vget_low_u16 (vreinterpretq_u16_f32 (_const_0)));

          //convert RGB double word from 8 pixel to float;
          _fr32_low = vcvtq_f32_u32 (_r32_low);
          _fg32_low = vcvtq_f32_u32 (_g32_low);
          _fb32_low = vcvtq_f32_u32 (_b32_low);

          //normalization from 0..255 to 0.0f..1.0f;
          _ymm5 = vmulq_f32 (_fr32_low, _const_1_to_255);
          _ymm6 = vmulq_f32 (_fg32_low, _const_1_to_255);
          _ymm7 = vmulq_f32 (_fb32_low, _const_1_to_255);

          _temp_r = _ymm5;
          _temp_g = _ymm6;
          _temp_b = _ymm7;

          _rgb24 += 3;

          //float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
          _ymm4 = vminq_f32 (_ymm6, _ymm5);
          _ymm4 = vminq_f32 (_ymm7, _ymm4);

          //float _max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
          _ymm3 = vmaxq_f32 (_ymm6, _ymm5);
          _ymm3 = vmaxq_f32 (_ymm7, _ymm3);
          _max  = _ymm3;

          //_max_min = _max + var_Min;
          _max_min = vaddq_f32 (_ymm4, _ymm3);

          //L = ( _max + var_Min ) / 2.0f;
          _l8 = vmulq_f32 (_const_1_to_2, _max_min);

          //float _delta_max = _max - var_Min; Delta RGB value
          _old_delta_max = vsubq_f32 (_ymm3, _ymm4);

          //if ( _delta_max == 0 )              This is a gray, no chroma...
          //{
          //  H = 0.0f;                   HSL results = 0 ? 1
          //  S = 0.0f;
          //}
          //else                        Chromatic data...
          _iymm0 = vceqq_f32 (_const_0, _old_delta_max);
          _ymm1  = vreinterpretq_f32_u32 (vandq_u32 (_iymm0, vreinterpretq_u32_f32 (_const_1)));

          //add 1.0f for distance from 0.0;
          _delta_max = vaddq_f32 (_old_delta_max, _ymm1);

          //if ( L < 0.5f ) S = _delta_max / ( _max + var_Min );
          //else            S = _delta_max / ( 2.0f - ( _max + var_Min) );
          _ymm3 = vrecpeq_f32 (_max_min);
          _ymm3 = vmulq_f32 (vrecpsq_f32 (_max_min, _ymm3), _ymm3);
          _ymm3 = vmulq_f32 (vrecpsq_f32 (_max_min, _ymm3), _ymm3);
          _ymm3 = vmulq_f32 (_delta_max, _ymm3);      //RES S
          _ymm4 = vsubq_f32 (_const_2, _max_min);
          _ymm5 = vrecpeq_f32 (_ymm4);
          _ymm5 = vmulq_f32 (vrecpsq_f32 (_ymm4, _ymm5), _ymm5);
          _ymm5 = vmulq_f32 (vrecpsq_f32 (_ymm4, _ymm5), _ymm5);
          _ymm5 = vmulq_f32 (_delta_max, _ymm5);      //RES S
#if 0
        {
          float _deb[ 32 ];
          vst1q_f32( _deb, _l8 );
          ULOGI( "_l8= %f, %f, %f, %f", _deb[ 0 ], _deb[ 1 ], _deb[ 2 ], _deb[ 3 ] );
        }
#endif

          _iymm0 = vcltq_f32 (_l8, _const_1_to_2);
          _ymm3  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_ymm3), _iymm0));
          _iymm1 = vceqq_f32 (_const_1_to_2, _const_1_to_2);
          _iymm1 = veorq_u32 (_iymm1, _iymm0);
          _ymm5  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_ymm5), _iymm1));
          _ymm5  = vreinterpretq_f32_u32 (vorrq_u32 (vreinterpretq_u32_f32 (_ymm5), vreinterpretq_u32_f32 (_ymm3)));
          _s8    = _ymm5;
          //_s8     = vdupq_n_f32(1.0f );//debug

          //inverse _delta_max;
          _inv_delta_max = vrecpeq_f32 (_delta_max);
          _inv_delta_max = vmulq_f32 (vrecpsq_f32 (_delta_max, _inv_delta_max), _inv_delta_max);
          _inv_delta_max = vmulq_f32 (vrecpsq_f32 (_delta_max, _inv_delta_max), _inv_delta_max);

          _ymm0 = _max;
          _ymm2 = _inv_delta_max;
          _ymm4 = _temp_r;

          //float _delta_r = ( ( ( _max - var_R ) / 6.0f ) + ( _delta_max / 2.0f ) ) / _delta_max;
          // 1.( _max - var_R );
          _ymm3 = vsubq_f32 (_ymm0, _ymm4);
          // 2.( _max - var_R ) / 6.0f;
          _ymm3 = vmulq_f32 (_ymm3, _const_1_to_6);
          // 3.( _delta_max / 2.0f )
          _ymm5 = vmulq_f32 (_const_1_to_2, _delta_max);
          // 4.( ( _max - var_R ) / 6.0f ) + ( _delta_max / 2.0f ) )
          _ymm3 = vaddq_f32 (_ymm3, _ymm5);
          // 5.end
          _ymm3    = vmulq_f32 (_ymm3, _ymm2);
          _delta_r = _ymm3;

          //float _delta_g = ( ( ( _max - var_G ) / 6.0f ) + ( _delta_max / 2.0f ) ) / _delta_max;
          _ymm4 = _temp_g;
          // 1.( _max - var_G )
          _ymm3 = vsubq_f32 (_ymm0, _ymm4);
          // 2.( _max - var_G ) / 6.0f
          _ymm3 = vmulq_f32 (_ymm3, _const_1_to_6);
          // 3.( _delta_max / 2.0f )
          _ymm5 = vmulq_f32 (_const_1_to_2, _delta_max);
          // 4.( ( _max - var_G ) / 6.0f ) + ( _delta_max / 2.0f ) )
          _ymm3 = vaddq_f32 (_ymm3, _ymm5);
          // 5.end
          _ymm3    = vmulq_f32 (_ymm3, _ymm2);
          _delta_g = _ymm3;

          //float _delta_b = ( ( ( _max - var_B ) / 6.0f ) + ( _delta_max / 2.0f ) ) / _delta_max;
          _ymm4 = _temp_b;
          // 1.( _max - var_B )
          _ymm3 = vsubq_f32 (_ymm0, _ymm4);
          // 2.( _max - var_B ) / 6.0f
          _ymm3 = vmulq_f32 (_ymm3, _const_1_to_6);
          // 3.( _delta_max / 2.0f )
          _ymm5 = vmulq_f32 (_const_1_to_2, _delta_max);
          // 4.( ( _max - var_B ) / 6.0f ) + ( _delta_max / 2.0f ) )
          _ymm3 = vaddq_f32 (_ymm3, _ymm5);
          // 5.end
          _ymm3    = vmulq_f32 (_ymm3, _ymm2);
          _delta_b = _ymm3;

          //if      ( var_R == _max ) H = _delta_b - _delta_g;
          //else if ( var_G == _max ) H = ( 1.0f / 3.0f ) + _delta_r - _delta_b;
          //else if ( var_B == _max ) H = ( 2.0f / 3.0f ) + _delta_g - _delta_r;
          //_ymm1 = _const_2_to_3;//fuke
          _ymm3 = _delta_g;
          _ymm2 = _delta_r;
          //else if ( var_B == _max ) H = ( 2.0f / 3.0f ) + _delta_g - _delta_r;
          _ymm7 = vaddq_f32 (_const_2_to_3, _ymm3);
          _ymm7 = vsubq_f32 (_ymm7, _ymm2);
          //else if ( var_G == _max ) H = ( 1.0f / 3.0f ) + _delta_r - _delta_b;
          //_ymm1 = _const_1_to_3;//fuke
          _ymm4  = _delta_b;
          _ymm6  = vaddq_f32 (_const_1_to_3, _ymm2);
          _ymm6  = vsubq_f32 (_ymm6, _ymm4);      //RES H
          _ymm0  = _max;
          _ymm1  = _temp_g;
          _ymm2  = _ymm1;
          _iymm1 = vceqq_f32 (_ymm1, _ymm0);
          _ymm6  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_ymm6), _iymm1));
          _iymm2 = vceqq_f32 (_ymm2, _ymm0);
          _iymm2 = vmvnq_u32 (_iymm2);
          _iymm7 = vandq_u32 (vreinterpretq_u32_f32 (_ymm7), _iymm2);
          _ymm7  = vreinterpretq_f32_u32 (vorrq_u32 (_iymm7, vreinterpretq_u32_f32 (_ymm6)));
          //if      ( var_R == _max ) H = _delta_b - _delta_g;
          _ymm6  = _delta_b;
          _ymm1  = _delta_g;
          _ymm6  = vsubq_f32 (_ymm6, _ymm1);
          _ymm1  = _temp_r;
          _ymm2  = _ymm1;
          _iymm1 = vceqq_f32 (_ymm1, _ymm0);
          _iymm2 = vceqq_f32 (_ymm2, _ymm0);

          _iymm2 = vmvnq_u32 (_iymm2);
          _ymm6  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_ymm6), _iymm1));
          _ymm7  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_ymm7), _iymm2));
          _ymm7  = vreinterpretq_f32_u32 (vorrq_u32 (vreinterpretq_u32_f32 (_ymm7), vreinterpretq_u32_f32 (_ymm6)));

          //if ( H < 0 ) H += 1.0f;
          _ymm3  = _ymm7;
          _iymm3 = vcltq_f32 (_ymm3, _const_0);
          _ymm2  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_const_1), _iymm3));
          _ymm7  = vaddq_f32 (_ymm7, _ymm2);
          //if ( H > 1 ) H -= 1.0f;
          _ymm3  = _ymm7;
          _iymm2 = vcltq_f32 (_const_1, _ymm3);
          _ymm1  = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_const_1), _iymm2));
          _ymm7  = vsubq_f32 (_ymm7, _ymm1);
          _h8    = _ymm7;
          //_h8 = vdupq_n_f32(0.5f );//debug

          //if ( _delta_max == 0 )      This is a gray, no chroma...
          //{
          //  H = 0.0f;                 HSL results = 0 ? 1
          //  S = 0.0f;
          //}
          //else                        Chromatic data...
          _iymm0 = vceqq_f32 (_old_delta_max, _const_0);
          _iymm0 = vmvnq_u32 (_iymm0);

          _h8 = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_h8), _iymm0));
          _s8 = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_s8), _iymm0));

          //converting from float HSL to word HSL and saved to buffers
          //_h8 = vdupq_n_f32(0.33f );//debug
          _h8              = vmulq_f32 (_h8, _const_255);
          int32x4_t _h_i32 = vcvtq_s32_f32 (_h8);
          int16x4_t _h_i16 = vreinterpret_s16_u16 (vqmovun_s32 (_h_i32));
          vst1_s16 (_h, _h_i16);
          _h += _ppc;

          //_s8 = vdupq_n_f32(0.5f );//debug
          _s8              = vmulq_f32 (_s8, _const_255);
          int32x4_t _s_i32 = vcvtq_s32_f32 (_s8);
          int16x4_t _s_i16 = vreinterpret_s16_u16 (vqmovun_s32 (_s_i32));
          vst1_s16 (_s, _s_i16);
          _s += _ppc;

          _l8              = vmulq_f32 (_l8, _const_255);
          int32x4_t _l_i32 = vcvtq_s32_f32 (_l8);
          int16x4_t _l_i16 = vreinterpret_s16_u16 (vqmovun_s32 (_l_i32));
          vst1_s16 (_l, _l_i16);
          _l += _ppc;
        }

      FAST_MOVE_CPTR (_rgb24, _leak_rgb);
      FAST_MOVE_PTR (_h, _leak_hsl);
      FAST_MOVE_PTR (_s, _leak_hsl);
      FAST_MOVE_PTR (_l, _leak_hsl);
    }

  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
