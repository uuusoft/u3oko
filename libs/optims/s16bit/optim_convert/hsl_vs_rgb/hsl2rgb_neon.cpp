//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       hsl2rgb_neon.cpp
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

#if defined(UUU_CPU_ARM)

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {

UUU_SET_TARGET_CPU (neon)
void
hsl_to_rgb24_neon (::libs::optim::MCallInfo& _info)
{
  XULOG_TRACE ("hsl_to_rgb24_neon::beg");
  HSL2RGB_PREFIX (8);

  const float32x4_t _const_0        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  const float32x4_t _const_1        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1);
  const float32x4_t _const_2        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d2);
  const float32x4_t _const_3        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d3);
  const float32x4_t _const_6        = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d6);
  const float32x4_t _const_255      = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d255);
  const float32x4_t _const_1_to_2   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d2);
  const float32x4_t _const_1_to_3   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d3);
  const float32x4_t _const_1_to_255 = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d1_to_d255);
  const float32x4_t _const_2_to_3   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d2_to_d3);

  float32x4_t _thue1   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t _tsat1   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t _tlight1 = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t _thue2   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t _tsat2   = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);
  float32x4_t _tlight2 = vdupq_n_f32 (::libs::optim::s16bit::consts::f_d0);

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          {
            int32x4_t _tload32;
            int16x8_t _tload16;

            _tload16 = vld1q_s16 (_h);
            FAST_MOVE_CPTR (_h, 16);

            _tload32 = vmovl_s16 (vget_low_s16 (_tload16));
            _thue1   = vcvtq_f32_s32 (_tload32);
            _thue1   = vmulq_f32 (_thue1, _const_1_to_255);

            _tload32 = vmovl_s16 (vget_high_s16 (_tload16));
            _thue2   = vcvtq_f32_s32 (_tload32);
            _thue2   = vmulq_f32 (_thue2, _const_1_to_255);

            _tload16 = vld1q_s16 (_s);
            FAST_MOVE_CPTR (_s, 16);

            _tload32 = vmovl_s16 (vget_low_s16 (_tload16));
            _tsat1   = vcvtq_f32_s32 (_tload32);
            _tsat1   = vmulq_f32 (_tsat1, _const_1_to_255);

            _tload32 = vmovl_s16 (vget_high_s16 (_tload16));
            _tsat2   = vcvtq_f32_s32 (_tload32);
            _tsat2   = vmulq_f32 (_tsat2, _const_1_to_255);

            _tload16 = vld1q_s16 (_l);
            FAST_MOVE_CPTR (_l, 16);

            _tload32 = vmovl_s16 (vget_low_s16 (_tload16));
            _tlight1 = vcvtq_f32_s32 (_tload32);
            _tlight1 = vmulq_f32 (_tlight1, _const_1_to_255);

            _tload32 = vmovl_s16 (vget_high_s16 (_tload16));
            _tlight2 = vcvtq_f32_s32 (_tload32);
            _tlight2 = vmulq_f32 (_tlight2, _const_1_to_255);
          }


#define HSL_2_RGB_NEON(_mac_res, _mac_var1, _mac_var2, _mac_var3)                   \
                                                                                    \
  /*if ( vH < 0 ) vH+= 1.0f*/                                                       \
  _temp_4i  = vcltq_f32 (_mac_var3, _const_0);                                      \
  _temp_3i  = vandq_u32 (vreinterpretq_u32_f32 (_const_1), _temp_4i);               \
  _mac_var3 = vaddq_f32 (_mac_var3, vreinterpretq_f32_u32 (_temp_3i));              \
  /*if ( vH > 1 ) vH-= 1.0f*/                                                       \
  _temp_3i  = vcltq_f32 (_const_1, _mac_var3);                                      \
  _temp_3i  = vandq_u32 (_temp_3i, vreinterpretq_u32_f32 (_const_1));               \
  _mac_var3 = vsubq_f32 (_mac_var3, vreinterpretq_f32_u32 (_temp_3i));              \
  /*;return v1;*/                                                                   \
  _mac_res = _mac_var1;                                                             \
  /*if ( ( 3 * vH ) < 2 ) return (v1 + (v2-v1 ) * ( ( 2.0f/ 3.0f )- vH) * 6.0f );*/ \
  _temp_6f = vsubq_f32 (_const_2_to_3, _mac_var3);                                  \
  _temp_5f = vsubq_f32 (_mac_var2, _mac_var1);                                      \
  _temp_5f = vmulq_f32 (_temp_5f, _temp_6f);                                        \
  _temp_5f = vmlaq_f32 (_mac_var1, _temp_5f, _const_6);                             \
  _temp_6f = vmulq_f32 (_const_3, _mac_var3);                                       \
  _temp_6i = vcltq_f32 (_temp_6f, _const_2);                                        \
  _temp_5i = vreinterpretq_u32_f32 (_temp_5f);                                      \
  _temp_5i = vandq_u32 (_temp_5i, _temp_6i);                                        \
  _temp_6i = vmvnq_u32 (_temp_6i);                                                  \
  _temp_6i = vandq_u32 (_temp_6i, vreinterpretq_u32_f32 (_mac_res));                \
  _temp_6i = vorrq_u32 (_temp_6i, _temp_5i);                                        \
  _mac_res = vreinterpretq_f32_u32 (_temp_6i);                                      \
  /*;if ( ( 2 * vH ) < 1 ) return ( v2 );*/                                         \
  _temp_6f = vmulq_f32 (_const_2, _mac_var3);                                       \
  _temp_6i = vcltq_f32 (_temp_6f, _const_1);                                        \
  _temp_4i = vandq_u32 (vreinterpretq_u32_f32 (_mac_var2), _temp_6i);               \
  _temp_6i = vmvnq_u32 (_temp_6i);                                                  \
  _temp_6i = vandq_u32 (_temp_6i, vreinterpretq_u32_f32 (_mac_res));                \
  _temp_6i = vorrq_u32 (_temp_6i, _temp_4i);                                        \
  _mac_res = vreinterpretq_f32_u32 (_temp_6i);                                      \
  /*;if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6.0f * vH );*/               \
  _temp_6f = _mac_var2;                                                             \
  _temp_6f = vsubq_f32 (_temp_6f, _mac_var1);                                       \
  _temp_6f = vmulq_f32 (_temp_6f, _const_6);                                        \
  _temp_6f = vmlaq_f32 (_mac_var1, _temp_6f, _mac_var3);                            \
  _temp_5f = vmulq_f32 (_const_6, _mac_var3);                                       \
  _temp_5i = vcltq_f32 (_temp_5f, _const_1);                                        \
  _temp_6i = vandq_u32 (vreinterpretq_u32_f32 (_temp_6f), _temp_5i);                \
  _temp_5i = vmvnq_u32 (_temp_5i);                                                  \
  _temp_5i = vandq_u32 (_temp_5i, vreinterpretq_u32_f32 (_mac_res));                \
  _temp_6i = vorrq_u32 (_temp_6i, _temp_5i);                                        \
  _mac_res = vreinterpretq_f32_u32 (_temp_6i);


#define FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_NEON(_mac_out, _mac_mask, _mac_light) \
                                                                                    \
  _temp_2i = vandq_u32 (vreinterpretq_u32_f32 (_mac_light), _mac_mask);             \
  _temp_3i = vmvnq_u32 (_mac_mask);                                                 \
  _temp_3i = vandq_u32 (_temp_3i, vreinterpretq_u32_f32 (_mac_out));                \
  _temp_3i = vorrq_u32 (_temp_3i, _temp_2i);                                        \
  _mac_out = vmulq_f32 (vreinterpretq_f32_u32 (_temp_3i), _const_255);


#define CONVERT_4_PIXEL(_mac_hue, _mac_sat, _mac_light, _mac_r, _mac_g, _mac_b)           \
                                                                                          \
  /*if( L < 0.5f ) var_2 = L * ( 1 + S ); else var_2 = ( L + S ) - ( S * L ) */           \
  _temp_1f = vmulq_f32 (_mac_light, _mac_sat);                                            \
  _var2    = vaddq_f32 (_mac_light, _temp_1f);                                            \
  _temp_3f = vaddq_f32 (_mac_light, _mac_sat);                                            \
  _temp_3f = vsubq_f32 (_temp_3f, _temp_1f);                                              \
  _temp_5i = vcltq_f32 (_mac_light, _const_1_to_2);                                       \
  _var2    = vreinterpretq_f32_u32 (vandq_u32 (vreinterpretq_u32_f32 (_var2), _temp_5i)); \
  _temp_5i = vmvnq_u32 (_temp_5i);                                                        \
  _temp_5i = vandq_u32 (_temp_5i, vreinterpretq_u32_f32 (_temp_3f));                      \
  _var2    = vreinterpretq_f32_u32 (vorrq_u32 (vreinterpretq_u32_f32 (_var2), _temp_5i)); \
  /*float var1 = 2 * L - var_2; */                                                        \
  _var1 = vmulq_f32 (_mac_light, _const_2);                                               \
  _var1 = vsubq_f32 (_var1, _var2);                                                       \
  /*float var_3 = H + ( 1.0f / 3.0f );  */                                                \
  _var3 = vaddq_f32 (_const_1_to_3, _mac_hue);                                            \
  /*R = Hue_2_RGB( var1, var_2, var_3 );  */                                              \
  HSL_2_RGB_NEON (_mac_r, _var1, _var2, _var3);                                           \
  /*var_3 = H;  */                                                                        \
  _var3 = _mac_hue;                                                                       \
  /*G =  Hue_2_RGB( var1, var_2, var_3 ); */                                              \
  HSL_2_RGB_NEON (_mac_g, _var1, _var2, _var3);                                           \
  /*var_3 = H - ( 1.0f / 3.0f );  */                                                      \
  _var3 = vsubq_f32 (_mac_hue, _const_1_to_3);                                            \
  /*B =  Hue_2_RGB( var1, var_2, var_3 ); */                                              \
  HSL_2_RGB_NEON (_mac_b, _var1, _var2, _var3);                                           \
  /*if( S == 0.0f )                 HSL values = 0 ? 1  */                                \
  /*{ R = L;  G = L;  B = L; }              */                                            \
  _temp_4i = vcleq_f32 (_mac_sat, _const_0);                                              \
                                                                                          \
  FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_NEON (_mac_r, _temp_4i, _mac_light);              \
  FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_NEON (_mac_g, _temp_4i, _mac_light);              \
  FINALL_CHECK_RGB_AND_CONVERT_TO_0_255_NEON (_mac_b, _temp_4i, _mac_light);


          float32x4_t _tr1;
          float32x4_t _tg1;
          float32x4_t _tb1;
          float32x4_t _tr2;
          float32x4_t _tg2;
          float32x4_t _tb2;

          {
            float32x4_t _temp_1f;
            uint32x4_t  _temp_2i;
            float32x4_t _temp_3f;
            uint32x4_t  _temp_3i;
            uint32x4_t  _temp_4i;
            float32x4_t _temp_5f;
            uint32x4_t  _temp_5i;
            float32x4_t _temp_6f;
            uint32x4_t  _temp_6i;
            float32x4_t _var1;
            float32x4_t _var2;
            float32x4_t _var3;

            CONVERT_4_PIXEL (_thue1, _tsat1, _tlight1, _tr1, _tg1, _tb1);
            CONVERT_4_PIXEL (_thue2, _tsat2, _tlight2, _tr2, _tg2, _tb2);
          }

          //convert result ro rgb24
          {
            uint8x8x3_t _out;
            uint32x4_t  _temp32i;
            uint16x4_t  _temp16i1;
            uint32x4_t  _temp32i2;
            uint16x4_t  _temp16i2;

            _temp32i    = vcvtq_u32_f32 (_tr1);
            _temp16i1   = vqmovn_u32 (_temp32i);
            _temp32i2   = vcvtq_u32_f32 (_tr2);
            _temp16i2   = vqmovn_u32 (_temp32i2);
            _out.val[0] = vqmovn_u16 (vcombine_u16 (_temp16i1, _temp16i2));

            _temp32i    = vcvtq_u32_f32 (_tg1);
            _temp16i1   = vqmovn_u32 (_temp32i);
            _temp32i2   = vcvtq_u32_f32 (_tg2);
            _temp16i2   = vqmovn_u32 (_temp32i2);
            _out.val[1] = vqmovn_u16 (vcombine_u16 (_temp16i1, _temp16i2));

            _temp32i    = vcvtq_u32_f32 (_tb1);
            _temp16i1   = vqmovn_u32 (_temp32i);
            _temp32i2   = vcvtq_u32_f32 (_tb2);
            _temp16i2   = vqmovn_u32 (_temp32i2);
            _out.val[2] = vqmovn_u16 (vcombine_u16 (_temp16i1, _temp16i2));

            vst3_u8 (_rgb24, _out);
          }

          _rgb24 += 24;
        }

      //go next string
      FAST_MOVE_PTR (_rgb24, _leak_rgb24);
      FAST_MOVE_CPTR (_h, _leak_hsl);
      FAST_MOVE_CPTR (_s, _leak_hsl);
      FAST_MOVE_CPTR (_l, _leak_hsl);
    }

  XULOG_TRACE ("hsl_to_rgb24_neon::end");
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb

#endif
