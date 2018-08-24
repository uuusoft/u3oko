//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       rgb2l_avx2.cpp
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    10.09.2016
*\copyright www.uuusoft.com
*\project   uuu_optim_convert
*\brief     РќР°Р±РѕСЂ С„СѓРЅРєС†РёСЏ РґР»СЏ РєРѕРЅРІРµСЂС‚Р°С†РёРё L <---> RGB16
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb.hpp"
#include "rgb_to_l_int.hpp"
#include "../hsl_vs_rgb/rgb_to_hsl_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace l_vs_rgb {

UUU_SET_TARGET_CPU (avx2)
void
rgb24_to_l_avx2_float (::libs::optim::MCallInfo& _info)
{
  RGB2L_PREFIX (8);
  SPLIT_RGB24_AVX2_DEFINE_REGS;

  _mm256_zeroall ();

  const __m256 _const_1_to_255 = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_255);
  const __m256 _const_1_to_2   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_2);
  const __m256 _const_255      = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d255);

  __m256i _ir8 = _mm256_setzero_si256 ();
  __m256i _ig8 = _mm256_setzero_si256 ();
  __m256i _ib8 = _mm256_setzero_si256 ();

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          __m256i _i256_1 = _mm256_loadu_si256 (UUU_MEM_CAST<const __m256i*> (_rgb24));      //BOG0R0 B1G1R1 B2G2R2 B3G3R3 B4G4R4 B5G5R5 B6G6R6 B7G7R7

          SPLIT_RGB24_AVX2 (_i256_1, _ir8, _ig8, _ib8);

          //convert RGB double word from 8 pixel to float;
          __m256 _temp_r = _mm256_cvtepi32_ps (_ir8);
          __m256 _temp_g = _mm256_cvtepi32_ps (_ig8);
          __m256 _temp_b = _mm256_cvtepi32_ps (_ib8);

          //normalization from 0..255 to 0.0f..1.0f;
          _temp_r = _mm256_mul_ps (_temp_r, _const_1_to_255);
          _temp_g = _mm256_mul_ps (_temp_g, _const_1_to_255);
          _temp_b = _mm256_mul_ps (_temp_b, _const_1_to_255);

          _rgb24 += 6;

          //float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
          __m256 _var_min = _temp_r;
          _var_min        = _mm256_min_ps (_temp_g, _var_min);
          _var_min        = _mm256_min_ps (_temp_b, _var_min);

          //float _max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
          __m256 _max = _mm256_max_ps (_temp_g, _temp_r);
          _max        = _mm256_max_ps (_temp_b, _max);

          //_max_min = _max + var_Min;
          __m256 _max_min = _mm256_add_ps (_var_min, _max);

          //L = ( _max + var_Min ) / 2.0f;
          __m256 _l8 = _mm256_mul_ps (_const_1_to_2, _max_min);

          //converting from float HSL to word HSL and saved to buffers
          _l8             = _mm256_mul_ps (_l8, _const_255);
          _i256_1         = _mm256_cvtps_epi32 (_l8);
          __m256i _i256_2 = _mm256_permute2f128_si256 (_i256_1, _i256_1, 1);
          _i256_1         = _mm256_packs_epi32 (_i256_1, _i256_2);
          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_l), _i256_1);

          _l += 8;
        }

      FAST_MOVE_CPTR (_rgb24, _leak_rgb);
      FAST_MOVE_PTR (_l, _leak_hsl);
    }

  _mm256_zeroupper ();
  return;
}


UUU_SET_TARGET_CPU (avx2)
void
rgb24_to_l_avx2 (::libs::optim::MCallInfo& _info)
{
  RGB2L_PREFIX (8);
  SPLIT_RGB24_AVX2_DEFINE_REGS;

  _mm256_zeroall ();

  __m256i _ir8 = _mm256_setzero_si256 ();
  __m256i _ig8 = _mm256_setzero_si256 ();
  __m256i _ib8 = _mm256_setzero_si256 ();

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          __m256i _i256_1 = _mm256_loadu_si256 (UUU_MEM_CAST<const __m256i*> (_rgb24));      //BOG0R0 B1G1R1 B2G2R2 B3G3R3 B4G4R4 B5G5R5 B6G6R6 B7G7R7

          SPLIT_RGB24_AVX2 (_i256_1, _ir8, _ig8, _ib8);

          _rgb24 += 6;

          //float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
          __m256i _var_min = _ir8;
          _var_min         = _mm256_min_epi32 (_ig8, _var_min);
          _var_min         = _mm256_min_epi32 (_ib8, _var_min);

          //float _max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
          __m256i _max = _mm256_max_epi32 (_ig8, _ir8);
          _max         = _mm256_max_epi32 (_ib8, _max);

          //_max_min = _max + var_Min;
          __m256i _max_min = _mm256_add_epi32 (_var_min, _max);

          //L = ( _max + var_Min ) / 2.0f;
          __m256i _l8 = _mm256_srai_epi32 (_max_min, 1);

          //converting from float HSL to word HSL and saved to buffers
          __m256i _l8_2 = _mm256_permute2f128_si256 (_l8, _l8, 1);
          _l8           = _mm256_packs_epi32 (_l8, _l8_2);
          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_l), _l8);

          _l += 8;
        }

      FAST_MOVE_CPTR (_rgb24, _leak_rgb);
      FAST_MOVE_PTR (_l, _leak_hsl);
    }

  _mm256_zeroupper ();
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::l_vs_rgb

#endif
