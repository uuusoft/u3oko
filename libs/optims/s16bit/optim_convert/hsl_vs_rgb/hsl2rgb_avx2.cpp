//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    10.09.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
*\brief     Набор функция для конвертации HSL <---> RGB16
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

#define HSL_2_RGB_AVX2(_out_reg, _var1, _var2, _var3)                                       \
                                                                                            \
  /*if ( vH < 0 ) vH+= 1.0f*/                                                               \
  _temp_6 = _const_1;                                                                       \
  _temp_5 = _mm256_setzero_ps ();                                                           \
  _temp_4 = _var3;                                                                          \
  _temp_4 = _mm256_cmp_ps (_temp_4, _temp_5, 1);                                            \
  _temp_3 = _temp_6;                                                                        \
  _temp_3 = _mm256_and_ps (_temp_3, _temp_4);                                               \
  _var3   = _mm256_add_ps (_var3, _temp_3);                                                 \
  /*if ( vH > 1 ) vH-= 1.0f*/                                                               \
  _temp_3 = _temp_6;                                                                        \
  _temp_3 = _mm256_cmp_ps (_temp_3, _var3, 1);                                              \
  _temp_3 = _mm256_and_ps (_temp_3, _temp_6);                                               \
  _var3   = _mm256_sub_ps (_var3, _temp_3);                                                 \
  /*;return v1;*/                                                                           \
  _out_reg = _var1;                                                                         \
  /*;if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6.0f );*/ \
  _temp_6  = _const_2_to_3;                                                                 \
  _temp_6  = _mm256_sub_ps (_temp_6, _var3);                                                \
  _temp_5  = _var2;                                                                         \
  _temp_5  = _mm256_sub_ps (_temp_5, _var1);                                                \
  _temp_5  = _mm256_mul_ps (_temp_5, _temp_6);                                              \
  _temp_6  = _const_6;                                                                      \
  _temp_5  = _mm256_mul_ps (_temp_5, _temp_6);                                              \
  _temp_5  = _mm256_add_ps (_temp_5, _var1);                                                \
  _temp_6  = _const_3;                                                                      \
  _temp_6  = _mm256_mul_ps (_temp_6, _var3);                                                \
  _temp_4  = _const_2;                                                                      \
  _temp_6  = _mm256_cmp_ps (_temp_6, _temp_4, 1);                                           \
  _temp_5  = _mm256_and_ps (_temp_5, _temp_6);                                              \
  _temp_6  = _mm256_andnot_ps (_temp_6, _out_reg);                                          \
  _temp_6  = _mm256_or_ps (_temp_6, _temp_5);                                               \
  _out_reg = _temp_6;                                                                       \
  /*;if ( ( 2 * vH ) < 1 ) return ( v2 );*/                                                 \
  _temp_6  = _const_2;                                                                      \
  _temp_6  = _mm256_mul_ps (_temp_6, _var3);                                                \
  _temp_5  = _const_1;                                                                      \
  _temp_6  = _mm256_cmp_ps (_temp_6, _temp_5, 1);                                           \
  _temp_4  = _var2;                                                                         \
  _temp_4  = _mm256_and_ps (_temp_4, _temp_6);                                              \
  _temp_6  = _mm256_andnot_ps (_temp_6, _out_reg);                                          \
  _temp_6  = _mm256_or_ps (_temp_6, _temp_4);                                               \
  _out_reg = _temp_6;                                                                       \
  /*;if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6.0f * vH );*/                       \
  _temp_6  = _var2;                                                                         \
  _temp_6  = _mm256_sub_ps (_temp_6, _var1);                                                \
  _temp_5  = _const_6;                                                                      \
  _temp_6  = _mm256_mul_ps (_temp_6, _temp_5);                                              \
  _temp_6  = _mm256_mul_ps (_temp_6, _var3);                                                \
  _temp_6  = _mm256_add_ps (_temp_6, _var1);                                                \
  _temp_5  = _mm256_mul_ps (_temp_5, _var3);                                                \
  _temp_4  = _const_1;                                                                      \
  _temp_5  = _mm256_cmp_ps (_temp_5, _temp_4, 1);                                           \
  _temp_6  = _mm256_and_ps (_temp_6, _temp_5);                                              \
  _temp_5  = _mm256_andnot_ps (_temp_5, _out_reg);                                          \
  _temp_6  = _mm256_or_ps (_temp_6, _temp_5);                                               \
  _out_reg = _temp_6;


UUU_SET_TARGET_CPU (avx2)
void
hsl_to_rgb24_avx2 (::libs::optim::MCallInfo& _info)
{
  XULOG_TRACE ("hsl_to_rgb24_avx2::beg");
  HSL2RGB_PREFIX (8);

  _mm256_zeroall ();

  const __m256 _const_0        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d0);
  const __m256 _const_1        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1);
  const __m256 _const_2        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d2);
  const __m256 _const_3        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d3);
  const __m256 _const_6        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d6);
  const __m256 _const_255      = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d255);
  const __m256 _const_1_to_2   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_2);
  const __m256 _const_1_to_3   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_3);
  const __m256 _const_1_to_255 = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_255);
  const __m256 _const_2_to_3   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d2_to_3);

  __m256 _temph = _mm256_setzero_ps ();
  __m256 _temps = _mm256_setzero_ps ();
  __m256 _templ = _mm256_setzero_ps ();

  __m256 _temp_r = _mm256_setzero_ps ();
  __m256 _temp_g = _mm256_setzero_ps ();
  __m256 _temp_b = _mm256_setzero_ps ();

  __m256 _var1 = _mm256_setzero_ps ();
  __m256 _var2 = _mm256_setzero_ps ();
  __m256 _var3 = _mm256_setzero_ps ();

  __m256i _tempi1 = _mm256_setzero_si256 ();
  __m256i _tempi2 = _mm256_setzero_si256 ();
  __m256i _outr16 = _mm256_setzero_si256 ();
  __m256i _outg16 = _mm256_setzero_si256 ();
  __m256i _outb16 = _mm256_setzero_si256 ();

  __m256 _temp_3 = _mm256_setzero_ps ();
  __m256 _temp_4 = _mm256_setzero_ps ();
  __m256 _temp_5 = _mm256_setzero_ps ();
  __m256 _temp_6 = _mm256_setzero_ps ();

  const __m256i _bg8_shufle = _mm256_set_epi8 (UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x0F), UUU_ICAST_UCHAR (0x0E), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x0D), UUU_ICAST_UCHAR (0x0C), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x0B), UUU_ICAST_UCHAR (0x0A), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x09), UUU_ICAST_UCHAR (0x08), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x07), UUU_ICAST_UCHAR (0x06), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x05), UUU_ICAST_UCHAR (0x04), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x03), UUU_ICAST_UCHAR (0x02), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x01), UUU_ICAST_UCHAR (0x00));

  const __m256i _r8_shufle = _mm256_set_epi8 (UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x07), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x06), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x05), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x04), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x03), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x02), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x01), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x00), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80));

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          //load 8 unsigned short and convert to double word;
          _tempi1 = _mm256_lddqu_si256 (UUU_MEM_CAST<const __m256i*> (_h));
          FAST_MOVE_CPTR (_h, 16);
          _tempi1 = _mm256_cvtepi16_epi32 (_mm256_castsi256_si128 (_tempi1));
          _temph  = _mm256_cvtepi32_ps (_tempi1);
          _temph  = _mm256_mul_ps (_temph, _const_1_to_255);

          _tempi1 = _mm256_lddqu_si256 (UUU_MEM_CAST<const __m256i*> (_s));
          FAST_MOVE_CPTR (_s, 16);
          _tempi1 = _mm256_cvtepi16_epi32 (_mm256_castsi256_si128 (_tempi1));
          _temps  = _mm256_cvtepi32_ps (_tempi1);
          _temps  = _mm256_mul_ps (_temps, _const_1_to_255);

          _tempi1 = _mm256_lddqu_si256 (UUU_MEM_CAST<const __m256i*> (_l));
          FAST_MOVE_CPTR (_l, 16);
          _tempi1 = _mm256_cvtepi16_epi32 (_mm256_castsi256_si128 (_tempi1));
          _templ  = _mm256_cvtepi32_ps (_tempi1);
          _templ  = _mm256_mul_ps (_templ, _const_1_to_255);

          //if( L < 0.5f ) var_2 = L * ( 1 + S );
          //else           var_2 = ( L + S ) - ( S * L )
          __m256 _temp_1 = _mm256_mul_ps (_templ, _temps);
          __m256 _temp_2 = _templ;
          _temp_2        = _mm256_add_ps (_temp_2, _temp_1);
          _temp_3        = _templ;
          _temp_3        = _mm256_add_ps (_temp_3, _temps);
          _temp_3        = _mm256_sub_ps (_temp_3, _temp_1);
          _temp_5        = _templ;
          _temp_5        = _mm256_cmp_ps (_temp_5, _const_1_to_2, 1);
          _temp_2        = _mm256_and_ps (_temp_2, _temp_5);
          _temp_5        = _mm256_andnot_ps (_temp_5, _temp_3);
          _temp_2        = _mm256_or_ps (_temp_2, _temp_5);
          _var2          = _temp_2;

          //float var1 = 2 * L - var_2;
          _var1 = _mm256_mul_ps (_templ, _const_2);
          _var1 = _mm256_sub_ps (_var1, _temp_2);

          //float var_3 = H + ( 1.0f / 3.0f );
          _var3 = _mm256_add_ps (_const_1_to_3, _temph);

          //R = Hue_2_RGB( var1, var_2, var_3 );
          //load input arguments
          HSL_2_RGB_AVX2 (_temp_r, _var1, _var2, _var3);

          //var_3 = H;
          _var3 = _temph;

          //G =  Hue_2_RGB( var1, var_2, var_3 );
          HSL_2_RGB_AVX2 (_temp_g, _var1, _var2, _var3);

          //var_3 = H - ( 1.0f / 3.0f );
          _var3 = _mm256_sub_ps (_temph, _const_1_to_3);

          //B =  Hue_2_RGB( var1, var_2, var_3 );
          HSL_2_RGB_AVX2 (_temp_b, _var1, _var2, _var3);

          //if( S == 0.0f )               //HSL values = 0 ? 1
          //{
          //  R = L;                      //RGB results = 0 ? 255
          //  G = L;
          //  B = L;
          //}
          const __m256 _cmp_mask = _mm256_cmp_ps (_temps, _const_0, 0);


#define FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_AVX2(_reg, _cmp_mask) \
                                                                    \
  _temp_2 = _templ;                                                 \
  _temp_2 = _mm256_and_ps (_temp_2, _cmp_mask);                     \
  _temp_3 = _cmp_mask;                                              \
  _temp_3 = _mm256_andnot_ps (_temp_3, _reg);                       \
  _temp_3 = _mm256_or_ps (_temp_3, _temp_2);                        \
  _reg    = _temp_3;                                                \
  _reg    = _mm256_mul_ps (_reg, _const_255);


          FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_AVX2 (_temp_r, _cmp_mask);
          FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_AVX2 (_temp_g, _cmp_mask);
          FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_AVX2 (_temp_b, _cmp_mask);

          //convert result ro rgb24
          _tempi1 = _mm256_cvtps_epi32 (_temp_r);
          _tempi2 = _mm256_permute2x128_si256 (_tempi1, _tempi1, 1);
          _outr16 = _mm256_packs_epi32 (_tempi1, _tempi2);
          _outr16 = _mm256_packus_epi16 (_outr16, _outr16);

          _tempi1 = _mm256_cvtps_epi32 (_temp_g);
          _tempi2 = _mm256_permute2x128_si256 (_tempi1, _tempi1, 1);
          _outg16 = _mm256_packs_epi32 (_tempi1, _tempi2);
          _outg16 = _mm256_packus_epi16 (_outg16, _outg16);

          _tempi1 = _mm256_cvtps_epi32 (_temp_b);
          _tempi2 = _mm256_permute2x128_si256 (_tempi1, _tempi1, 1);
          _outb16 = _mm256_packs_epi32 (_tempi1, _tempi2);
          _outb16 = _mm256_packus_epi16 (_outb16, _outb16);

#if 0
        //debug
        _outb16 = _mm256_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01 );

        _outg16 = _mm256_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11 );

        _outr16 = _mm256_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21 );
#endif

          __m256i _bg8 = _mm256_unpacklo_epi8 (_outb16, _outg16);                 //B0G0B1G1B2G2B3G3B4G4B5G5B6G6B7G7  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
          _bg8         = _mm256_permute2f128_si256 (_bg8, _bg8, 0x00);            //B0G0B1G1B2G2B3G3B4G4B5G5B6G6B7G7  B0G0B1G1B2G2B3G3B4G4B5G5B6G6B7G7
          _outr16      = _mm256_permute2f128_si256 (_outr16, _outr16, 0x00);      //R0R1R2R3R4R5R6R7............... R0R1R2R3R4R5R6R7................
          _bg8         = _mm256_shuffle_epi8 (_bg8, _bg8_shufle);                 //B0G0..B1G1..B2G2..B3G3..B4G4..B5  G5..B6G6..B7G7..................
          _outr16      = _mm256_shuffle_epi8 (_outr16, _r8_shufle);               //....R0....R1....R2....R3....R4xx  xxR5xxxxR6xxxxR7................
          _bg8         = _mm256_or_si256 (_bg8, _outr16);                         //B0G0R0B1G1R1B2G2R2B3G3R3B4G4R4B5  G5R5B6G6R6B7G7R7................

          _mm256_storeu_si256 (UUU_MEM_CAST<__m256i*> (_rgb24), _bg8);

          _rgb24 += 24;
        }

      //go next string
      FAST_MOVE_PTR (_rgb24, _leak_rgb24);
      FAST_MOVE_CPTR (_h, _leak_hsl);
      FAST_MOVE_CPTR (_s, _leak_hsl);
      FAST_MOVE_CPTR (_l, _leak_hsl);
    }

  _mm256_zeroupper ();

  XULOG_TRACE ("hsl_to_rgb24_avx2::end");
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
