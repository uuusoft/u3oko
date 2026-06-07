/**
\file       rgb2hsl_avx2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create     04.09.2016
\project    u3_optim_convert
\brief      HSL <---> RGB16
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "rgb_to_hsl_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
U3_SET_TARGET_CPU (avx2)
void
rgb24_to_hsl_avx2 (::libs::optim::io::MCallInfo& info)
{
  RGB2HSL_PREFIX (8);
  // U3_XLOG_DEV ("count_threads_=" << info.count_threads_ << " indx_thread_=" << info.indx_thread_ << " width=" << width << " height=" << height << " raw_cycle=" << raw_cycle << " cycle=" << cycle << " leak_rgb=" << leak_rgb);
  _mm256_zeroall ();

  const __m256 const_0        = _mm256_setzero_ps ();
  const __m256 const_1        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1);
  const __m256 const_2        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d2);
  const __m256 const_255      = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d255);
  const __m256 const_1_to_2   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_2);
  const __m256 const_1_to_3   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_3);
  const __m256 const_1_to_6   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_6);
  const __m256 const_1_to_255 = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_255);
  const __m256 const_2_to_3   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d2_to_3);
  __m256i      ir8            = _mm256_setzero_si256 ();
  __m256i      ig8            = _mm256_setzero_si256 ();
  __m256i      ib8            = _mm256_setzero_si256 ();
  __m256i      i256_2         = _mm256_setzero_si256 ();

  SPLIT_RGB24_AVX2_DEFINE_REGS;

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      __m256i i256_1 = _mm256_loadu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (rgb24));   // BOG0R0 B1G1R1 B2G2R2 B3G3R3 B4G4R4 B5G5R5 B6G6R6 B7G7R7

      SPLIT_RGB24_AVX2 (i256_1, ir8, ig8, ib8);

      // convert RGB double word from 8 pixel to float;
      __m256 temp_r = _mm256_cvtepi32_ps (ir8);
      __m256 temp_g = _mm256_cvtepi32_ps (ig8);
      __m256 temp_b = _mm256_cvtepi32_ps (ib8);

      // normalization from 0..255 to 0.0F..1.0F;
      temp_r = _mm256_mul_ps (temp_r, const_1_to_255);
      temp_g = _mm256_mul_ps (temp_g, const_1_to_255);
      temp_b = _mm256_mul_ps (temp_b, const_1_to_255);

      rgb24 += 6;

      // float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
      __m256 var_min = _mm256_min_ps (temp_g, temp_r);
      var_min        = _mm256_min_ps (temp_b, var_min);

      // float max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
      __m256 max = _mm256_max_ps (temp_g, temp_r);
      max        = _mm256_max_ps (temp_b, max);

      // max_min = max + var_Min;
      const __m256 max_min = _mm256_add_ps (var_min, max);

      // L = ( max + var_Min ) / 2.0F;
      __m256 l8 = _mm256_mul_ps (const_1_to_2, max_min);

      // float delta_max = max - var_Min; Delta RGB value
      const __m256 old_delta_max = _mm256_sub_ps (max, var_min);

      // if ( delta_max == 0 )  This is a gray, no chroma...
      //{
      //   H = 0.0F;       HSL results = 0 ? 1
      //   S = 0.0F;
      // }
      // else            Chromatic data...
      __m256 temp1 = _mm256_cmp_ps (const_0, old_delta_max, 0);
      __m256 temp2 = _mm256_and_ps (temp1, const_1);

      // add 1.0F for distance from 0.0;
      const __m256 delta_max      = _mm256_add_ps (old_delta_max, temp2);
      const __m256 half_delta_max = _mm256_mul_ps (const_1_to_2, delta_max);

      // if ( L < 0.5f ) S = delta_max / ( max + var_Min );
      // else            S = delta_max / ( 2.0F - ( max + var_Min) );
      __m256 temp4 = _mm256_div_ps (delta_max, max_min);   // RES S
      __m256 s8    = _mm256_sub_ps (const_2, max_min);

      s8    = _mm256_div_ps (delta_max, s8);   // RES S
      temp1 = _mm256_cmp_ps (l8, const_1_to_2, 1);
      temp4 = _mm256_and_ps (temp4, temp1);
      temp2 = _mm256_cmp_ps (const_1_to_2, const_1_to_2, 0);
      temp2 = _mm256_xor_ps (temp2, temp1);
      s8    = _mm256_and_ps (s8, temp2);
      s8    = _mm256_or_ps (s8, temp4);

      const __m256 inv_delta_max = _mm256_rcp_ps (delta_max);

      // float delta_r = ( ( ( max - var_R ) / 6.0F ) + ( delta_max / 2.0F ) ) / delta_max;
      //  1.( max - var_R );
      //  2.( max - var_R ) / 6.0F;
      //  3.( delta_max / 2.0F )
      //  4.( ( max - var_R ) / 6.0F ) + ( delta_max / 2.0F ) )
      //  5.end
      __m256 delta_r = _mm256_sub_ps (max, temp_r);
      delta_r        = _mm256_mul_ps (delta_r, const_1_to_6);
      delta_r        = _mm256_add_ps (delta_r, half_delta_max);
      delta_r        = _mm256_mul_ps (delta_r, inv_delta_max);

      // float delta_g = ( ( ( max - var_G ) / 6.0F ) + ( delta_max / 2.0F ) ) / delta_max;
      //  1.( max - var_G )
      //  2.( max - var_G ) / 6.0F
      //  3.( delta_max / 2.0F )
      //  4.( ( max - var_G ) / 6.0F ) + ( delta_max / 2.0F ) )
      //  5.end
      __m256 delta_g = _mm256_sub_ps (max, temp_g);
      delta_g        = _mm256_mul_ps (delta_g, const_1_to_6);
      delta_g        = _mm256_add_ps (delta_g, half_delta_max);
      delta_g        = _mm256_mul_ps (delta_g, inv_delta_max);

      // float delta_b = ( ( ( max - var_B ) / 6.0F ) + ( delta_max / 2.0F ) ) / delta_max;
      //  1.( max - var_B )
      //  2.( max - var_B ) / 6.0F
      //  3.( delta_max / 2.0F )
      //  4.( ( max - var_B ) / 6.0F ) + ( delta_max / 2.0F ) )
      //  5.end
      __m256 delta_b = _mm256_sub_ps (max, temp_b);
      delta_b        = _mm256_mul_ps (delta_b, const_1_to_6);
      delta_b        = _mm256_add_ps (delta_b, half_delta_max);
      delta_b        = _mm256_mul_ps (delta_b, inv_delta_max);

      // if      ( var_R == max ) H = delta_b - delta_g;
      // else if ( var_G == max ) H = ( 1.0F / 3.0F ) + delta_r - delta_b;
      // else if ( var_B == max ) H = ( 2.0F / 3.0F ) + delta_g - delta_r;
      temp4 = delta_g;
      // else if ( var_B == max ) H = ( 2.0F / 3.0F ) + delta_g - delta_r;
      __m256 temp5 = _mm256_add_ps (const_2_to_3, temp4);
      temp5        = _mm256_sub_ps (temp5, delta_r);
      // else if ( var_G == max ) H = ( 1.0F / 3.0F ) + delta_r - delta_b;
      __m256 temp6 = _mm256_add_ps (const_1_to_3, delta_r);
      temp6        = _mm256_sub_ps (temp6, delta_b);   // RES H
      temp2        = temp_g;
      __m256 temp3 = temp2;
      temp2        = _mm256_cmp_ps (temp2, max, 0);
      temp6        = _mm256_and_ps (temp6, temp2);
      temp3        = _mm256_cmp_ps (temp3, max, 4);
      temp5        = _mm256_and_ps (temp5, temp3);
      temp5        = _mm256_or_ps (temp5, temp6);
      // if      ( var_R == max ) H = delta_b - delta_g;
      temp6 = delta_b;
      temp2 = delta_g;
      temp6 = _mm256_sub_ps (temp6, temp2);
      temp2 = temp_r;
      temp3 = temp2;
      temp2 = _mm256_cmp_ps (temp2, max, 0);
      temp3 = _mm256_cmp_ps (temp3, max, 4);
      temp6 = _mm256_and_ps (temp6, temp2);
      temp5 = _mm256_and_ps (temp5, temp3);
      temp5 = _mm256_or_ps (temp5, temp6);

      // if ( H < 0 ) H += 1.0F;
      temp3 = const_1;
      temp4 = temp5;
      temp4 = _mm256_cmp_ps (temp4, const_0, 1);
      temp3 = _mm256_and_ps (temp3, temp4);
      temp5 = _mm256_add_ps (temp5, temp3);
      // if ( H > 1 ) H -= 1.0F;
      temp4     = temp5;
      temp3     = const_1;
      temp3     = _mm256_cmp_ps (temp3, temp4, 1);
      temp2     = _mm256_and_ps (const_1, temp3);
      temp5     = _mm256_sub_ps (temp5, temp2);
      __m256 h8 = temp5;

      // if ( delta_max == 0 )  This is a gray, no chroma...
      //{
      //   H = 0.0F;       HSL results = 0 ? 1
      //   S = 0.0F;
      // }
      // else            Chromatic data...
      temp2 = _mm256_setzero_ps ();
      temp1 = _mm256_cmp_ps (old_delta_max, temp2, 4);

      h8 = _mm256_and_ps (h8, temp1);
      s8 = _mm256_and_ps (s8, temp1);

      // converting from float HSL to word HSL and saved to bufs
      h8     = _mm256_mul_ps (h8, const_255);
      i256_1 = _mm256_cvtps_epi32 (h8);
      i256_2 = _mm256_permute2f128_si256 (i256_1, i256_1, 1);
      i256_1 = _mm256_packs_epi32 (i256_1, i256_2);

      _mm256_storeu_si256 (::libs::helpers::casts::reinterpret_cast_helper< __m256i* > (h), i256_1);
      h += 8;

      s8     = _mm256_mul_ps (s8, const_255);
      i256_1 = _mm256_cvtps_epi32 (s8);
      i256_2 = _mm256_permute2f128_si256 (i256_1, i256_1, 1);
      i256_1 = _mm256_packs_epi32 (i256_1, i256_2);

      _mm256_storeu_si256 (::libs::helpers::casts::reinterpret_cast_helper< __m256i* > (s), i256_1);
      s += 8;

      l8     = _mm256_mul_ps (l8, const_255);
      i256_1 = _mm256_cvtps_epi32 (l8);
      i256_2 = _mm256_permute2f128_si256 (i256_1, i256_1, 1);
      i256_1 = _mm256_packs_epi32 (i256_1, i256_2);

      _mm256_storeu_si256 (::libs::helpers::casts::reinterpret_cast_helper< __m256i* > (l), i256_1);
      l += 8;
    }

    rgb24 = ::libs::helpers::mem::move_cptr (rgb24, leak_rgb);
    h     = ::libs::helpers::mem::move_ptr (h, leak_hsl);
    s     = ::libs::helpers::mem::move_ptr (s, leak_hsl);
    l     = ::libs::helpers::mem::move_ptr (l, leak_hsl);
  }

  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
