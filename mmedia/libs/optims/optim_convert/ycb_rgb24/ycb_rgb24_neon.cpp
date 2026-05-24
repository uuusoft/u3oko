/**
\file       ycb_rgb24_neon.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       30.07.2018
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "ycb_rgb24.hpp"
#include "ycb_rgb24_int.hpp"

#if defined(U3_CPU_ARM)

namespace libs::optim::convert::ycb_rgb24
{
void
neon (::libs::optim::io::MCallInfo& info)
{
#  if 1
  return alu (info);
#  else
  YCB2RGB24_PREFIX;

  U3_MARK_UNUSED_HERE (yuy2_buf);
  U3_MARK_UNUSED_HERE (rgb24_buf);
  U3_MARK_UNUSED_HERE (height);

  int16x8_t const_16  = vdupq_n_s16 (16);
  int16x8_t const_128 = vdupq_n_s16 (128);

  const int mem_consts_red_uv[4] = { 0, 6537, 0, 6537 };
  int32x4_t consts_red_uv        = vld1q_s32 (mem_consts_red_uv);
  const int mem_consts_red_vu[4] = { 6537, 0, 6537, 0 };
  int32x4_t consts_red_vu        = vld1q_s32 (mem_consts_red_vu);

  const int mem_consts_green_uv[4] = { -1605, -3330, -1605, -3300 };
  int32x4_t consts_green_uv        = vld1q_s32 (mem_consts_green_uv);
  const int mem_consts_green_vu[4] = { -3330, -1605, -3330, -1605 };
  int32x4_t consts_green_vu        = vld1q_s32 (mem_consts_green_vu);

  const int mem_consts_blue_uv[4] = { 8391, 0, 8391, 0 };
  int32x4_t consts_blue_uv        = vld1q_s32 (mem_consts_blue_uv);
  const int mem_consts_blue_vu[4] = { 0, 8391, 0, 8391 };
  int32x4_t consts_blue_vu        = vld1q_s32 (mem_consts_blue_vu);

  int32x4_t   consts_4769 = vdupq_n_s32 (4769);
  uint8x8x2_t y_vu;
  uint8x8_t   vu8;
  int16x8_t   y16;
  int16x8_t   vu16;
  int16x8_t   uv16;
  uint8x8x3_t vrgb24;

  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += 8)
    {
      y_vu = vld2_u8 (yuy2_buf);
      vu8  = vrev16_u8 (y_vu.val[1]);
      y16  = vreinterpretq_s16_u16 (vmovl_u8 (y_vu.val[0]));
      vu16 = vreinterpretq_s16_u16 (vmovl_u8 (vu8));
      uv16 = vreinterpretq_s16_u16 (vmovl_u8 (y_vu.val[1]));

      const int32x4_t y32_low         = vsubl_s16 (vget_low_s16 (y16), vget_low_s16 (const_16));
      const int32x4_t y32_high        = vsubl_s16 (vget_high_s16 (y16), vget_high_s16 (const_16));
      const int32x4_t vu32_low        = vsubl_s16 (vget_low_s16 (vu16), vget_low_s16 (const_128));
      const int32x4_t vu32_high       = vsubl_s16 (vget_high_s16 (vu16), vget_high_s16 (const_128));
      const int32x4_t uv32_low        = vsubl_s16 (vget_low_s16 (uv16), vget_low_s16 (const_128));
      const int32x4_t uv32_high       = vsubl_s16 (vget_high_s16 (uv16), vget_high_s16 (const_128));
      const int32x4_t y32_premul_low  = vmulq_s32 (y32_low, consts_4769);
      const int32x4_t y32_premul_high = vmulq_s32 (y32_high, consts_4769);

      // red
      int32x4_t akk32_low  = vmlaq_s32 (y32_premul_low, vu32_low, consts_red_vu);
      int32x4_t akk32_high = vmlaq_s32 (y32_premul_high, vu32_high, consts_red_vu);

      akk32_low  = vmlaq_s32 (akk32_low, uv32_low, consts_red_uv);
      akk32_high = vmlaq_s32 (akk32_high, uv32_high, consts_red_uv);

      akk32_low  = vshrq_n_s32 (akk32_low, 12);
      akk32_high = vshrq_n_s32 (akk32_high, 12);

      uint16x4_t akk16_low  = vqmovun_s32 (akk32_low);
      uint16x4_t akk16_high = vqmovun_s32 (akk32_high);

      vrgb24.val[2] = vqmovn_u16 (vcombine_u16 (akk16_low, akk16_high));
      // vrgb24.val[2]  = vdup_n_u8(255 );//debug

      // green
      akk32_low  = vmlaq_s32 (y32_premul_low, vu32_low, consts_green_vu);
      akk32_high = vmlaq_s32 (y32_premul_high, vu32_high, consts_green_vu);
      akk32_low  = vmlaq_s32 (akk32_low, uv32_low, consts_green_uv);
      akk32_high = vmlaq_s32 (akk32_high, uv32_high, consts_green_uv);

      akk32_low  = vshrq_n_s32 (akk32_low, 12);
      akk32_high = vshrq_n_s32 (akk32_high, 12);

      akk16_low  = vqmovun_s32 (akk32_low);
      akk16_high = vqmovun_s32 (akk32_high);

      vrgb24.val[1] = vqmovn_u16 (vcombine_u16 (akk16_low, akk16_high));
      // vrgb24.val[1]  = vdup_n_u8(0);//debug

      // blue
      akk32_low  = vmlaq_s32 (y32_premul_low, vu32_low, consts_blue_vu);
      akk32_high = vmlaq_s32 (y32_premul_high, vu32_high, consts_blue_vu);
      akk32_low  = vmlaq_s32 (akk32_low, uv32_low, consts_blue_uv);
      akk32_high = vmlaq_s32 (akk32_high, uv32_high, consts_blue_uv);

      akk32_low  = vshrq_n_s32 (akk32_low, 12);
      akk32_high = vshrq_n_s32 (akk32_high, 12);

      akk16_low  = vqmovun_s32 (akk32_low);
      akk16_high = vqmovun_s32 (akk32_high);

      vrgb24.val[0] = vqmovn_u16 (vcombine_u16 (akk16_low, akk16_high));
      // vrgb24.val[0]  = vdup_n_u8(0);//debug

      // store
      vst3_u8 (rgb24_buf, vrgb24);

      yuy2_buf += 16;
      rgb24_buf += 24;
    }

    yuy2_buf += leak_yuy2;
    rgb24_buf += leak_rgb24;
  }
#  endif
}
}   // namespace libs::optim::convert::ycb_rgb24

#endif
