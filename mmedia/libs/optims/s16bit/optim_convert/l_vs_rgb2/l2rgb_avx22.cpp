/**
\file       l2rgb_avx2.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb2.hpp"
#include "l_to_rgb_int2.hpp"
#include "../hsl_vs_rgb/rgb_to_hsl_int.hpp"

#ifdef U3_CPU_X86

namespace libs::optim::s16bit::convert::l_vs_rgb2
{
U3_SET_TARGET_CPU (avx2)
void
l_to_rgb24_avx2 (::libs::optim::io::MCallInfo& info)
{
#  if 1
  return l_to_rgb24_alu (info);
#  else

  L2RGB_PREFIX (16);

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      const __m256i val = _mm256_load_si256 (::libs::helpers::casts::reinterpret_cast_helper< const __m256i* > (rgb24));

      _mm256_storeu_si256 (::libs::helpers::casts::reinterpret_cast_helper< __m256i* > (rgb24 + 0), val);
      _mm256_storeu_si256 (::libs::helpers::casts::reinterpret_cast_helper< __m256i* > (rgb24 + 16), val);
      _mm256_storeu_si256 (::libs::helpers::casts::reinterpret_cast_helper< __m256i* > (rgb24 + 32), val);

      l += 16;
      rgb24 += 3 * 16;
    }

    rgb24 = ::libs::helpers::mem::move_ptr (rgb24, leak_l);
    l     = ::libs::helpers::mem::move_cptr (l, leak_l);
  }

  return;

#    if 0
    U3_CHECK( check_l2rgb( info ), "failde check l2rgb" );

    const std::uint32_t width      = info.srcs_[0].width_;
    const std::uint32_t height     = info.srcs_[0].height_;
    const std::uint32_t stride_l   = info.srcs_[0].stride_;
    const std::uint32_t leak_bytes   = stride_l - width * sizeof (std::uint16_t );
    const std::uint32_t stride_rgb24 = width * sizeof (std::uint8_t) * 3;
    const std::int16_t*    buf_l     = info.srcs_[0].buf();
    std::uint8_t*    rgb24      = info.dsts_[0].ubuf();
    int*        out_stride   = info.params_.pints_[0];

    if (0 == *out_stride )
    {
      *out_stride = stride_rgb24;
    }

    const std::uint32_t  leak_l   = *out_stride - stride_rgb24;
    std::uint8_t*    cstring  = rgb24;

    for (std::uint32_t indxy = 0; indxy < height; ++indxy)
    {
      for (std::uint32_t indxx = 0; indxx < width; ++indxx )
      {
        const std::uint8_t val = buf_l[0];
        cstring[0] = val;
        cstring[1] = val;
        cstring[2] = val;

        buf_l++;
        cstring += 3;
      }

      cstring = ::libs::helpers::mem::move_ptr( cstring,  leak_l);
      buf_l = ::libs::helpers::mem::move_cptr( buf_l,  leak_bytes);
    }

    RGB2L_PREFIX(16);
    S1PLIT_RGB24_AVX2_DEFINE_REGS;

    _mm256_zeroall();

    __m256i ir8  = _mm256_setzero_si256();
    __m256i ig8  = _mm256_setzero_si256();
    __m256i ib8  = _mm256_setzero_si256();

    for( std::uint32_t indxy = 0; indxy < height; ++indxy )
    {
      for( std::uint32_t indxx = 0; indxx < width; indxx+= ppc )
      {
        __m256i i256_1 = _mm256_loadu_si256( ::libs::helpers::casts::reinterpret_cast_helper<const __m256i*>( rgb24 ) ); //BOG0R0 B1G1R1 B2G2R2 B3G3R3 B4G4R4 B5G5R5 B6G6R6 B7G7R7

        SPLIT_RGB24_AVX2( i256_1, ir8, ig8, ib8 );

        rgb24+= 6;

        //float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
        __m256i var_min = ir8;
        var_min = _mm256_min_epi32( ig8, var_min );
        var_min = _mm256_min_epi32( ib8, var_min );

        //float max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
        __m256i max = _mm256_max_epi32( ig8, ir8 );
        max = _mm256_max_epi32( ib8, max );

        //max_min = max + var_Min;
        __m256i max_min = _mm256_add_epi32( var_min, max );

        //L = ( max + var_Min ) / 2.0F;
        __m256i l8 = _mm256_srai_epi32( max_min, 1 );

        //converting from float HSL to word HSL and saved to bufs
        __m256i l8_2 = _mm256_permute2f128_si256( l8, l8, 1 );
        l8 = _mm256_packs_epi32( l8, l8_2 );
        _mm256_storeu_si256( ::libs::helpers::casts::reinterpret_cast_helper<__m256i*>( l), l8 );

        l+= 8;
      }

      rgb24 = ::libs::helpers::mem::move_cptr( rgb24, leak_rgb );
      l = ::libs::helpers::mem::move_ptr( l, leak_hsl );
    }

    _mm256_zeroupper();
#    endif
#  endif
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb2

#endif
