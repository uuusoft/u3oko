/**
\file
\author    Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create    27.11.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
U3_SET_TARGET_CPU (sse)
void
hsl_to_rgb24_sse1 (::libs::optim::io::MCallInfo& info)
{
  // remove mmx instruction
#  if 1
  U3_ASSERT_TODO_OPTIM;
  hsl_to_rgb24_alu (info);
#  else
  HSL2RGB_PREFIX (4);

  const __m128 const_1        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1[0]);
  const __m128 const_2        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d2[0]);
  const __m128 const_3        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d3[0]);
  const __m128 const_6        = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d6[0]);
  const __m128 const_255      = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d255[0]);
  const __m128 const_1_to_2   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_2[0]);
  const __m128 const_1_to_3   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_3[0]);
  const __m128 const_1_to_255 = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d1_to_255[0]);
  const __m128 const_2_to_3   = _mm_set_ps1 (::libs::optim::s16bit::consts::f_all_d2_to_3[0]);

  __m128 temph = _mm_setzero_ps ();
  __m128 temps = _mm_setzero_ps ();
  __m128 templ = _mm_setzero_ps ();

  __m128 temp_r = _mm_setzero_ps ();
  __m128 temp_g = _mm_setzero_ps ();
  __m128 temp_b = _mm_setzero_ps ();

  __m128 var_1 = _mm_setzero_ps ();
  __m128 var_2 = _mm_setzero_ps ();

  __m64 mm0;
  __m64 mm1;
  __m64 mm5;
  __m64 mm6;
  __m64 mm7;

  __m128 xmm0;
  __m128 xmm1;
  __m128 xmm2;
  __m128 xmm3;
  __m128 xmm4;
  __m128 xmm5;
  __m128 xmm6;
  __m128 xmm7;


#    define Hue_2_RGB_SSE(out_reg)                                                              \
      /*if ( vH < 0 ) vH+= 1.0f*/                                                               \
      xmm7 = const_1;                                                                           \
      xmm6 = _mm_setzero_ps ();                                                                 \
      xmm5 = xmm1;                                                                              \
      xmm5 = _mm_cmplt_ps (xmm5, xmm6);                                                         \
      xmm4 = xmm7;                                                                              \
      xmm4 = _mm_and_ps (xmm4, xmm5);                                                           \
      xmm1 = _mm_add_ps (xmm1, xmm4);                                                           \
      /*if ( vH > 1 ) vH-= 1.0f*/                                                               \
      xmm4 = xmm7;                                                                              \
      xmm4 = _mm_cmplt_ps (xmm4, xmm1);                                                         \
      xmm4 = _mm_and_ps (xmm4, xmm7);                                                           \
      xmm1 = _mm_sub_ps (xmm1, xmm4);                                                           \
      /*;return v1;*/                                                                           \
      out_reg = xmm2;                                                                           \
      /*;if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6.0f );*/ \
      xmm7    = const_2_to_3;                                                                   \
      xmm7    = _mm_sub_ps (xmm7, xmm1);                                                        \
      xmm6    = xmm3;                                                                           \
      xmm6    = _mm_sub_ps (xmm6, xmm2);                                                        \
      xmm6    = _mm_mul_ps (xmm6, xmm7);                                                        \
      xmm7    = const_6;                                                                        \
      xmm6    = _mm_mul_ps (xmm6, xmm7);                                                        \
      xmm6    = _mm_add_ps (xmm6, xmm2);                                                        \
      xmm7    = const_3;                                                                        \
      xmm7    = _mm_mul_ps (xmm7, xmm1);                                                        \
      xmm5    = const_2;                                                                        \
      xmm7    = _mm_cmplt_ps (xmm7, xmm5);                                                      \
      xmm6    = _mm_and_ps (xmm6, xmm7);                                                        \
      xmm7    = _mm_andnot_ps (xmm7, out_reg);                                                  \
      xmm7    = _mm_or_ps (xmm7, xmm6);                                                         \
      out_reg = xmm7;                                                                           \
      /*;if ( ( 2 * vH ) < 1 ) return ( v2 );*/                                                 \
      xmm7    = const_2;                                                                        \
      xmm7    = _mm_mul_ps (xmm7, xmm1);                                                        \
      xmm6    = const_1;                                                                        \
      xmm7    = _mm_cmplt_ps (xmm7, xmm6);                                                      \
      xmm5    = xmm3;                                                                           \
      xmm5    = _mm_and_ps (xmm5, xmm7);                                                        \
      xmm7    = _mm_andnot_ps (xmm7, out_reg);                                                  \
      xmm7    = _mm_or_ps (xmm7, xmm5);                                                         \
      out_reg = xmm7;                                                                           \
      /*;if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6.0f * vH );*/                       \
      xmm7    = xmm3;                                                                           \
      xmm7    = _mm_sub_ps (xmm7, xmm2);                                                        \
      xmm6    = const_6;                                                                        \
      xmm7    = _mm_mul_ps (xmm7, xmm6);                                                        \
      xmm7    = _mm_mul_ps (xmm7, xmm1);                                                        \
      xmm7    = _mm_add_ps (xmm7, xmm2);                                                        \
      xmm6    = _mm_mul_ps (xmm6, xmm1);                                                        \
      xmm5    = const_1;                                                                        \
      xmm6    = _mm_cmplt_ps (xmm6, xmm5);                                                      \
      xmm7    = _mm_and_ps (xmm7, xmm6);                                                        \
      xmm6    = _mm_andnot_ps (xmm6, out_reg);                                                  \
      xmm7    = _mm_or_ps (xmm7, xmm6);                                                         \
      out_reg = xmm7;


#    define FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE(src, dst) \
      dst  = src;                                               \
      xmm3 = xmm0;                                              \
      xmm3 = _mm_and_ps (xmm3, xmm1);                           \
      xmm4 = xmm1;                                              \
      xmm4 = _mm_andnot_ps (xmm4, dst);                         \
      xmm4 = _mm_or_ps (xmm4, xmm3);                            \
      dst  = xmm4;                                              \
      dst  = _mm_mul_ps (dst, const_255);


#    define CONVERT_FLOAT_2_WORD_SSE(src, dst) \
      dst = _mm_cvt_ps2pi (src);               \
      src = _mm_movehl_ps (src, src);          \
      mm0 = _mm_cvt_ps2pi (src);               \
      dst = m_packssdw (dst, mm0);


  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      // load 4 std::uint16_t and convert to double word;
      __m64 mm2 = _mm_setzero_si64 ();

      mm0 = _mm_set_pi32 (*U3_CAST_REINTERPRET< const int* > (h + 2), *U3_CAST_REINTERPRET< const int* > (h + 0));
      mm1 = mm0;
      U3_FAST_MOVE_CPTR (h, 8);
      mm0   = m_punpcklwd (mm0, mm2);
      mm1   = m_punpckhwd (mm1, mm2);
      temph = _mm_setzero_ps ();
      temph = _mm_cvt_pi2ps (temph, mm1);
      temph = _mm_movelh_ps (temph, temph);
      temph = _mm_cvt_pi2ps (temph, mm0);
      temph = _mm_mul_ps (temph, const_1_to_255);

      mm0 = _mm_set_pi32 (*U3_CAST_REINTERPRET< const int* > (s + 2), *U3_CAST_REINTERPRET< const int* > (s + 0));
      mm1 = mm0;
      U3_FAST_MOVE_CPTR (s, 8);
      mm0   = m_punpcklwd (mm0, mm2);
      mm1   = m_punpckhwd (mm1, mm2);
      temps = _mm_cvt_pi2ps (temps, mm1);
      temps = _mm_movelh_ps (temps, temps);
      temps = _mm_cvt_pi2ps (temps, mm0);
      temps = _mm_mul_ps (temps, const_1_to_255);

      mm0 = _mm_set_pi32 (*U3_CAST_REINTERPRET< const int* > (l + 2), *U3_CAST_REINTERPRET< const int* > (l + 0));
      mm1 = mm0;
      U3_FAST_MOVE_CPTR (l, 8);
      mm0   = m_punpcklwd (mm0, mm2);
      mm1   = m_punpckhwd (mm1, mm2);
      templ = _mm_cvt_pi2ps (templ, mm1);
      templ = _mm_movelh_ps (templ, templ);
      templ = _mm_cvt_pi2ps (templ, mm0);
      templ = _mm_mul_ps (templ, const_1_to_255);

      // if( L < 0.5f ) var_2 = L * ( 1 + S );
      // else           var_2 = ( L + S ) - ( S * L )
      xmm1  = temps;
      xmm2  = _mm_mul_ps (templ, xmm1);
      xmm3  = templ;
      xmm3  = _mm_add_ps (xmm3, xmm2);
      xmm4  = templ;
      xmm4  = _mm_add_ps (xmm4, xmm1);
      xmm4  = _mm_sub_ps (xmm4, xmm2);
      xmm6  = templ;
      xmm6  = _mm_cmplt_ps (xmm6, const_1_to_2);
      xmm3  = _mm_and_ps (xmm3, xmm6);
      xmm6  = _mm_andnot_ps (xmm6, xmm4);
      xmm3  = _mm_or_ps (xmm3, xmm6);
      var_2 = xmm3;

      // float var_1 = 2 * L - var_2;
      // lea eax, _2_vals;
      xmm0  = _mm_mul_ps (templ, const_2);
      xmm0  = _mm_sub_ps (xmm0, xmm3);
      var_1 = xmm0;

      // float var_3 = H + ( 1.0f / 3.0f );
      xmm0 = const_1_to_3;
      xmm0 = _mm_add_ps (const_1_to_3, temph);

      // R = Hue_2_RGB( var_1, var_2, var_3 );
      // load input arguments
      xmm1 = xmm0;
      xmm2 = var_1;
      xmm3 = var_2;

      Hue_2_RGB_SSE (temp_r);

      // var_3 = H;
      xmm1 = temph;

      // G =  Hue_2_RGB( var_1, var_2, var_3 );
      Hue_2_RGB_SSE (temp_g);

      // var_3 = H - ( 1.0f / 3.0f );
      xmm1 = _mm_sub_ps (temph, const_1_to_3);

      // B =  Hue_2_RGB( var_1, var_2, var_3 );
      Hue_2_RGB_SSE (temp_b);

      // if( S == 0.0f )               //HSL values = 0 ? 1
      //{
      //   R = L;                      //RGB results = 0 ? 255
      //   G = L;
      //   B = L;
      // }
      xmm0 = _mm_setzero_ps ();
      xmm1 = _mm_cmpeq_ps (temps, xmm0);
      xmm0 = templ;

      FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE (temp_r, xmm7);
      FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE (temp_g, xmm6);
      FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_SSE (temp_b, xmm5);

      // convert result ro rgb24
      CONVERT_FLOAT_2_WORD_SSE (xmm7, mm7);
      CONVERT_FLOAT_2_WORD_SSE (xmm6, mm6);
      CONVERT_FLOAT_2_WORD_SSE (xmm5, mm5);

#    if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
      // pextrw eax, mm5, 0;//B0
      int b0 = _mm_extract_pi16 (mm5, 0);
      // mov[esi + 0], al;
      rgb24[0] = b0;
      // pextrw eax, mm6, 0;//G0
      int g0 = _mm_extract_pi16 (mm6, 0);
      // mov[esi + 1], al;
      rgb24[1] = g0;
      // pextrw eax, mm7, 0;//R0
      int r0 = _mm_extract_pi16 (mm7, 0);
      // mov[esi + 2], al;
      rgb24[2] = r0;

      // pextrw eax, mm5, 1;//B1
      b0 = _mm_extract_pi16 (mm5, 1);
      // mov[esi + 3], al;
      rgb24[3] = b0;
      // pextrw eax, mm6, 1;//G1
      g0 = _mm_extract_pi16 (mm6, 1);
      // mov[esi + 4], al;
      rgb24[4] = g0;
      // pextrw eax, mm7, 1;//R1
      r0 = _mm_extract_pi16 (mm7, 1);
      // mov[esi + 5], al;
      rgb24[5] = r0;

      // pextrw eax, mm5, 2;//B2
      b0 = _mm_extract_pi16 (mm5, 2);
      // mov[esi + 6], al;
      rgb24[6] = b0;
      // pextrw eax, mm6, 2;//G2
      g0 = _mm_extract_pi16 (mm6, 2);
      // mov[esi + 7], al;
      rgb24[7] = g0;
      // pextrw eax, mm7, 2;//R2
      r0 = _mm_extract_pi16 (mm7, 2);
      // mov[esi + 8], al;
      rgb24[8] = r0;

      // pextrw eax, mm5, 3;//B3
      b0 = _mm_extract_pi16 (mm5, 3);
      // mov[esi + 9], al;
      rgb24[9] = b0;
      // pextrw eax, mm6, 3;//G3
      g0 = _mm_extract_pi16 (mm6, 3);
      // mov[esi + 10], al;
      rgb24[10] = g0;
      // pextrw eax, mm7, 3;//R3
      r0 = _mm_extract_pi16 (mm7, 3);
      // mov[esi + 11], al;
      rgb24[11] = r0;
#    else
      rgb24[0] = mm5.m64_u8[0];
      rgb24[1] = mm6.m64_u8[0];
      rgb24[2] = mm7.m64_u8[0];

      rgb24[3] = mm5.m64_u8[2];
      rgb24[4] = mm6.m64_u8[2];
      rgb24[5] = mm7.m64_u8[2];

      rgb24[6] = mm5.m64_u8[4];
      rgb24[7] = mm6.m64_u8[4];
      rgb24[8] = mm7.m64_u8[4];

      rgb24[9]  = mm5.m64_u8[6];
      rgb24[10] = mm6.m64_u8[6];
      rgb24[11] = mm7.m64_u8[6];
#    endif

      rgb24 += 12;
    }

    // go next string
    rgb24 += leak_rgb24;

    U3_FAST_MOVE_CPTR (h, leak_hsl);
    U3_FAST_MOVE_CPTR (s, leak_hsl);
    U3_FAST_MOVE_CPTR (l, leak_hsl);
  }

  _mm_empty ();
#  endif
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
