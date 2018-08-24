//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       hsl2rgb_sse3.cpp
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
#include "hsl_to_rgb_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

#define HSL_2_RGB_SSE3(_out_reg, _var1, _var2, _var3)                                       \
                                                                                            \
  /*if ( vH < 0 ) vH+= 1.0f*/                                                               \
  _temp_6 = _const_1;                                                                       \
  _temp_5 = _mm_setzero_ps ();                                                              \
  _temp_4 = _var3;                                                                          \
  _temp_4 = _mm_cmplt_ps (_temp_4, _temp_5);                                                \
  _temp_3 = _temp_6;                                                                        \
  _temp_3 = _mm_and_ps (_temp_3, _temp_4);                                                  \
  _var3   = _mm_add_ps (_var3, _temp_3);                                                    \
  /*if ( vH > 1 ) vH-= 1.0f*/                                                               \
  _temp_3 = _temp_6;                                                                        \
  _temp_3 = _mm_cmplt_ps (_temp_3, _var3);                                                  \
  _temp_3 = _mm_and_ps (_temp_3, _temp_6);                                                  \
  _var3   = _mm_sub_ps (_var3, _temp_3);                                                    \
  /*;return v1;*/                                                                           \
  _out_reg = _var1;                                                                         \
  /*;if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6.0f );*/ \
  _temp_6  = _const_2_to_3;                                                                 \
  _temp_6  = _mm_sub_ps (_temp_6, _var3);                                                   \
  _temp_5  = _var2;                                                                         \
  _temp_5  = _mm_sub_ps (_temp_5, _var1);                                                   \
  _temp_5  = _mm_mul_ps (_temp_5, _temp_6);                                                 \
  _temp_6  = _const_6;                                                                      \
  _temp_5  = _mm_mul_ps (_temp_5, _temp_6);                                                 \
  _temp_5  = _mm_add_ps (_temp_5, _var1);                                                   \
  _temp_6  = _const_3;                                                                      \
  _temp_6  = _mm_mul_ps (_temp_6, _var3);                                                   \
  _temp_4  = _const_2;                                                                      \
  _temp_6  = _mm_cmplt_ps (_temp_6, _temp_4);                                               \
  _temp_5  = _mm_and_ps (_temp_5, _temp_6);                                                 \
  _temp_6  = _mm_andnot_ps (_temp_6, _out_reg);                                             \
  _temp_6  = _mm_or_ps (_temp_6, _temp_5);                                                  \
  _out_reg = _temp_6;                                                                       \
  /*;if ( ( 2 * vH ) < 1 ) return ( v2 );*/                                                 \
  _temp_6  = _const_2;                                                                      \
  _temp_6  = _mm_mul_ps (_temp_6, _var3);                                                   \
  _temp_5  = _const_1;                                                                      \
  _temp_6  = _mm_cmplt_ps (_temp_6, _temp_5);                                               \
  _temp_4  = _var2;                                                                         \
  _temp_4  = _mm_and_ps (_temp_4, _temp_6);                                                 \
  _temp_6  = _mm_andnot_ps (_temp_6, _out_reg);                                             \
  _temp_6  = _mm_or_ps (_temp_6, _temp_4);                                                  \
  _out_reg = _temp_6;                                                                       \
  /*;if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6.0f * vH );*/                       \
  _temp_6  = _var2;                                                                         \
  _temp_6  = _mm_sub_ps (_temp_6, _var1);                                                   \
  _temp_5  = _const_6;                                                                      \
  _temp_6  = _mm_mul_ps (_temp_6, _temp_5);                                                 \
  _temp_6  = _mm_mul_ps (_temp_6, _var3);                                                   \
  _temp_6  = _mm_add_ps (_temp_6, _var1);                                                   \
  _temp_5  = _mm_mul_ps (_temp_5, _var3);                                                   \
  _temp_4  = _const_1;                                                                      \
  _temp_5  = _mm_cmplt_ps (_temp_5, _temp_4);                                               \
  _temp_6  = _mm_and_ps (_temp_6, _temp_5);                                                 \
  _temp_5  = _mm_andnot_ps (_temp_5, _out_reg);                                             \
  _temp_6  = _mm_or_ps (_temp_6, _temp_5);                                                  \
  _out_reg = _temp_6;


UUU_SET_TARGET_CPU (sse3)
void
hsl_to_rgb24_sse3 (::libs::optim::MCallInfo& _info)
{
  UASSERT_SIGNAL_OPTIM;
  hsl_to_rgb24_sse2 (_info);
  return;
#if 0
    XULOG_TRACE( "hsl_to_rgb24_sse3::beg" );

    HSL2RGB_PREFIX( 4 );

    const __m128    _const_0    = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d0[0] );
    const __m128i   _const_i0   = _mm_setzero_si128();
    const __m128    _const_1    = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d1[0] );
    const __m128    _const_2    = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d2[0] );
    const __m128    _const_3    = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d3[0] );
    const __m128    _const_6    = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d6[0] );
    const __m128    _const_255    = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d255[0] );
    const __m128    _const_1_to_2 = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d1_to_2[0] );
    const __m128    _const_1_to_3 = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d1_to_3[0] );
    const __m128    _const_1_to_255 = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d1_to_255[0] );
    const __m128    _const_2_to_3 = _mm_set_ps1( ::libs::optim::s16bit::consts::f_all_d2_to_3[0] );

    __m128        _temph      = _mm_setzero_ps();
    __m128        _temps      = _mm_setzero_ps();
    __m128        _templ      = _mm_setzero_ps();

    __m128        _temp_r     = _mm_setzero_ps();
    __m128        _temp_g     = _mm_setzero_ps();
    __m128        _temp_b     = _mm_setzero_ps();

    __m128        _var1     = _mm_setzero_ps();
    __m128        _var2     = _mm_setzero_ps();
    __m128        _var3     = _mm_setzero_ps();

    __m128i       _tempi1     = _mm_setzero_si128();
    __m128i       _tempi2     = _mm_setzero_si128();
    __m128i       _outr16     = _mm_setzero_si128();
    __m128i       _outg16     = _mm_setzero_si128();
    __m128i       _outb16     = _mm_setzero_si128();

    __m128        _temp_3     = _mm_setzero_ps();
    __m128        _temp_4     = _mm_setzero_ps();
    __m128        _temp_5     = _mm_setzero_ps();
    __m128        _temp_6     = _mm_setzero_ps();

    const unsigned char _filling_x80   = UUU_ICAST_UCHAR(0x80);
    const unsigned char _filling_x00   = UUU_ICAST_UCHAR(0x00);
    const unsigned char _filling_x01   = UUU_ICAST_UCHAR(0x01 );
    const unsigned char _filling_x02   = UUU_ICAST_UCHAR(0x02 );
    const unsigned char _filling_x03   = UUU_ICAST_UCHAR(0x03);
    const unsigned char _filling_x04   = UUU_ICAST_UCHAR(0x04 );
    const unsigned char _filling_x05   = UUU_ICAST_UCHAR(0x05 );
    const unsigned char _filling_x06   = UUU_ICAST_UCHAR(0x06);
    const unsigned char _filling_x07   = UUU_ICAST_UCHAR(0x07);

    const __m128i   _bg8_shufle   = _mm_set_epi8( _filling_x80, _filling_x80, _filling_x80, _filling_x80,
                              _filling_x80, _filling_x07, _filling_x06, _filling_x80,
                              _filling_x05, _filling_x04, _filling_x80, _filling_x03,
                              _filling_x01, _filling_x80, _filling_x01, _filling_x00 );

    const __m128i   _r8_shufle    = _mm_set_epi8( _filling_x80, _filling_x80, _filling_x80, _filling_x80,
                              _filling_x03, _filling_x80, _filling_x80, _filling_x02,
                              _filling_x80, _filling_x80, _filling_x01, _filling_x80,
                              _filling_x80, _filling_x00, _filling_x80, _filling_x80 );

    for( std::size_t _indxy = 0; _indxy < _height; ++_indxy )
    {
      for( std::size_t _indxx = 0; _indxx < _width; _indxx+= _ppc )
      {
#if 0
        //load 8 unsigned short and convert to double word;
        _tempi1 =  _mm_lddqu_si128( UUU_MEM_CAST<const __m128i*>( _h) );
        FAST_MOVE_CPTR( _h, 8 );
        //_tempi1 = _mm_cvtepi16_epi32( _tempi1 );
        _tempi1 = _mm_unpacklo_epi16( _tempi1, _const_i0 );
        _temph  = _mm_cvtepi32_ps( _tempi1 );
        _temph  = _mm_mul_ps( _temph, _const_1_to_255 );

        _tempi1 =  _mm_lddqu_si128( UUU_MEM_CAST<const __m128i*>( _s) );
        FAST_MOVE_CPTR( _s, 8 );
        //_tempi1 = _mm_cvtepi16_epi32( _tempi1 );
        _tempi1 = _mm_unpacklo_epi16( _tempi1, _const_i0 );
        _temps  = _mm_cvtepi32_ps( _tempi1 );
        _temps  = _mm_mul_ps( _temps, _const_1_to_255 );

        _tempi1 =  _mm_lddqu_si128( UUU_MEM_CAST<const __m128i*>( _l) );
        FAST_MOVE_CPTR( _l, 8 );
        //_tempi1 = _mm_cvtepi16_epi32( _tempi1 );
        _tempi1 = _mm_unpacklo_epi16( _tempi1, _const_i0 );
        _templ  = _mm_cvtepi32_ps( _tempi1 );
        _templ  = _mm_mul_ps( _templ, _const_1_to_255 );

        //if( L < 0.5f ) var_2 = L * ( 1 + S );
        //else           var_2 = ( L + S ) - ( S * L )
        __m128 _temp_1 = _mm_mul_ps( _templ, _temps );
        __m128 _temp_2 = _templ;
        _temp_2 = _mm_add_ps( _temp_2, _temp_1 );
        _temp_3 = _templ;
        _temp_3 = _mm_add_ps( _temp_3, _temps );
        _temp_3 = _mm_sub_ps( _temp_3, _temp_1 );
        _temp_5 = _templ;
        _temp_5 = _mm_cmplt_ps( _temp_5, _const_1_to_2 );
        _temp_2 = _mm_and_ps( _temp_2, _temp_5 );
        _temp_5 = _mm_andnot_ps( _temp_5, _temp_3 );
        _temp_2 = _mm_or_ps( _temp_2, _temp_5 );
        _var2 = _temp_2;

        //float var1 = 2 * L - var_2;
        _var1 = _mm_mul_ps( _templ, _const_2 );
        _var1 = _mm_sub_ps( _var1, _temp_2 );

        //float var_3 = H + ( 1.0f / 3.0f );
        _var3 = _mm_add_ps( _const_1_to_3, _temph );

        //R = Hue_2_RGB( var1, var_2, var_3 );
        //load input arguments
        HSL_2_RGB_SSE3( _temp_r, _var1, _var2, _var3 );

        //var_3 = H;
        _var3 = _temph;

        //G =  Hue_2_RGB( var1, var_2, var_3 );
        HSL_2_RGB_SSE3( _temp_g, _var1, _var2, _var3 );

        //var_3 = H - ( 1.0f / 3.0f );
        _var3 = _mm_sub_ps( _temph, _const_1_to_3 );

        //B =  Hue_2_RGB( var1, var_2, var_3 );
        HSL_2_RGB_SSE3( _temp_b, _var1, _var2, _var3 );

        //if( S == 0.0f )               //HSL values = 0 ? 1 
        //{
        //  R = L;                      //RGB results = 0 ? 255
        //  G = L;
        //  B = L;
        //}
        const __m128 _cmp_mask = _mm_cmpeq_ps( _temps, _const_0 );

#define FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE3(_reg, _cmp_mask) \
                                                                    \
  _temp_2 = _templ;                                                 \
  _temp_2 = _mm_and_ps (_temp_2, _cmp_mask);                        \
  _temp_3 = _cmp_mask;                                              \
  _temp_3 = _mm_andnot_ps (_temp_3, _reg);                          \
  _temp_3 = _mm_or_ps (_temp_3, _temp_2);                           \
  _reg    = _temp_3;                                                \
  _reg    = _mm_mul_ps (_reg, _const_255);

        FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE3 ( _temp_r, _cmp_mask );
        FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE3 ( _temp_g, _cmp_mask );
        FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE3 ( _temp_b, _cmp_mask );

        //convert result ro rgb24
        _tempi1 = _mm_cvtps_epi32( _temp_r );
        //_tempi2 = _mm_permute2x128_si128( _tempi1, _tempi1, 0x01 );
        _tempi2 = _mm_shuffle_epi32( _tempi1, 0x44 );   //b01000100=0x44
        _outr16 = _mm_packs_epi32( _tempi1, _tempi2 );
        _outr16 = _mm_packus_epi16( _outr16, _outr16  );

        _tempi1 = _mm_cvtps_epi32( _temp_g );
        //_tempi2 = _mm_permute2x128_si128( _tempi1, _tempi1, 0x01 );
        _tempi2 = _mm_shuffle_epi32( _tempi1, 0x44 );   //b01000100=0x44
        _outg16 = _mm_packs_epi32( _tempi1, _tempi2 );
        _outg16 = _mm_packus_epi16( _outg16, _outg16  );

        _tempi1 = _mm_cvtps_epi32( _temp_b );
        //_tempi2 = _mm_permute2x64_si128( _tempi1, _tempi1, 0x01 );
        _tempi2 = _mm_shuffle_epi32( _tempi1, 0x44 );   //b01000100=0x44
        _outb16 = _mm_packs_epi32( _tempi1, _tempi2 );
        _outb16 = _mm_packus_epi16( _outb16, _outb16  );

#if 0
        //debug
        _outb16 = _mm_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01 );

        _outg16 = _mm_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11 );

        _outr16 = _mm_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21 );
#endif

        __m128i _bg8 = _mm_unpacklo_epi8( _outb16, _outg16 );     //B0G0B1G1B2G2B3G3  xxxxxxxxxxxxxxxx
        _bg8  = _mm_shuffle_epi32( _bg8, 0x44 );            //B0G0B1G1B2G2B3G3  B0G0B1G1B2G2B3G3
        _outr16 = _mm_shuffle_epi32( _outr16, 0x44 );         //R0R1R2R3........  R0R1R2R3........
        _bg8  = _mm_shuffle_epi8( _bg8, _bg8_shufle );        //B0G0..B1G1..B2G2  ..B3G3..........
        _outr16 = _mm_shuffle_epi8( _outr16, _r8_shufle );        //....R0....R1....  R2....R3........
        _bg8  = _mm_or_si128( _bg8, _outr16 );            //B0G0R0B1G1R1B2G2  R2B3G3R3........

        _mm_storeu_si128( UUU_MEM_CAST<__m128i*>( _rgb24 ), _bg8 );
#endif
        _rgb24+= 12;
      }

      //go next string
      FAST_MOVE_PTR( _rgb24, _leak_rgb24 );
      FAST_MOVE_CPTR( _h, _leak_hsl );
      FAST_MOVE_CPTR( _s, _leak_hsl );
      FAST_MOVE_CPTR( _l, _leak_hsl );
    }
        
    XULOG_TRACE( "hsl_to_rgb24_sse3::end" );
    return;
#endif
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
