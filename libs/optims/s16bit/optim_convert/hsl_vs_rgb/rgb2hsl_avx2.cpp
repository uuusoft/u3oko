//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    04.09.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
*\brief     РќР°Р±РѕСЂ С„СѓРЅРєС†РёСЏ РґР»СЏ РєРѕРЅРІРµСЂС‚Р°С†РёРё HSL <---> RGB16
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "rgb_to_hsl_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

UUU_SET_TARGET_CPU (avx2)
void
rgb24_to_hsl_avx2 (::libs::optim::MCallInfo& _info)
{
  RGB2HSL_PREFIX (8);

  _mm256_zeroall ();

  const __m256 _const_0        = _mm256_setzero_ps ();
  const __m256 _const_1        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1);
  const __m256 _const_2        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d2);
  const __m256 _const_255      = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d255);
  const __m256 _const_1_to_2   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_2);
  const __m256 _const_1_to_3   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_3);
  const __m256 _const_1_to_6   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_6);
  const __m256 _const_1_to_255 = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_255);
  const __m256 _const_2_to_3   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d2_to_3);

  __m256i _ir8    = _mm256_setzero_si256 ();
  __m256i _ig8    = _mm256_setzero_si256 ();
  __m256i _ib8    = _mm256_setzero_si256 ();
  __m256i _i256_2 = _mm256_setzero_si256 ();

  SPLIT_RGB24_AVX2_DEFINE_REGS;

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
          __m256 _var_min = _mm256_min_ps (_temp_g, _temp_r);
          _var_min        = _mm256_min_ps (_temp_b, _var_min);

          //float _max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
          __m256 _max = _mm256_max_ps (_temp_g, _temp_r);
          _max        = _mm256_max_ps (_temp_b, _max);

          //_max_min = _max + var_Min;
          const __m256 _max_min = _mm256_add_ps (_var_min, _max);

          //L = ( _max + var_Min ) / 2.0f;
          __m256 _l8 = _mm256_mul_ps (_const_1_to_2, _max_min);

          //float _delta_max = _max - var_Min; Delta RGB value
          const __m256 _old_delta_max = _mm256_sub_ps (_max, _var_min);

          //if ( _delta_max == 0 )  This is a gray, no chroma...
          //{
          //  H = 0.0f;       HSL results = 0 ? 1
          //  S = 0.0f;
          //}
          //else            Chromatic data...
          __m256 _temp1 = _mm256_cmp_ps (_const_0, _old_delta_max, 0);
          __m256 _temp2 = _mm256_and_ps (_temp1, _const_1);

          //add 1.0f for distance from 0.0;
          const __m256 _delta_max      = _mm256_add_ps (_old_delta_max, _temp2);
          const __m256 _half_delta_max = _mm256_mul_ps (_const_1_to_2, _delta_max);

          //if ( L < 0.5f ) S = _delta_max / ( _max + var_Min );
          //else            S = _delta_max / ( 2.0f - ( _max + var_Min) );
          __m256 _temp4 = _mm256_div_ps (_delta_max, _max_min);      //RES S
          __m256 _s8    = _mm256_sub_ps (_const_2, _max_min);

          _s8    = _mm256_div_ps (_delta_max, _s8);      //RES S
          _temp1 = _mm256_cmp_ps (_l8, _const_1_to_2, 1);
          _temp4 = _mm256_and_ps (_temp4, _temp1);
          _temp2 = _mm256_cmp_ps (_const_1_to_2, _const_1_to_2, 0);
          _temp2 = _mm256_xor_ps (_temp2, _temp1);
          _s8    = _mm256_and_ps (_s8, _temp2);
          _s8    = _mm256_or_ps (_s8, _temp4);

          const __m256 _inv_delta_max = _mm256_rcp_ps (_delta_max);

          //float _delta_r = ( ( ( _max - var_R ) / 6.0f ) + ( _delta_max / 2.0f ) ) / _delta_max;
          // 1.( _max - var_R );
          // 2.( _max - var_R ) / 6.0f;
          // 3.( _delta_max / 2.0f )
          // 4.( ( _max - var_R ) / 6.0f ) + ( _delta_max / 2.0f ) )
          // 5.end
          __m256 _delta_r = _mm256_sub_ps (_max, _temp_r);
          _delta_r        = _mm256_mul_ps (_delta_r, _const_1_to_6);
          _delta_r        = _mm256_add_ps (_delta_r, _half_delta_max);
          _delta_r        = _mm256_mul_ps (_delta_r, _inv_delta_max);

          //float _delta_g = ( ( ( _max - var_G ) / 6.0f ) + ( _delta_max / 2.0f ) ) / _delta_max;
          // 1.( _max - var_G )
          // 2.( _max - var_G ) / 6.0f
          // 3.( _delta_max / 2.0f )
          // 4.( ( _max - var_G ) / 6.0f ) + ( _delta_max / 2.0f ) )
          // 5.end
          __m256 _delta_g = _mm256_sub_ps (_max, _temp_g);
          _delta_g        = _mm256_mul_ps (_delta_g, _const_1_to_6);
          _delta_g        = _mm256_add_ps (_delta_g, _half_delta_max);
          _delta_g        = _mm256_mul_ps (_delta_g, _inv_delta_max);

          //float _delta_b = ( ( ( _max - var_B ) / 6.0f ) + ( _delta_max / 2.0f ) ) / _delta_max;
          // 1.( _max - var_B )
          // 2.( _max - var_B ) / 6.0f
          // 3.( _delta_max / 2.0f )
          // 4.( ( _max - var_B ) / 6.0f ) + ( _delta_max / 2.0f ) )
          // 5.end
          __m256 _delta_b = _mm256_sub_ps (_max, _temp_b);
          _delta_b        = _mm256_mul_ps (_delta_b, _const_1_to_6);
          _delta_b        = _mm256_add_ps (_delta_b, _half_delta_max);
          _delta_b        = _mm256_mul_ps (_delta_b, _inv_delta_max);

          //if      ( var_R == _max ) H = _delta_b - _delta_g;
          //else if ( var_G == _max ) H = ( 1.0f / 3.0f ) + _delta_r - _delta_b;
          //else if ( var_B == _max ) H = ( 2.0f / 3.0f ) + _delta_g - _delta_r;
          _temp4 = _delta_g;
          //else if ( var_B == _max ) H = ( 2.0f / 3.0f ) + _delta_g - _delta_r;
          __m256 _temp5 = _mm256_add_ps (_const_2_to_3, _temp4);
          _temp5        = _mm256_sub_ps (_temp5, _delta_r);
          //else if ( var_G == _max ) H = ( 1.0f / 3.0f ) + _delta_r - _delta_b;
          __m256 _temp6 = _mm256_add_ps (_const_1_to_3, _delta_r);
          _temp6        = _mm256_sub_ps (_temp6, _delta_b);      //RES H
          _temp2        = _temp_g;
          __m256 _temp3 = _temp2;
          _temp2        = _mm256_cmp_ps (_temp2, _max, 0);
          _temp6        = _mm256_and_ps (_temp6, _temp2);
          _temp3        = _mm256_cmp_ps (_temp3, _max, 4);
          _temp5        = _mm256_and_ps (_temp5, _temp3);
          _temp5        = _mm256_or_ps (_temp5, _temp6);
          //if      ( var_R == _max ) H = _delta_b - _delta_g;
          _temp6 = _delta_b;
          _temp2 = _delta_g;
          _temp6 = _mm256_sub_ps (_temp6, _temp2);
          _temp2 = _temp_r;
          _temp3 = _temp2;
          _temp2 = _mm256_cmp_ps (_temp2, _max, 0);
          _temp3 = _mm256_cmp_ps (_temp3, _max, 4);
          _temp6 = _mm256_and_ps (_temp6, _temp2);
          _temp5 = _mm256_and_ps (_temp5, _temp3);
          _temp5 = _mm256_or_ps (_temp5, _temp6);

          //if ( H < 0 ) H += 1.0f;
          _temp3 = _const_1;
          _temp4 = _temp5;
          _temp4 = _mm256_cmp_ps (_temp4, _const_0, 1);
          _temp3 = _mm256_and_ps (_temp3, _temp4);
          _temp5 = _mm256_add_ps (_temp5, _temp3);
          //if ( H > 1 ) H -= 1.0f;
          _temp4     = _temp5;
          _temp3     = _const_1;
          _temp3     = _mm256_cmp_ps (_temp3, _temp4, 1);
          _temp2     = _mm256_and_ps (_const_1, _temp3);
          _temp5     = _mm256_sub_ps (_temp5, _temp2);
          __m256 _h8 = _temp5;

          //if ( _delta_max == 0 )  This is a gray, no chroma...
          //{
          //  H = 0.0f;       HSL results = 0 ? 1
          //  S = 0.0f;
          //}
          //else            Chromatic data...
          _temp2 = _mm256_setzero_ps ();
          _temp1 = _mm256_cmp_ps (_old_delta_max, _temp2, 4);

          _h8 = _mm256_and_ps (_h8, _temp1);
          _s8 = _mm256_and_ps (_s8, _temp1);

          //converting from float HSL to word HSL and saved to buffers
          _h8     = _mm256_mul_ps (_h8, _const_255);
          _i256_1 = _mm256_cvtps_epi32 (_h8);
          _i256_2 = _mm256_permute2f128_si256 (_i256_1, _i256_1, 1);
          _i256_1 = _mm256_packs_epi32 (_i256_1, _i256_2);
          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_h), _i256_1);
          _h += 8;

          _s8     = _mm256_mul_ps (_s8, _const_255);
          _i256_1 = _mm256_cvtps_epi32 (_s8);
          _i256_2 = _mm256_permute2f128_si256 (_i256_1, _i256_1, 1);
          _i256_1 = _mm256_packs_epi32 (_i256_1, _i256_2);
          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_s), _i256_1);
          _s += 8;

          _l8     = _mm256_mul_ps (_l8, _const_255);
          _i256_1 = _mm256_cvtps_epi32 (_l8);
          _i256_2 = _mm256_permute2f128_si256 (_i256_1, _i256_1, 1);
          _i256_1 = _mm256_packs_epi32 (_i256_1, _i256_2);
          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_l), _i256_1);
          _l += 8;
        }

      FAST_MOVE_CPTR (_rgb24, _leak_rgb);
      FAST_MOVE_PTR (_h, _leak_hsl);
      FAST_MOVE_PTR (_s, _leak_hsl);
      FAST_MOVE_PTR (_l, _leak_hsl);
    }

  _mm256_zeroupper ();
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
