//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    27.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
*\brief     Набор функция для конвертации HSL <---> RGB16
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

#if defined(UUU_CPU_X86) && !defined(UUU_CPU_X86_64)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

UUU_SET_TARGET_CPU (sse)
void
hsl_to_rgb24_sse1 (::libs::optim::MCallInfo& _info)
{
  HSL2RGB_PREFIX (4);

  const __m128 _const_1        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1[0]);
  const __m128 _const_2        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d2[0]);
  const __m128 _const_3        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d3[0]);
  const __m128 _const_6        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d6[0]);
  const __m128 _const_255      = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d255[0]);
  const __m128 _const_1_to_2   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_2[0]);
  const __m128 _const_1_to_3   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_3[0]);
  const __m128 _const_1_to_255 = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_255[0]);
  const __m128 _const_2_to_3   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d2_to_3[0]);

  __m128 _temph = _mm_setzero_ps ();
  __m128 _temps = _mm_setzero_ps ();
  __m128 _templ = _mm_setzero_ps ();

  __m128 _temp_r = _mm_setzero_ps ();
  __m128 _temp_g = _mm_setzero_ps ();
  __m128 _temp_b = _mm_setzero_ps ();

  __m128 var_1 = _mm_setzero_ps ();
  __m128 var_2 = _mm_setzero_ps ();

  __m64 _mm0;
  __m64 _mm1;
  __m64 _mm5;
  __m64 _mm6;
  __m64 _mm7;

  __m128 _xmm0;
  __m128 _xmm1;
  __m128 _xmm2;
  __m128 _xmm3;
  __m128 _xmm4;
  __m128 _xmm5;
  __m128 _xmm6;
  __m128 _xmm7;


#define Hue_2_RGB_SSE(_out_reg)                                                             \
  /*if ( vH < 0 ) vH+= 1.0f*/                                                               \
  _xmm7 = _const_1;                                                                         \
  _xmm6 = _mm_setzero_ps ();                                                                \
  _xmm5 = _xmm1;                                                                            \
  _xmm5 = _mm_cmplt_ps (_xmm5, _xmm6);                                                      \
  _xmm4 = _xmm7;                                                                            \
  _xmm4 = _mm_and_ps (_xmm4, _xmm5);                                                        \
  _xmm1 = _mm_add_ps (_xmm1, _xmm4);                                                        \
  /*if ( vH > 1 ) vH-= 1.0f*/                                                               \
  _xmm4 = _xmm7;                                                                            \
  _xmm4 = _mm_cmplt_ps (_xmm4, _xmm1);                                                      \
  _xmm4 = _mm_and_ps (_xmm4, _xmm7);                                                        \
  _xmm1 = _mm_sub_ps (_xmm1, _xmm4);                                                        \
  /*;return v1;*/                                                                           \
  _out_reg = _xmm2;                                                                         \
  /*;if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6.0f );*/ \
  _xmm7    = _const_2_to_3;                                                                 \
  _xmm7    = _mm_sub_ps (_xmm7, _xmm1);                                                     \
  _xmm6    = _xmm3;                                                                         \
  _xmm6    = _mm_sub_ps (_xmm6, _xmm2);                                                     \
  _xmm6    = _mm_mul_ps (_xmm6, _xmm7);                                                     \
  _xmm7    = _const_6;                                                                      \
  _xmm6    = _mm_mul_ps (_xmm6, _xmm7);                                                     \
  _xmm6    = _mm_add_ps (_xmm6, _xmm2);                                                     \
  _xmm7    = _const_3;                                                                      \
  _xmm7    = _mm_mul_ps (_xmm7, _xmm1);                                                     \
  _xmm5    = _const_2;                                                                      \
  _xmm7    = _mm_cmplt_ps (_xmm7, _xmm5);                                                   \
  _xmm6    = _mm_and_ps (_xmm6, _xmm7);                                                     \
  _xmm7    = _mm_andnot_ps (_xmm7, _out_reg);                                               \
  _xmm7    = _mm_or_ps (_xmm7, _xmm6);                                                      \
  _out_reg = _xmm7;                                                                         \
  /*;if ( ( 2 * vH ) < 1 ) return ( v2 );*/                                                 \
  _xmm7    = _const_2;                                                                      \
  _xmm7    = _mm_mul_ps (_xmm7, _xmm1);                                                     \
  _xmm6    = _const_1;                                                                      \
  _xmm7    = _mm_cmplt_ps (_xmm7, _xmm6);                                                   \
  _xmm5    = _xmm3;                                                                         \
  _xmm5    = _mm_and_ps (_xmm5, _xmm7);                                                     \
  _xmm7    = _mm_andnot_ps (_xmm7, _out_reg);                                               \
  _xmm7    = _mm_or_ps (_xmm7, _xmm5);                                                      \
  _out_reg = _xmm7;                                                                         \
  /*;if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6.0f * vH );*/                       \
  _xmm7    = _xmm3;                                                                         \
  _xmm7    = _mm_sub_ps (_xmm7, _xmm2);                                                     \
  _xmm6    = _const_6;                                                                      \
  _xmm7    = _mm_mul_ps (_xmm7, _xmm6);                                                     \
  _xmm7    = _mm_mul_ps (_xmm7, _xmm1);                                                     \
  _xmm7    = _mm_add_ps (_xmm7, _xmm2);                                                     \
  _xmm6    = _mm_mul_ps (_xmm6, _xmm1);                                                     \
  _xmm5    = _const_1;                                                                      \
  _xmm6    = _mm_cmplt_ps (_xmm6, _xmm5);                                                   \
  _xmm7    = _mm_and_ps (_xmm7, _xmm6);                                                     \
  _xmm6    = _mm_andnot_ps (_xmm6, _out_reg);                                               \
  _xmm7    = _mm_or_ps (_xmm7, _xmm6);                                                      \
  _out_reg = _xmm7;


#define FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE(_src, _dst) \
  _dst  = _src;                                               \
  _xmm3 = _xmm0;                                              \
  _xmm3 = _mm_and_ps (_xmm3, _xmm1);                          \
  _xmm4 = _xmm1;                                              \
  _xmm4 = _mm_andnot_ps (_xmm4, _dst);                        \
  _xmm4 = _mm_or_ps (_xmm4, _xmm3);                           \
  _dst  = _xmm4;                                              \
  _dst  = _mm_mul_ps (_dst, _const_255);


#define CONVERT_FLOAT_2_WORD_SSE(_src, _dst) \
  _dst = _mm_cvt_ps2pi (_src);               \
  _src = _mm_movehl_ps (_src, _src);         \
  _mm0 = _mm_cvt_ps2pi (_src);               \
  _dst = _m_packssdw (_dst, _mm0);


  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          //load 4 unsigned short and convert to double word;
          __m64 _mm2 = _mm_setzero_si64 ();

          _mm0 = _mm_set_pi32 (*UUU_MEM_CAST<const int*> (_h + 2), *UUU_MEM_CAST<const int*> (_h + 0));
          _mm1 = _mm0;
          FAST_MOVE_CPTR (_h, 8);
          _mm0   = _m_punpcklwd (_mm0, _mm2);
          _mm1   = _m_punpckhwd (_mm1, _mm2);
          _temph = _mm_setzero_ps ();
          _temph = _mm_cvt_pi2ps (_temph, _mm1);
          _temph = _mm_movelh_ps (_temph, _temph);
          _temph = _mm_cvt_pi2ps (_temph, _mm0);
          _temph = _mm_mul_ps (_temph, _const_1_to_255);

          _mm0 = _mm_set_pi32 (*UUU_MEM_CAST<const int*> (_s + 2), *UUU_MEM_CAST<const int*> (_s + 0));
          _mm1 = _mm0;
          FAST_MOVE_CPTR (_s, 8);
          _mm0   = _m_punpcklwd (_mm0, _mm2);
          _mm1   = _m_punpckhwd (_mm1, _mm2);
          _temps = _mm_cvt_pi2ps (_temps, _mm1);
          _temps = _mm_movelh_ps (_temps, _temps);
          _temps = _mm_cvt_pi2ps (_temps, _mm0);
          _temps = _mm_mul_ps (_temps, _const_1_to_255);

          _mm0 = _mm_set_pi32 (*UUU_MEM_CAST<const int*> (_l + 2), *UUU_MEM_CAST<const int*> (_l + 0));
          _mm1 = _mm0;
          FAST_MOVE_CPTR (_l, 8);
          _mm0   = _m_punpcklwd (_mm0, _mm2);
          _mm1   = _m_punpckhwd (_mm1, _mm2);
          _templ = _mm_cvt_pi2ps (_templ, _mm1);
          _templ = _mm_movelh_ps (_templ, _templ);
          _templ = _mm_cvt_pi2ps (_templ, _mm0);
          _templ = _mm_mul_ps (_templ, _const_1_to_255);

          //if( L < 0.5f ) var_2 = L * ( 1 + S );
          //else           var_2 = ( L + S ) - ( S * L )
          _xmm1 = _temps;
          _xmm2 = _mm_mul_ps (_templ, _xmm1);
          _xmm3 = _templ;
          _xmm3 = _mm_add_ps (_xmm3, _xmm2);
          _xmm4 = _templ;
          _xmm4 = _mm_add_ps (_xmm4, _xmm1);
          _xmm4 = _mm_sub_ps (_xmm4, _xmm2);
          _xmm6 = _templ;
          _xmm6 = _mm_cmplt_ps (_xmm6, _const_1_to_2);
          _xmm3 = _mm_and_ps (_xmm3, _xmm6);
          _xmm6 = _mm_andnot_ps (_xmm6, _xmm4);
          _xmm3 = _mm_or_ps (_xmm3, _xmm6);
          var_2 = _xmm3;

          //float var_1 = 2 * L - var_2;
          //lea eax, _2_vals;
          _xmm0 = _mm_mul_ps (_templ, _const_2);
          _xmm0 = _mm_sub_ps (_xmm0, _xmm3);
          var_1 = _xmm0;

          //float var_3 = H + ( 1.0f / 3.0f );
          _xmm0 = _const_1_to_3;
          _xmm0 = _mm_add_ps (_const_1_to_3, _temph);

          //R = Hue_2_RGB( var_1, var_2, var_3 );
          //load input arguments
          _xmm1 = _xmm0;
          _xmm2 = var_1;
          _xmm3 = var_2;

          Hue_2_RGB_SSE (_temp_r);

          //var_3 = H;
          _xmm1 = _temph;

          //G =  Hue_2_RGB( var_1, var_2, var_3 );
          Hue_2_RGB_SSE (_temp_g);

          //var_3 = H - ( 1.0f / 3.0f );
          _xmm1 = _mm_sub_ps (_temph, _const_1_to_3);

          //B =  Hue_2_RGB( var_1, var_2, var_3 );
          Hue_2_RGB_SSE (_temp_b);

          //if( S == 0.0f )               //HSL values = 0 ? 1
          //{
          //  R = L;                      //RGB results = 0 ? 255
          //  G = L;
          //  B = L;
          //}
          _xmm0 = _mm_setzero_ps ();
          _xmm1 = _mm_cmpeq_ps (_temps, _xmm0);
          _xmm0 = _templ;

          FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE (_temp_r, _xmm7);
          FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE (_temp_g, _xmm6);
          FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE (_temp_b, _xmm5);

          //convert result ro rgb24
          CONVERT_FLOAT_2_WORD_SSE (_xmm7, _mm7);
          CONVERT_FLOAT_2_WORD_SSE (_xmm6, _mm6);
          CONVERT_FLOAT_2_WORD_SSE (_xmm5, _mm5);

#if defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)
          //pextrw eax, mm5, 0;//B0
          int _b0 = _mm_extract_pi16 (_mm5, 0);
          //mov[esi + 0], al;
          _rgb24[0] = _b0;
          //pextrw eax, mm6, 0;//G0
          int _g0 = _mm_extract_pi16 (_mm6, 0);
          //mov[esi + 1], al;
          _rgb24[1] = _g0;
          //pextrw eax, mm7, 0;//R0
          int _r0 = _mm_extract_pi16 (_mm7, 0);
          //mov[esi + 2], al;
          _rgb24[2] = _r0;

          //pextrw eax, mm5, 1;//B1
          _b0 = _mm_extract_pi16 (_mm5, 1);
          //mov[esi + 3], al;
          _rgb24[3] = _b0;
          //pextrw eax, mm6, 1;//G1
          _g0 = _mm_extract_pi16 (_mm6, 1);
          //mov[esi + 4], al;
          _rgb24[4] = _g0;
          //pextrw eax, mm7, 1;//R1
          _r0 = _mm_extract_pi16 (_mm7, 1);
          //mov[esi + 5], al;
          _rgb24[5] = _r0;

          //pextrw eax, mm5, 2;//B2
          _b0 = _mm_extract_pi16 (_mm5, 2);
          //mov[esi + 6], al;
          _rgb24[6] = _b0;
          //pextrw eax, mm6, 2;//G2
          _g0 = _mm_extract_pi16 (_mm6, 2);
          //mov[esi + 7], al;
          _rgb24[7] = _g0;
          //pextrw eax, mm7, 2;//R2
          _r0 = _mm_extract_pi16 (_mm7, 2);
          //mov[esi + 8], al;
          _rgb24[8] = _r0;

          //pextrw eax, mm5, 3;//B3
          _b0 = _mm_extract_pi16 (_mm5, 3);
          //mov[esi + 9], al;
          _rgb24[9] = _b0;
          //pextrw eax, mm6, 3;//G3
          _g0 = _mm_extract_pi16 (_mm6, 3);
          //mov[esi + 10], al;
          _rgb24[10] = _g0;
          //pextrw eax, mm7, 3;//R3
          _r0 = _mm_extract_pi16 (_mm7, 3);
          //mov[esi + 11], al;
          _rgb24[11] = _r0;
#else
          _rgb24[0] = _mm5.m64_u8[0];
          _rgb24[1] = _mm6.m64_u8[0];
          _rgb24[2] = _mm7.m64_u8[0];

          _rgb24[3] = _mm5.m64_u8[2];
          _rgb24[4] = _mm6.m64_u8[2];
          _rgb24[5] = _mm7.m64_u8[2];

          _rgb24[6] = _mm5.m64_u8[4];
          _rgb24[7] = _mm6.m64_u8[4];
          _rgb24[8] = _mm7.m64_u8[4];

          _rgb24[9]  = _mm5.m64_u8[6];
          _rgb24[10] = _mm6.m64_u8[6];
          _rgb24[11] = _mm7.m64_u8[6];
#endif

          _rgb24 += 12;
        }

      //go next string
      _rgb24 += _leak_rgb24;

      FAST_MOVE_CPTR (_h, _leak_hsl);
      FAST_MOVE_CPTR (_s, _leak_hsl);
      FAST_MOVE_CPTR (_l, _leak_hsl);
    }

  _mm_empty ();
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
