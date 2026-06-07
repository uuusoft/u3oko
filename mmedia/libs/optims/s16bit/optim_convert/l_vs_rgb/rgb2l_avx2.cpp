/**
file        rgb2l_avx2.cpp
author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
create      10.09.2016
copyright   Erashov A.I.
project     u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb.hpp"
#include "rgb_to_l_int.hpp"
#include "../hsl_vs_rgb/rgb_to_hsl_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::convert::l_vs_rgb
{
U3_SET_TARGET_CPU (avx2)
void
rgb24_to_l_avx2_float (::libs::optim::io::MCallInfo& info)
{
  RGB2L_PREFIX (8);
  SPLIT_RGB24_AVX2_DEFINE_REGS;

  _mm256_zeroall ();

  const __m256 const_1_to_255 = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_255);
  const __m256 const_1_to_2   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_2);
  const __m256 const_255      = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d255);

  __m256i ir8 = _mm256_setzero_si256 ();
  __m256i ig8 = _mm256_setzero_si256 ();
  __m256i ib8 = _mm256_setzero_si256 ();

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
      __m256 var_min = temp_r;
      var_min        = _mm256_min_ps (temp_g, var_min);
      var_min        = _mm256_min_ps (temp_b, var_min);

      // float max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
      __m256 max = _mm256_max_ps (temp_g, temp_r);
      max        = _mm256_max_ps (temp_b, max);

      // max_min = max + var_Min;
      __m256 max_min = _mm256_add_ps (var_min, max);

      // L = ( max + var_Min ) / 2.0F;
      __m256 l8 = _mm256_mul_ps (const_1_to_2, max_min);

      // converting from float HSL to word HSL and saved to bufs
      l8             = _mm256_mul_ps (l8, const_255);
      i256_1         = _mm256_cvtps_epi32 (l8);
      __m256i i256_2 = _mm256_permute2f128_si256 (i256_1, i256_1, 1);
      i256_1         = _mm256_packs_epi32 (i256_1, i256_2);
      _mm256_storeu_si256 (::libs::helpers::casts::reinterpret_cast_helper< __m256i* > (l), i256_1);

      l += 8;
    }

    rgb24 = ::libs::helpers::mem::move_cptr (rgb24, leak_rgb);
    l     = ::libs::helpers::mem::move_ptr (l, leak_hsl);
  }

  _mm256_zeroupper ();
}


U3_SET_TARGET_CPU (avx2)
void
rgb24_to_l_avx2 (::libs::optim::io::MCallInfo& info)
{
  RGB2L_PREFIX (8);
  SPLIT_RGB24_AVX2_DEFINE_REGS;

  _mm256_zeroall ();

  __m256i ir8 = _mm256_setzero_si256 ();
  __m256i ig8 = _mm256_setzero_si256 ();
  __m256i ib8 = _mm256_setzero_si256 ();

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      __m256i i256_1 = _mm256_loadu_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (rgb24));   // BOG0R0 B1G1R1 B2G2R2 B3G3R3 B4G4R4 B5G5R5 B6G6R6 B7G7R7

      SPLIT_RGB24_AVX2 (i256_1, ir8, ig8, ib8);

      rgb24 += 6;

      // float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
      __m256i var_min = ir8;
      var_min         = _mm256_min_epi32 (ig8, var_min);
      var_min         = _mm256_min_epi32 (ib8, var_min);

      // float max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
      __m256i max = _mm256_max_epi32 (ig8, ir8);
      max         = _mm256_max_epi32 (ib8, max);

      // max_min = max + var_Min;
      __m256i max_min = _mm256_add_epi32 (var_min, max);

      // L = ( max + var_Min ) / 2.0F;
      __m256i l8 = _mm256_srai_epi32 (max_min, 1);

      // converting from float HSL to word HSL and saved to bufs
      __m256i l8_2 = _mm256_permute2f128_si256 (l8, l8, 1);
      l8           = _mm256_packs_epi32 (l8, l8_2);
      _mm256_storeu_si256 (::libs::helpers::casts::reinterpret_cast_helper< __m256i* > (l), l8);

      l += 8;
    }

    rgb24 = ::libs::helpers::mem::move_cptr (rgb24, leak_rgb);
    l     = ::libs::helpers::mem::move_ptr (l, leak_hsl);
  }

  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb

#endif
