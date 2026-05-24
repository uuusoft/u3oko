/**
\file       hsl2rgb_sse3.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
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
#  define HSL_2_RGB_SSE3(out_reg, var1, var2, var3)                                           \
                                                                                              \
    /*if ( vH < 0 ) vH+= 1.0f*/                                                               \
    temp_6 = const_1;                                                                         \
    temp_5 = _mm_setzero_ps ();                                                               \
    temp_4 = var3;                                                                            \
    temp_4 = _mm_cmplt_ps (temp_4, temp_5);                                                   \
    temp_3 = temp_6;                                                                          \
    temp_3 = _mm_and_ps (temp_3, temp_4);                                                     \
    var3   = _mm_add_ps (var3, temp_3);                                                       \
    /*if ( vH > 1 ) vH-= 1.0f*/                                                               \
    temp_3 = temp_6;                                                                          \
    temp_3 = _mm_cmplt_ps (temp_3, var3);                                                     \
    temp_3 = _mm_and_ps (temp_3, temp_6);                                                     \
    var3   = _mm_sub_ps (var3, temp_3);                                                       \
    /*;return v1;*/                                                                           \
    out_reg = var1;                                                                           \
    /*;if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6.0f );*/ \
    temp_6  = const_2_to_3;                                                                   \
    temp_6  = _mm_sub_ps (temp_6, var3);                                                      \
    temp_5  = var2;                                                                           \
    temp_5  = _mm_sub_ps (temp_5, var1);                                                      \
    temp_5  = _mm_mul_ps (temp_5, temp_6);                                                    \
    temp_6  = const_6;                                                                        \
    temp_5  = _mm_mul_ps (temp_5, temp_6);                                                    \
    temp_5  = _mm_add_ps (temp_5, var1);                                                      \
    temp_6  = const_3;                                                                        \
    temp_6  = _mm_mul_ps (temp_6, var3);                                                      \
    temp_4  = const_2;                                                                        \
    temp_6  = _mm_cmplt_ps (temp_6, temp_4);                                                  \
    temp_5  = _mm_and_ps (temp_5, temp_6);                                                    \
    temp_6  = _mm_andnot_ps (temp_6, out_reg);                                                \
    temp_6  = _mm_or_ps (temp_6, temp_5);                                                     \
    out_reg = temp_6;                                                                         \
    /*;if ( ( 2 * vH ) < 1 ) return ( v2 );*/                                                 \
    temp_6  = const_2;                                                                        \
    temp_6  = _mm_mul_ps (temp_6, var3);                                                      \
    temp_5  = const_1;                                                                        \
    temp_6  = _mm_cmplt_ps (temp_6, temp_5);                                                  \
    temp_4  = var2;                                                                           \
    temp_4  = _mm_and_ps (temp_4, temp_6);                                                    \
    temp_6  = _mm_andnot_ps (temp_6, out_reg);                                                \
    temp_6  = _mm_or_ps (temp_6, temp_4);                                                     \
    out_reg = temp_6;                                                                         \
    /*;if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6.0f * vH );*/                       \
    temp_6  = var2;                                                                           \
    temp_6  = _mm_sub_ps (temp_6, var1);                                                      \
    temp_5  = const_6;                                                                        \
    temp_6  = _mm_mul_ps (temp_6, temp_5);                                                    \
    temp_6  = _mm_mul_ps (temp_6, var3);                                                      \
    temp_6  = _mm_add_ps (temp_6, var1);                                                      \
    temp_5  = _mm_mul_ps (temp_5, var3);                                                      \
    temp_4  = const_1;                                                                        \
    temp_5  = _mm_cmplt_ps (temp_5, temp_4);                                                  \
    temp_6  = _mm_and_ps (temp_6, temp_5);                                                    \
    temp_5  = _mm_andnot_ps (temp_5, out_reg);                                                \
    temp_6  = _mm_or_ps (temp_6, temp_5);                                                     \
    out_reg = temp_6;


U3_SET_TARGET_CPU (sse3)
void
hsl_to_rgb24_sse3 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  hsl_to_rgb24_sse2 (info);
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
