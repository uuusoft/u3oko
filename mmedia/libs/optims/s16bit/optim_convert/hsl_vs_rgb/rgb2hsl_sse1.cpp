/**
\file
\author    Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create    27.11.2016
\project    u3_optim_convert
\brief     Набор функция для конвертации HSL <---> RGB16
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "rgb_to_hsl_int.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
U3_SET_TARGET_CPU (sse)
void
rgb24_to_hsl_sse1 (::libs::optim::io::MCallInfo& info)
{
#  if 1

  rgb24_to_hsl_alu (info);
  return;

#  else

  RGB2HSL_PREFIX (4);

  const __m128 const_0        = _mm_setzero_ps ();
  const __m128 const_1        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1[0]);
  const __m128 const_2        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d2[0]);
  const __m128 const_255      = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d255[0]);
  const __m128 const_1_to_2   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_2[0]);
  const __m128 const_1_to_3   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_3[0]);
  const __m128 const_1_to_6   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_6[0]);
  const __m128 const_1_to_255 = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_255[0]);
  const __m128 const_2_to_3   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d2_to_3[0]);

  __m128i ir8;
  __m128i ig8;
  __m128i ib8;

  __m128i i128_1;
  __m128i i128_2;

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      i128_1 = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (rgb24));   // BOG0R0B1G1R1B2G2R2B3G3R3B4G4R4

      SLOW_SPLIT_RGB24_SSE1 (i128_1, ir8, ig8, ib8);

      // convert RGB double word from 8 pixel to float;
      __m128 temp_r = _mm_cvtepi32_ps (ir8);
      __m128 temp_g = _mm_cvtepi32_ps (ig8);
      __m128 temp_b = _mm_cvtepi32_ps (ib8);

      // normalization from 0..255 to 0.0f..1.0f;
      temp_r = _mm_mul_ps (temp_r, const_1_to_255);
      temp_g = _mm_mul_ps (temp_g, const_1_to_255);
      temp_b = _mm_mul_ps (temp_b, const_1_to_255);

      rgb24 += 3;

      // float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
      __m128 var_min = _mm_min_ps (temp_g, temp_r);
      var_min        = _mm_min_ps (temp_b, var_min);

      // float max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
      __m128 max = _mm_max_ps (temp_g, temp_r);
      max        = _mm_max_ps (temp_b, max);

      // max_min = max + var_Min;
      const __m128 max_min = _mm_add_ps (var_min, max);

      // L = ( max + var_Min ) / 2.0f;
      __m128 l8 = _mm_mul_ps (const_1_to_2, max_min);

      // float delta_max = max - var_Min; Delta RGB value
      const __m128 old_delta_max = _mm_sub_ps (max, var_min);

      // if ( delta_max == 0 )  This is a gray, no chroma...
      //{
      //   H = 0.0f;       HSL results = 0 ? 1
      //   S = 0.0f;
      // }
      // else            Chromatic data...
      __m128 temp1 = _mm_cmpeq_ps (const_0, old_delta_max);
      __m128 temp2 = _mm_and_ps (temp1, const_1);

      // add 1.0f for distance from 0.0;
      const __m128 delta_max      = _mm_add_ps (old_delta_max, temp2);
      const __m128 half_delta_max = _mm_mul_ps (const_1_to_2, delta_max);

      // if ( L < 0.5f ) S = delta_max / ( max + var_Min );
      // else            S = delta_max / ( 2.0f - ( max + var_Min) );
      __m128 temp4 = _mm_div_ps (delta_max, max_min);   // RES S
      __m128 s8    = _mm_sub_ps (const_2, max_min);

      s8    = _mm_div_ps (delta_max, s8);   // RES S
      temp1 = _mm_cmplt_ps (l8, const_1_to_2);
      temp4 = _mm_and_ps (temp4, temp1);
      temp2 = _mm_cmpeq_ps (const_1_to_2, const_1_to_2);
      temp2 = _mm_xor_ps (temp2, temp1);
      s8    = _mm_and_ps (s8, temp2);
      s8    = _mm_or_ps (s8, temp4);

      const __m128 inv_delta_max = _mm_rcp_ps (delta_max);

      // float delta_r = ( ( ( max - var_R ) / 6.0f ) + ( delta_max / 2.0f ) ) / delta_max;
      //  1.( max - var_R );
      //  2.( max - var_R ) / 6.0f;
      //  3.( delta_max / 2.0f )
      //  4.( ( max - var_R ) / 6.0f ) + ( delta_max / 2.0f ) )
      //  5.end
      __m128 delta_r = _mm_sub_ps (max, temp_r);
      delta_r        = _mm_mul_ps (delta_r, const_1_to_6);
      delta_r        = _mm_add_ps (delta_r, half_delta_max);
      delta_r        = _mm_mul_ps (delta_r, inv_delta_max);

      // float delta_g = ( ( ( max - var_G ) / 6.0f ) + ( delta_max / 2.0f ) ) / delta_max;
      //  1.( max - var_G )
      //  2.( max - var_G ) / 6.0f
      //  3.( delta_max / 2.0f )
      //  4.( ( max - var_G ) / 6.0f ) + ( delta_max / 2.0f ) )
      //  5.end
      __m128 delta_g = _mm_sub_ps (max, temp_g);
      delta_g        = _mm_mul_ps (delta_g, const_1_to_6);
      delta_g        = _mm_add_ps (delta_g, half_delta_max);
      delta_g        = _mm_mul_ps (delta_g, inv_delta_max);

      // float delta_b = ( ( ( max - var_B ) / 6.0f ) + ( delta_max / 2.0f ) ) / delta_max;
      //  1.( max - var_B )
      //  2.( max - var_B ) / 6.0f
      //  3.( delta_max / 2.0f )
      //  4.( ( max - var_B ) / 6.0f ) + ( delta_max / 2.0f ) )
      //  5.end
      __m128 delta_b = _mm_sub_ps (max, temp_b);
      delta_b        = _mm_mul_ps (delta_b, const_1_to_6);
      delta_b        = _mm_add_ps (delta_b, half_delta_max);
      delta_b        = _mm_mul_ps (delta_b, inv_delta_max);

      // if      ( var_R == max ) H = delta_b - delta_g;
      // else if ( var_G == max ) H = ( 1.0f / 3.0f ) + delta_r - delta_b;
      // else if ( var_B == max ) H = ( 2.0f / 3.0f ) + delta_g - delta_r;
      temp4 = delta_g;
      // else if ( var_B == max ) H = ( 2.0f / 3.0f ) + delta_g - delta_r;
      __m128 temp5 = _mm_add_ps (const_2_to_3, temp4);
      temp5        = _mm_sub_ps (temp5, delta_r);
      // else if ( var_G == max ) H = ( 1.0f / 3.0f ) + delta_r - delta_b;
      __m128 temp6 = _mm_add_ps (const_1_to_3, delta_r);
      temp6        = _mm_sub_ps (temp6, delta_b);   // RES H
      temp2        = temp_g;
      __m128 temp3 = temp2;
      temp2        = _mm_cmpeq_ps (temp2, max);
      temp6        = _mm_and_ps (temp6, temp2);
      temp3        = _mm_cmpneq_ps (temp3, max);
      temp5        = _mm_and_ps (temp5, temp3);
      temp5        = _mm_or_ps (temp5, temp6);
      // if      ( var_R == max ) H = delta_b - delta_g;
      temp6 = delta_b;
      temp2 = delta_g;
      temp6 = _mm_sub_ps (temp6, temp2);
      temp2 = temp_r;
      temp3 = temp2;
      temp2 = _mm_cmpeq_ps (temp2, max);
      temp3 = _mm_cmpneq_ps (temp3, max);
      temp6 = _mm_and_ps (temp6, temp2);
      temp5 = _mm_and_ps (temp5, temp3);
      temp5 = _mm_or_ps (temp5, temp6);

      // if ( H < 0 ) H += 1.0f;
      temp3 = const_1;
      temp4 = temp5;
      temp4 = _mm_cmplt_ps (temp4, const_0);
      temp3 = _mm_and_ps (temp3, temp4);
      temp5 = _mm_add_ps (temp5, temp3);
      // if ( H > 1 ) H -= 1.0f;
      temp4     = temp5;
      temp3     = const_1;
      temp3     = _mm_cmplt_ps (temp3, temp4);
      temp2     = _mm_and_ps (const_1, temp3);
      temp5     = _mm_sub_ps (temp5, temp2);
      __m128 h8 = temp5;

      // if ( delta_max == 0 )  This is a gray, no chroma...
      //{
      //   H = 0.0f;       HSL results = 0 ? 1
      //   S = 0.0f;
      // }
      // else            Chromatic data...
      temp2 = _mm_setzero_ps ();
      temp1 = _mm_cmpneq_ps (old_delta_max, temp2);

      h8 = _mm_and_ps (h8, temp1);
      s8 = _mm_and_ps (s8, temp1);

      // converting from float HSL to word HSL and saved to bufs
      h8     = _mm_mul_ps (h8, const_255);
      i128_1 = _mm_cvtps_epi32 (h8);
      i128_2 = _mm_castpd_si128 (mm_shuffle_pd (mm_castsi128_pd (i128_1), _mm_castsi128_pd (i128_1), 1));
      i128_1 = _mm_packs_epi32 (i128_1, i128_2);
      _mm_storeu_si128 (U3_CAST_REINTERPRET< __m128i* > (h), i128_1);
      h += 4;

      s8     = _mm_mul_ps (s8, const_255);
      i128_1 = _mm_cvtps_epi32 (s8);
      i128_2 = _mm_castpd_si128 (mm_shuffle_pd (mm_castsi128_pd (i128_1), _mm_castsi128_pd (i128_1), 1));
      i128_1 = _mm_packs_epi32 (i128_1, i128_2);
      _mm_storeu_si128 (U3_CAST_REINTERPRET< __m128i* > (s), i128_1);
      s += 4;

      l8     = _mm_mul_ps (l8, const_255);
      i128_1 = _mm_cvtps_epi32 (l8);
      i128_2 = _mm_castpd_si128 (mm_shuffle_pd (mm_castsi128_pd (i128_1), _mm_castsi128_pd (i128_1), 1));
      i128_1 = _mm_packs_epi32 (i128_1, i128_2);
      _mm_storeu_si128 (U3_CAST_REINTERPRET< __m128i* > (l), i128_1);
      l += 4;
    }

    U3_FAST_MOVE_CPTR (rgb24, leak_rgb);
    U3_FAST_MOVE_PTR (h, leak_hsl);
    U3_FAST_MOVE_PTR (s, leak_hsl);
    U3_FAST_MOVE_PTR (l, leak_hsl);
  }

#  endif
}

}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
