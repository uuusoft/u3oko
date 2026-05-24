/**
\file       hsl2rgb_avx2.cpp
\author    Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create    10.09.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

#if defined(U3_CPU_X86)

#  define HSL_2_RGB_AVX2(out_reg, var1, var2, var3)                                           \
                                                                                              \
    /*if ( vH < 0 ) vH+= 1.0f*/                                                               \
    temp_6 = const_1;                                                                         \
    temp_5 = _mm256_setzero_ps ();                                                            \
    temp_4 = var3;                                                                            \
    temp_4 = _mm256_cmp_ps (temp_4, temp_5, 1);                                               \
    temp_3 = temp_6;                                                                          \
    temp_3 = _mm256_and_ps (temp_3, temp_4);                                                  \
    var3   = _mm256_add_ps (var3, temp_3);                                                    \
    /*if ( vH > 1 ) vH-= 1.0f*/                                                               \
    temp_3 = temp_6;                                                                          \
    temp_3 = _mm256_cmp_ps (temp_3, var3, 1);                                                 \
    temp_3 = _mm256_and_ps (temp_3, temp_6);                                                  \
    var3   = _mm256_sub_ps (var3, temp_3);                                                    \
    /*;return v1;*/                                                                           \
    out_reg = var1;                                                                           \
    /*;if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0f / 3.0f ) - vH ) * 6.0f );*/ \
    temp_6  = const_2_to_3;                                                                   \
    temp_6  = _mm256_sub_ps (temp_6, var3);                                                   \
    temp_5  = var2;                                                                           \
    temp_5  = _mm256_sub_ps (temp_5, var1);                                                   \
    temp_5  = _mm256_mul_ps (temp_5, temp_6);                                                 \
    temp_6  = const_6;                                                                        \
    temp_5  = _mm256_mul_ps (temp_5, temp_6);                                                 \
    temp_5  = _mm256_add_ps (temp_5, var1);                                                   \
    temp_6  = const_3;                                                                        \
    temp_6  = _mm256_mul_ps (temp_6, var3);                                                   \
    temp_4  = const_2;                                                                        \
    temp_6  = _mm256_cmp_ps (temp_6, temp_4, 1);                                              \
    temp_5  = _mm256_and_ps (temp_5, temp_6);                                                 \
    temp_6  = _mm256_andnot_ps (temp_6, out_reg);                                             \
    temp_6  = _mm256_or_ps (temp_6, temp_5);                                                  \
    out_reg = temp_6;                                                                         \
    /*;if ( ( 2 * vH ) < 1 ) return ( v2 );*/                                                 \
    temp_6  = const_2;                                                                        \
    temp_6  = _mm256_mul_ps (temp_6, var3);                                                   \
    temp_5  = const_1;                                                                        \
    temp_6  = _mm256_cmp_ps (temp_6, temp_5, 1);                                              \
    temp_4  = var2;                                                                           \
    temp_4  = _mm256_and_ps (temp_4, temp_6);                                                 \
    temp_6  = _mm256_andnot_ps (temp_6, out_reg);                                             \
    temp_6  = _mm256_or_ps (temp_6, temp_4);                                                  \
    out_reg = temp_6;                                                                         \
    /*;if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6.0f * vH );*/                       \
    temp_6  = var2;                                                                           \
    temp_6  = _mm256_sub_ps (temp_6, var1);                                                   \
    temp_5  = const_6;                                                                        \
    temp_6  = _mm256_mul_ps (temp_6, temp_5);                                                 \
    temp_6  = _mm256_mul_ps (temp_6, var3);                                                   \
    temp_6  = _mm256_add_ps (temp_6, var1);                                                   \
    temp_5  = _mm256_mul_ps (temp_5, var3);                                                   \
    temp_4  = const_1;                                                                        \
    temp_5  = _mm256_cmp_ps (temp_5, temp_4, 1);                                              \
    temp_6  = _mm256_and_ps (temp_6, temp_5);                                                 \
    temp_5  = _mm256_andnot_ps (temp_5, out_reg);                                             \
    temp_6  = _mm256_or_ps (temp_6, temp_5);                                                  \
    out_reg = temp_6;

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
U3_SET_TARGET_CPU (avx2)
void
hsl_to_rgb24_avx2 (::libs::optim::io::MCallInfo& info)
{
  HSL2RGB_PREFIX (8);
  // U3_XLOG_DEV ("count_threads_=" << info.count_threads_ << " indx_thread_=" << info.indx_thread_ << " width=" << width << " height=" << height);
  _mm256_zeroall ();

  const __m256 const_0        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d0);
  const __m256 const_1        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1);
  const __m256 const_2        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d2);
  const __m256 const_3        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d3);
  const __m256 const_6        = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d6);
  const __m256 const_255      = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d255);
  const __m256 const_1_to_2   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_2);
  const __m256 const_1_to_3   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_3);
  const __m256 const_1_to_255 = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d1_to_255);
  const __m256 const_2_to_3   = _mm256_broadcast_ss (::libs::optim::s16bit::consts::f_all_d2_to_3);

  __m256 temph = _mm256_setzero_ps ();
  __m256 temps = _mm256_setzero_ps ();
  __m256 templ = _mm256_setzero_ps ();

  __m256 temp_r = _mm256_setzero_ps ();
  __m256 temp_g = _mm256_setzero_ps ();
  __m256 temp_b = _mm256_setzero_ps ();

  __m256 var1 = _mm256_setzero_ps ();
  __m256 var2 = _mm256_setzero_ps ();
  __m256 var3 = _mm256_setzero_ps ();

  __m256i tempi1 = _mm256_setzero_si256 ();
  __m256i tempi2 = _mm256_setzero_si256 ();
  __m256i outr16 = _mm256_setzero_si256 ();
  __m256i outg16 = _mm256_setzero_si256 ();
  __m256i outb16 = _mm256_setzero_si256 ();

  __m256 temp_3 = _mm256_setzero_ps ();
  __m256 temp_4 = _mm256_setzero_ps ();
  __m256 temp_5 = _mm256_setzero_ps ();
  __m256 temp_6 = _mm256_setzero_ps ();

  const __m256i bg8_shufle      = _mm256_set_epi8 (U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x0F), U3_CAST_UINT8 (0x0E), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x0D), U3_CAST_UINT8 (0x0C), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x0B), U3_CAST_UINT8 (0x0A), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x09), U3_CAST_UINT8 (0x08), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x07), U3_CAST_UINT8 (0x06), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x05), U3_CAST_UINT8 (0x04), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x03), U3_CAST_UINT8 (0x02), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x01), U3_CAST_UINT8 (0x00));
  const __m256i r8_shufle       = _mm256_set_epi8 (U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x07), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x06), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x05), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x04), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x03), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x02), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x01), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x00), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80));
  const __m256i mask_last_block = _mm256_set_epi32 (U3_CAST_UINT32 (0x00), U3_CAST_UINT32 (0x00), U3_CAST_UINT32 (0xFFFFFFFF), U3_CAST_UINT32 (0xFFFFFFFF), U3_CAST_UINT32 (0xFFFFFFFF), U3_CAST_UINT32 (0xFFFFFFFF), U3_CAST_UINT32 (0xFFFFFFFF), U3_CAST_UINT32 (0xFFFFFFFF));

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      // load 8 std::uint16_t and convert to double word;
      tempi1 = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (h));
      U3_FAST_MOVE_CPTR (h, 16);
      tempi1 = _mm256_cvtepi16_epi32 (_mm256_castsi256_si128 (tempi1));
      temph  = _mm256_cvtepi32_ps (tempi1);
      temph  = _mm256_mul_ps (temph, const_1_to_255);

      tempi1 = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (s));
      U3_FAST_MOVE_CPTR (s, 16);
      tempi1 = _mm256_cvtepi16_epi32 (_mm256_castsi256_si128 (tempi1));
      temps  = _mm256_cvtepi32_ps (tempi1);
      temps  = _mm256_mul_ps (temps, const_1_to_255);

      tempi1 = _mm256_lddqu_si256 (U3_CAST_REINTERPRET< const __m256i* > (l));
      U3_FAST_MOVE_CPTR (l, 16);
      tempi1 = _mm256_cvtepi16_epi32 (_mm256_castsi256_si128 (tempi1));
      templ  = _mm256_cvtepi32_ps (tempi1);
      templ  = _mm256_mul_ps (templ, const_1_to_255);

      // if( L < 0.5f ) var_2 = L * ( 1 + S );
      // else           var_2 = ( L + S ) - ( S * L )
      __m256 temp_1 = _mm256_mul_ps (templ, temps);
      __m256 temp_2 = templ;
      temp_2        = _mm256_add_ps (temp_2, temp_1);
      temp_3        = templ;
      temp_3        = _mm256_add_ps (temp_3, temps);
      temp_3        = _mm256_sub_ps (temp_3, temp_1);
      temp_5        = templ;
      temp_5        = _mm256_cmp_ps (temp_5, const_1_to_2, 1);
      temp_2        = _mm256_and_ps (temp_2, temp_5);
      temp_5        = _mm256_andnot_ps (temp_5, temp_3);
      temp_2        = _mm256_or_ps (temp_2, temp_5);
      var2          = temp_2;

      // float var1 = 2 * L - var_2;
      var1 = _mm256_mul_ps (templ, const_2);
      var1 = _mm256_sub_ps (var1, temp_2);

      // float var_3 = H + ( 1.0f / 3.0f );
      var3 = _mm256_add_ps (const_1_to_3, temph);

      // R = Hue_2_RGB( var1, var_2, var_3 );
      // load input arguments
      HSL_2_RGB_AVX2 (temp_r, var1, var2, var3);

      // var_3 = H;
      var3 = temph;

      // G =  Hue_2_RGB( var1, var_2, var_3 );
      HSL_2_RGB_AVX2 (temp_g, var1, var2, var3);

      // var_3 = H - ( 1.0f / 3.0f );
      var3 = _mm256_sub_ps (temph, const_1_to_3);

      // B =  Hue_2_RGB( var1, var_2, var_3 );
      HSL_2_RGB_AVX2 (temp_b, var1, var2, var3);

      // if( S == 0.0f )               //HSL values = 0 ? 1
      //{
      //   R = L;                      //RGB results = 0 ? 255
      //   G = L;
      //   B = L;
      // }
      const __m256 cmp_mask = _mm256_cmp_ps (temps, const_0, 0);


#  define FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_AVX2(reg, cmp_mask) \
                                                                    \
    temp_2 = templ;                                                 \
    temp_2 = _mm256_and_ps (temp_2, cmp_mask);                      \
    temp_3 = cmp_mask;                                              \
    temp_3 = _mm256_andnot_ps (temp_3, reg);                        \
    temp_3 = _mm256_or_ps (temp_3, temp_2);                         \
    reg    = temp_3;                                                \
    reg    = _mm256_mul_ps (reg, const_255);


      FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_AVX2 (temp_r, cmp_mask);
      FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_AVX2 (temp_g, cmp_mask);
      FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_AVX2 (temp_b, cmp_mask);

      // convert result ro rgb24
      tempi1 = _mm256_cvtps_epi32 (temp_r);
      tempi2 = _mm256_permute2x128_si256 (tempi1, tempi1, 1);
      outr16 = _mm256_packs_epi32 (tempi1, tempi2);
      outr16 = _mm256_packus_epi16 (outr16, outr16);

      tempi1 = _mm256_cvtps_epi32 (temp_g);
      tempi2 = _mm256_permute2x128_si256 (tempi1, tempi1, 1);
      outg16 = _mm256_packs_epi32 (tempi1, tempi2);
      outg16 = _mm256_packus_epi16 (outg16, outg16);

      tempi1 = _mm256_cvtps_epi32 (temp_b);
      tempi2 = _mm256_permute2x128_si256 (tempi1, tempi1, 1);
      outb16 = _mm256_packs_epi32 (tempi1, tempi2);
      outb16 = _mm256_packus_epi16 (outb16, outb16);

#  if 0
        //debug
        outb16 = _mm256_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01 );

        outg16 = _mm256_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11 );

        outr16 = _mm256_set_epi8(
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
          0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21 );
#  endif

      __m256i bg8 = _mm256_unpacklo_epi8 (outb16, outg16);              // B0G0B1G1B2G2B3G3B4G4B5G5B6G6B7G7  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
      bg8         = _mm256_permute2f128_si256 (bg8, bg8, 0x00);         // B0G0B1G1B2G2B3G3B4G4B5G5B6G6B7G7  B0G0B1G1B2G2B3G3B4G4B5G5B6G6B7G7
      outr16      = _mm256_permute2f128_si256 (outr16, outr16, 0x00);   // R0R1R2R3R4R5R6R7............... R0R1R2R3R4R5R6R7................
      bg8         = _mm256_shuffle_epi8 (bg8, bg8_shufle);              // B0G0..B1G1..B2G2..B3G3..B4G4..B5  G5..B6G6..B7G7..................
      outr16      = _mm256_shuffle_epi8 (outr16, r8_shufle);            //....R0....R1....R2....R3....R4xx  xxR5xxxxR6xxxxR7................
      bg8         = _mm256_or_si256 (bg8, outr16);                      // B0G0R0B1G1R1B2G2R2B3G3R3B4G4R4B5  G5R5B6G6R6B7G7R7................

      if (indxy == height - 1 && indxx == width - 1 * ppc)
      {
        // последний блок в последней строке сохраняем точно, чтобы не было перезаписи в данные следующего потока
        _mm256_maskstore_pd (U3_CAST_REINTERPRET< double* > (rgb24), mask_last_block, _mm256_castsi256_pd (bg8));
      }
      else
      {
        _mm256_storeu_si256 (U3_CAST_REINTERPRET< __m256i* > (rgb24), bg8);
      }

      rgb24 += 24;
    }

    // go next string
    U3_FAST_MOVE_PTR (rgb24, leak_rgb24);
    U3_FAST_MOVE_CPTR (h, leak_hsl);
    U3_FAST_MOVE_CPTR (s, leak_hsl);
    U3_FAST_MOVE_CPTR (l, leak_hsl);
  }

  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
