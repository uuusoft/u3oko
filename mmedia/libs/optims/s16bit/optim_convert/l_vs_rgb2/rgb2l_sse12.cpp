/**
\file      rgb2l_sse1.cpp
\brief     Набор функция для конвертации L <---> RGB16
\author    Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create    27.11.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb2.hpp"
#include "rgb_to_l_int2.hpp"
#include "../hsl_vs_rgb/rgb_to_hsl_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::convert::l_vs_rgb2
{
U3_SET_TARGET_CPU (sse)
void
rgb24_to_l_sse1 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  return rgb24_to_l_alu (info);
#  if 0
    RGB2L_PREFIX(4 );

    const __m128  const_255    = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d255[0] );
    const __m128  const_1_to_2 = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d1_to_2[0] );
    const __m128  const_1_to_255 = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d1_to_255[0] );

    __m128i     ir8;
    __m128i     ig8;
    __m128i     ib8;

    __m128i     i128_1;
    __m128i     i128_2;

    for( std::uint32_t indxy = 0; indxy < height; ++indxy )
    {
      for( std::uint32_t indxx = 0; indxx < width; indxx+= ppc )
      {
        i128_1 = _mm_loadu_si128( ::libs::helpers::casts::reinterpret_cast_helper<const __m128i*>( rgb24 ) );  //BOG0R0B1G1R1B2G2R2B3G3R3B4G4R4

        SLOW_SPLIT_RGB24_SSE1( i128_1, ir8, ig8, ib8 );

        //convert RGB double word from 8 pixel to float;
        __m128 temp_r = _mm_cvtepi32_ps( ir8 );
        __m128 temp_g = _mm_cvtepi32_ps( ig8 );
        __m128 temp_b = _mm_cvtepi32_ps( ib8 );

        //normalization from 0..255 to 0.0F..1.0F;
        temp_r = _mm_mul_ps( temp_r, const_1_to_255 );
        temp_g = _mm_mul_ps( temp_g, const_1_to_255 );
        temp_b = _mm_mul_ps( temp_b, const_1_to_255 );

        rgb24+= 3;

        //float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
        __m128 var_min = _mm_min_ps( temp_g, temp_r );
        var_min = _mm_min_ps( temp_b, var_min );

        //float max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
        __m128 max = _mm_max_ps( temp_g, temp_r );
        max = _mm_max_ps( temp_b, max );

        //max_min = max + var_Min;
        const __m128 max_min = _mm_add_ps( var_min, max );

        //L = ( max + var_Min ) / 2.0F;
        __m128 l8 = _mm_mul_ps( const_1_to_2, max_min );

        l8 = _mm_mul_ps( l8, const_255 );
        i128_1 = _mm_cvtps_epi32( l8 );
        i128_2 = _mm_castpd_si128( _mm_shuffle_pd( _mm_castsi128_pd( i128_1 ), _mm_castsi128_pd( i128_1 ), 1 ) );
        i128_1 = _mm_packs_epi32( i128_1, i128_2 );
        _mm_storeu_si128( ::libs::helpers::casts::reinterpret_cast_helper<__m128i*>( l), i128_1 );
        l+= 4;
      }

      rgb24 = ::libs::helpers::mem::move_cptr( rgb24,  leak_rgb );
      l = ::libs::helpers::mem::move_ptr( l,  leak_hsl);
    }
#  endif
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb2

#endif
