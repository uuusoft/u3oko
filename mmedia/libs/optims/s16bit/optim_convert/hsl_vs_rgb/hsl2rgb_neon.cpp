/**
\file       hsl2rgb_neon.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "hsl_vs_rgb.hpp"
#include "hsl_to_rgb_int.hpp"

#if defined(U3_CPU_ARM)

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
U3_SET_TARGET_CPU (+simd)
void
hsl_to_rgb24_neon (::libs::optim::io::MCallInfo& info)
{
  HSL2RGB_PREFIX (8);

  const float32x4_t const_0        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  const float32x4_t const_1        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1);
  const float32x4_t const_2        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d2);
  const float32x4_t const_3        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d3);
  const float32x4_t const_6        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d6);
  const float32x4_t const_255      = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d255);
  const float32x4_t const_1_to_2   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d2);
  const float32x4_t const_1_to_3   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d3);
  const float32x4_t const_1_to_255 = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d255);
  const float32x4_t const_2_to_3   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d2_to_d3);

  float32x4_t thue1   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t tsat1   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t tlight1 = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t thue2   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t tsat2   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t tlight2 = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      {
        int32x4_t tload32;
        int16x8_t tload16;

        tload16 = vld1q_s16 (h);
        U3_FAST_MOVE_CPTR (h, 16);

        tload32 = vmovl_s16 (vget_low_s16 (tload16));
        thue1   = vcvtq_f32_s32 (tload32);
        thue1   = vmulq_f32 (thue1, const_1_to_255);

        tload32 = vmovl_s16 (vget_high_s16 (tload16));
        thue2   = vcvtq_f32_s32 (tload32);
        thue2   = vmulq_f32 (thue2, const_1_to_255);

        tload16 = vld1q_s16 (s);
        U3_FAST_MOVE_CPTR (s, 16);

        tload32 = vmovl_s16 (vget_low_s16 (tload16));
        tsat1   = vcvtq_f32_s32 (tload32);
        tsat1   = vmulq_f32 (tsat1, const_1_to_255);

        tload32 = vmovl_s16 (vget_high_s16 (tload16));
        tsat2   = vcvtq_f32_s32 (tload32);
        tsat2   = vmulq_f32 (tsat2, const_1_to_255);

        tload16 = vld1q_s16 (l);
        U3_FAST_MOVE_CPTR (l, 16);

        tload32 = vmovl_s16 (vget_low_s16 (tload16));
        tlight1 = vcvtq_f32_s32 (tload32);
        tlight1 = vmulq_f32 (tlight1, const_1_to_255);

        tload32 = vmovl_s16 (vget_high_s16 (tload16));
        tlight2 = vcvtq_f32_s32 (tload32);
        tlight2 = vmulq_f32 (tlight2, const_1_to_255);
      }


#  define HSL_2_RGB_NEON(mac_res, mac_var1, mac_var2, mac_var3)                       \
                                                                                      \
    /*if ( vH < 0 ) vH+= 1.0f*/                                                       \
    temp_4i  = vcltq_f32 (mac_var3, const_0);                                         \
    temp_3i  = vandq_u32 (vreinterpretq_u32_f32 (const_1), temp_4i);                  \
    mac_var3 = vaddq_f32 (mac_var3, vreinterpretq_f32_u32 (temp_3i));                 \
    /*if ( vH > 1 ) vH-= 1.0f*/                                                       \
    temp_3i  = vcltq_f32 (const_1, mac_var3);                                         \
    temp_3i  = vandq_u32 (temp_3i, vreinterpretq_u32_f32 (const_1));                  \
    mac_var3 = vsubq_f32 (mac_var3, vreinterpretq_f32_u32 (temp_3i));                 \
    /*;return v1;*/                                                                   \
    mac_res = mac_var1;                                                               \
    /*if ( ( 3 * vH ) < 2 ) return (v1 + (v2-v1 ) * ( ( 2.0f/ 3.0f )- vH) * 6.0f );*/ \
    temp_6f = vsubq_f32 (const_2_to_3, mac_var3);                                     \
    temp_5f = vsubq_f32 (mac_var2, mac_var1);                                         \
    temp_5f = vmulq_f32 (temp_5f, temp_6f);                                           \
    temp_5f = vmlaq_f32 (mac_var1, temp_5f, const_6);                                 \
    temp_6f = vmulq_f32 (const_3, mac_var3);                                          \
    temp_6i = vcltq_f32 (temp_6f, const_2);                                           \
    temp_5i = vreinterpretq_u32_f32 (temp_5f);                                        \
    temp_5i = vandq_u32 (temp_5i, temp_6i);                                           \
    temp_6i = vmvnq_u32 (temp_6i);                                                    \
    temp_6i = vandq_u32 (temp_6i, vreinterpretq_u32_f32 (mac_res));                   \
    temp_6i = vorrq_u32 (temp_6i, temp_5i);                                           \
    mac_res = vreinterpretq_f32_u32 (temp_6i);                                        \
    /*;if ( ( 2 * vH ) < 1 ) return ( v2 );*/                                         \
    temp_6f = vmulq_f32 (const_2, mac_var3);                                          \
    temp_6i = vcltq_f32 (temp_6f, const_1);                                           \
    temp_4i = vandq_u32 (vreinterpretq_u32_f32 (mac_var2), temp_6i);                  \
    temp_6i = vmvnq_u32 (temp_6i);                                                    \
    temp_6i = vandq_u32 (temp_6i, vreinterpretq_u32_f32 (mac_res));                   \
    temp_6i = vorrq_u32 (temp_6i, temp_4i);                                           \
    mac_res = vreinterpretq_f32_u32 (temp_6i);                                        \
    /*;if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6.0f * vH );*/               \
    temp_6f = mac_var2;                                                               \
    temp_6f = vsubq_f32 (temp_6f, mac_var1);                                          \
    temp_6f = vmulq_f32 (temp_6f, const_6);                                           \
    temp_6f = vmlaq_f32 (mac_var1, temp_6f, mac_var3);                                \
    temp_5f = vmulq_f32 (const_6, mac_var3);                                          \
    temp_5i = vcltq_f32 (temp_5f, const_1);                                           \
    temp_6i = vandq_u32 (vreinterpretq_u32_f32 (temp_6f), temp_5i);                   \
    temp_5i = vmvnq_u32 (temp_5i);                                                    \
    temp_5i = vandq_u32 (temp_5i, vreinterpretq_u32_f32 (mac_res));                   \
    temp_6i = vorrq_u32 (temp_6i, temp_5i);                                           \
    mac_res = vreinterpretq_f32_u32 (temp_6i);


#  define FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_NEON(mac_out, mac_mask, mac_light) \
                                                                                   \
    temp_2i = vandq_u32 (vreinterpretq_u32_f32 (mac_light), mac_mask);             \
    temp_3i = vmvnq_u32 (mac_mask);                                                \
    temp_3i = vandq_u32 (temp_3i, vreinterpretq_u32_f32 (mac_out));                \
    temp_3i = vorrq_u32 (temp_3i, temp_2i);                                        \
    mac_out = vmulq_f32 (vreinterpretq_f32_u32 (temp_3i), const_255);


#  define CONVERT_4_PIXEL(mac_hue, mac_sat, mac_light, mac_r, mac_g, mac_b)              \
                                                                                         \
    /*if( L < 0.5f ) var_2 = L * ( 1 + S ); else var_2 = ( L + S ) - ( S * L ) */        \
    temp_1f = vmulq_f32 (mac_light, mac_sat);                                            \
    var2    = vaddq_f32 (mac_light, temp_1f);                                            \
    temp_3f = vaddq_f32 (mac_light, mac_sat);                                            \
    temp_3f = vsubq_f32 (temp_3f, temp_1f);                                              \
    temp_5i = vcltq_f32 (mac_light, const_1_to_2);                                       \
    var2    = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (var2), temp_5i)); \
    temp_5i = vmvnq_u32 (temp_5i);                                                       \
    temp_5i = vandq_u32 (temp_5i, vreinterpretq_u32_f32 (temp_3f));                      \
    var2    = vreinterpretq_f32_u32 (vorrq_u32 (vreinterpretq_u32_f32 (var2), temp_5i)); \
    /*float var1 = 2 * L - var_2; */                                                     \
    var1 = vmulq_f32 (mac_light, const_2);                                               \
    var1 = vsubq_f32 (var1, var2);                                                       \
    /*float var_3 = H + ( 1.0f / 3.0f );  */                                             \
    var3 = vaddq_f32 (const_1_to_3, mac_hue);                                            \
    /*R = Hue_2_RGB( var1, var_2, var_3 );  */                                           \
    HSL_2_RGB_NEON (mac_r, var1, var2, var3);                                            \
    /*var_3 = H;  */                                                                     \
    var3 = mac_hue;                                                                      \
    /*G =  Hue_2_RGB( var1, var_2, var_3 ); */                                           \
    HSL_2_RGB_NEON (mac_g, var1, var2, var3);                                            \
    /*var_3 = H - ( 1.0f / 3.0f );  */                                                   \
    var3 = vsubq_f32 (mac_hue, const_1_to_3);                                            \
    /*B =  Hue_2_RGB( var1, var_2, var_3 ); */                                           \
    HSL_2_RGB_NEON (mac_b, var1, var2, var3);                                            \
    /*if( S == 0.0f )                 HSL values = 0 ? 1  */                             \
    /*{ R = L;  G = L;  B = L; }              */                                         \
    temp_4i = vcleq_f32 (mac_sat, const_0);                                              \
                                                                                         \
    FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_NEON (mac_r, temp_4i, mac_light);              \
    FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_NEON (mac_g, temp_4i, mac_light);              \
    FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_NEON (mac_b, temp_4i, mac_light);


      float32x4_t tr1;
      float32x4_t tg1;
      float32x4_t tb1;
      float32x4_t tr2;
      float32x4_t tg2;
      float32x4_t tb2;

      {
        float32x4_t temp_1f;
        uint32x4_t  temp_2i;
        float32x4_t temp_3f;
        uint32x4_t  temp_3i;
        uint32x4_t  temp_4i;
        float32x4_t temp_5f;
        uint32x4_t  temp_5i;
        float32x4_t temp_6f;
        uint32x4_t  temp_6i;
        float32x4_t var1;
        float32x4_t var2;
        float32x4_t var3;

        CONVERT_4_PIXEL (thue1, tsat1, tlight1, tr1, tg1, tb1);
        CONVERT_4_PIXEL (thue2, tsat2, tlight2, tr2, tg2, tb2);
      }

      // convert result ro rgb24
      {
        uint8x8x3_t out;
        uint32x4_t  temp32i;
        uint16x4_t  temp16i1;
        uint32x4_t  temp32i2;
        uint16x4_t  temp16i2;

        temp32i    = vcvtq_u32_f32 (tr1);
        temp16i1   = vqmovn_u32 (temp32i);
        temp32i2   = vcvtq_u32_f32 (tr2);
        temp16i2   = vqmovn_u32 (temp32i2);
        out.val[0] = vqmovn_u16 (vcombine_u16 (temp16i1, temp16i2));

        temp32i    = vcvtq_u32_f32 (tg1);
        temp16i1   = vqmovn_u32 (temp32i);
        temp32i2   = vcvtq_u32_f32 (tg2);
        temp16i2   = vqmovn_u32 (temp32i2);
        out.val[1] = vqmovn_u16 (vcombine_u16 (temp16i1, temp16i2));

        temp32i    = vcvtq_u32_f32 (tb1);
        temp16i1   = vqmovn_u32 (temp32i);
        temp32i2   = vcvtq_u32_f32 (tb2);
        temp16i2   = vqmovn_u32 (temp32i2);
        out.val[2] = vqmovn_u16 (vcombine_u16 (temp16i1, temp16i2));

        vst3_u8 (rgb24, out);
      }

      rgb24 += 24;
    }

    // go next string
    U3_FAST_MOVE_PTR (rgb24, leak_rgb24);
    U3_FAST_MOVE_CPTR (h, leak_hsl);
    U3_FAST_MOVE_CPTR (s, leak_hsl);
    U3_FAST_MOVE_CPTR (l, leak_hsl);
  }
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
