/**
\file       rgb2l_sse2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb2.hpp"
#include "rgb_to_l_int2.hpp"
#include "../hsl_vs_rgb/rgb_to_hsl_int.hpp"

#if defined(U3_CPU_X86)

#  if 0
#    define RGB2L_PREFIX_SSE2                                                                                                                       \
      const __m128i permute32  = _mm128_setr_epi32 (0, 1, 2, 0, 3, 4, 5, 3);                                                                        \
      const __m128i permute_b8 = _mm128_setr_epi8 (0x00, 0x80, 0x80, 0x80, 0x03, 0x80, 0x80, 0x80, 0x06, 0x80, 0x80, 0x80, 0x09, 0x80, 0x80, 0x80); \
      const __m128i permute_g8 = _mm128_setr_epi8 (0x01, 0x80, 0x80, 0x80, 0x04, 0x80, 0x80, 0x80, 0x07, 0x80, 0x80, 0x80, 0x0A, 0x80, 0x80, 0x80); \
      const __m128i permute_r8 = _mm128_setr_epi8 (0x02, 0x80, 0x80, 0x80, 0x05, 0x80, 0x80, 0x80, 0x08, 0x80, 0x80, 0x80, 0x0B, 0x80, 0x80, 0x80);

#  endif

namespace libs::optim::s16bit::convert::l_vs_rgb2
{
U3_SET_TARGET_CPU (sse2)
void
rgb24_to_l_sse2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  return rgb24_to_l_alu (info);
#  if 0
    RGB2L_PREFIX(4 );

    __m128i ir8  = _mm_setzero_si128();
    __m128i ig8  = _mm_setzero_si128();
    __m128i ib8  = _mm_setzero_si128();

    SPLIT_RGB24_SSE2_DEFINE_REGS;

    for( std::uint32_t indxy = 0; indxy < height; ++indxy )
    {
      for( std::uint32_t indxx = 0; indxx < width; indxx+= ppc )
      {
        __m128i i128_1 = _mm_loadu_si128( U3_CAST_REINTERPRET<const __m128i*>( rgb24 ) );    //BOG0R0B1 G1R1B2G2 R2B3G3R3 B4G4R4B5
        //i128_1 = _mm_setr_epi8( 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F );//debug

        SPLIT_RGB24_SSE2( i128_1, ir8, ig8, ib8 );

        rgb24+= 3;

        //select by 16 bit, 32 bit exist for sse4.1
        //float var_Min = min( var_R, min(var_G, var_B) )     Min. value of RGB
        __m128i var_min = _mm_min_epi16( ig8, ir8 );       // 16bit as 32
        var_min = _mm_min_epi16( ib8, var_min );         // 16bit as 32

        //float max = max( var_R, max(var_G, var_B) )        //Max. value of RGB
        __m128i max = _mm_max_epi16( ig8, ir8 );         // 16bit as 32
        max = _mm_max_epi16( ib8, max );             // 16bit as 32

        //max_min = max + var_Min;
        const __m128i max_min = _mm_add_epi16( var_min, max );

        //L = ( max + var_Min ) / 2.0f;
        __m128i l8 = _mm_srai_epi16( max_min, 1 );

        i128_1 = _mm_castpd_si128( _mm_shuffle_pd( _mm_castsi128_pd( l8), _mm_castsi128_pd( l8), 1 ) );
        l8 = _mm_packs_epi32( l8, i128_1 );
        _mm_storeu_si128( U3_CAST_REINTERPRET<__m128i*>( l), l8);
        l+= 4;
      }

      U3_FAST_MOVE_CPTR( rgb24,  leak_rgb );
      U3_FAST_MOVE_PTR( l,  leak_hsl);
    }
#  endif
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb2

#endif
