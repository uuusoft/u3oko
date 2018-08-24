//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       l2rgb_avx2.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb.hpp"
#include "l_to_rgb_int.hpp"
#include "../hsl_vs_rgb/rgb_to_hsl_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace l_vs_rgb {

UUU_SET_TARGET_CPU (avx2)
void
l_to_rgb24_avx2 (::libs::optim::MCallInfo& _info)
{
#if 1
  return l_to_rgb24_alu (_info);
#else

  L2RGB_PREFIX (16);

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          const __m256i _val = _mm256_load_si256 (UUU_MEM_CAST<const __m256i*> (_rgb24));

          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_rgb24 + 0), _val);
          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_rgb24 + 16), _val);
          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_rgb24 + 32), _val);

          _l += 16;
          _rgb24 += 3 * 16;
        }

      FAST_MOVE_PTR (_rgb24, _leak_l);
      FAST_MOVE_CPTR (_l, _leak_l);
    }

  return;

#if 0
    CHECK_CALL( check_l2rgb( _info ), "failde check l2rgb" );

    const std::size_t _width      = _info.srcs_[0].width_;
    const std::size_t _height     = _info.srcs_[0].height_;
    const std::size_t _stride_l   = _info.srcs_[0].stride_;
    const std::size_t _leak_bytes   = _stride_l - _width * sizeof (unsigned short );
    const std::size_t _stride_rgb24 = _width * sizeof (unsigned char) * 3;
    const short*    _buff_l     = _info.srcs_[0].buff();
    unsigned char*    _rgb24      = _info.dsts_[0].ubuff();
    int*        _out_stride   = _info.params_.pints_[0];

    if (0 == *_out_stride )
    {
      *_out_stride = _stride_rgb24;
    }

    const unsigned int  _leak_l   = *_out_stride - _stride_rgb24;
    unsigned char*    _cstring  = _rgb24;

    for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; ++_indxx )
      {
        const unsigned char _val = _buff_l[0];
        _cstring[0] = _val;
        _cstring[1] = _val;
        _cstring[2] = _val;

        _buff_l++;
        _cstring += 3;
      }

      FAST_MOVE_PTR( _cstring,  _leak_l);
      FAST_MOVE_CPTR( _buff_l,  _leak_bytes);
    }





    RGB2L_PREFIX(16);
    S1PLIT_RGB24_AVX2_DEFINE_REGS;

    _mm256_zeroall();

    __m256i _ir8  = _mm256_setzero_si256();
    __m256i _ig8  = _mm256_setzero_si256();
    __m256i _ib8  = _mm256_setzero_si256();

    for( std::size_t _indxy = 0; _indxy < _height; ++_indxy )
    {
      for( std::size_t _indxx = 0; _indxx < _width; _indxx+= _ppc )
      {
        __m256i _i256_1 = _mm256_loadu_si256( UUU_MEM_CAST<const __m256i*>( _rgb24 ) ); //BOG0R0 B1G1R1 B2G2R2 B3G3R3 B4G4R4 B5G5R5 B6G6R6 B7G7R7

        SPLIT_RGB24_AVX2( _i256_1, _ir8, _ig8, _ib8 );

        _rgb24+= 6;

        //float var_Min = min( var_R, min(var_G, var_B) ) Min. value of RGB
        __m256i _var_min = _ir8;
        _var_min = _mm256_min_epi32( _ig8, _var_min );
        _var_min = _mm256_min_epi32( _ib8, _var_min );

        //float _max = max( var_R, max(var_G, var_B) )  //Max. value of RGB
        __m256i _max = _mm256_max_epi32( _ig8, _ir8 );
        _max = _mm256_max_epi32( _ib8, _max );

        //_max_min = _max + var_Min;
        __m256i _max_min = _mm256_add_epi32( _var_min, _max );

        //L = ( _max + var_Min ) / 2.0f;
        __m256i _l8 = _mm256_srai_epi32( _max_min, 1 );

        //converting from float HSL to word HSL and saved to buffers
        __m256i _l8_2 = _mm256_permute2f128_si256( _l8, _l8, 1 );
        _l8 = _mm256_packs_epi32( _l8, _l8_2 );
        _mm256_storeu_si256( UUU_MEM_CAST<__m256i*>( _l), _l8 );

        _l+= 8;
      }

      FAST_MOVE_CPTR( _rgb24, _leak_rgb );
      FAST_MOVE_PTR( _l, _leak_hsl );
    }

    _mm256_zeroupper();

    return;
#endif
#endif
}

}}}}}      // namespace libs::optim::s16bit::convert::l_vs_rgb

#endif
