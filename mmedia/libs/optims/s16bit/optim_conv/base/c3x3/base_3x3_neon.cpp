/**
\file       base_3x3_neon.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.11.2016
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_3x3.hpp"

#ifdef U3_CPU_ARM

namespace libs::optim::s16bit::conv::base::c3x3::consts
{
constexpr std::int32_t pxs_per_cycle = 4;
}

namespace libs::optim::s16bit::conv::base::c3x3
{
struct TNeonCalcObj {
  TNeonCalcObj () = default;

  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
    permute8_low_  = vcreate_s8 (0x0302050403020100LL);
    permute8_high_ = vcreate_s8 (0x0706050407060504LL);

    str1_core_.val[0] = vld1q_s16 (&(**pmask).get (0, 0));
    str2_core_.val[0] = vld1q_s16 (&(**pmask).get (0, 1));
    str3_core_.val[0] = vld1q_s16 (&(**pmask).get (0, 2));

    clone_core_str (str1_core_);
    clone_core_str (str2_core_);
    clone_core_str (str3_core_);
  }

  void
  clone_core_str (int16x8x2_t& str)
  {
    // 1 px
    //-
    // 2 px
    str.val[0] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 0), str.val[0], 3);
    str.val[0] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 1), str.val[0], 4);
    str.val[0] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 2), str.val[0], 5);
    // 3 px
    str.val[0] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 0), str.val[0], 6);
    str.val[0] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 1), str.val[0], 7);
    str.val[1] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 2), str.val[1], 0);
    // 4 px
    str.val[1] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 0), str.val[1], 1);
    str.val[1] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 1), str.val[1], 2);
    str.val[1] = vsetq_lane_s16 (vgetq_lane_s16 (str.val[0], 2), str.val[1], 3);
  }

  void
  get_res (
    const std::int16_t             mul_koeff,
    const std::int16_t*            csstr,
    const cores::values_core_type* mask,
    const std::uint32_t            stride,
    std::int32_t*                  tress,
    std::int16_t*                  dstr)
  {
    int16x4_t str_data8;
    int16x8_t str_data;
    // int16x8_t str_himul;
    // int16x8_t str_lomul;
    // int16x8_t str_mul1;
    // int16x8_t str_mul2;
    int32x4_t akk1 = vdupq_n_s32 (0);
    int32x4_t akk2 = akk1;
    int32x4_t akk3 = akk1;
    int32x4_t akk4 = akk1;

    str_data8 = vld1_s16 (csstr);
    str_data  = vcombine_s16 (
      vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_low_)),
      vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_high_)));

    akk1 = vmlal_s16 (akk1, vget_low_s16 (str_data), vget_low_s16 (str1_core_.val[0]));
    akk2 = vmlal_s16 (akk2, vget_high_s16 (str_data), vget_high_s16 (str1_core_.val[0]));
    akk3 = vmlal_s16 (akk3, vget_low_s16 (str_data), vget_low_s16 (str1_core_.val[1]));
    akk4 = vmlal_s16 (akk4, vget_high_s16 (str_data), vget_high_s16 (str1_core_.val[1]));

    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    str_data8 = vld1_s16 (csstr);
    str_data  = vcombine_s16 (
      vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_low_)),
      vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_high_)));

    akk1 = vmlal_s16 (akk1, vget_low_s16 (str_data), vget_low_s16 (str2_core_.val[0]));
    akk2 = vmlal_s16 (akk2, vget_high_s16 (str_data), vget_high_s16 (str2_core_.val[0]));
    akk3 = vmlal_s16 (akk3, vget_low_s16 (str_data), vget_low_s16 (str2_core_.val[1]));
    akk4 = vmlal_s16 (akk4, vget_high_s16 (str_data), vget_high_s16 (str2_core_.val[1]));

    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    str_data8 = vld1_s16 (csstr);
    str_data  = vcombine_s16 (
      vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_low_)),
      vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_high_)));

    akk1 = vmlal_s16 (akk1, vget_low_s16 (str_data), vget_low_s16 (str3_core_.val[0]));
    akk2 = vmlal_s16 (akk2, vget_high_s16 (str_data), vget_high_s16 (str3_core_.val[0]));
    akk3 = vmlal_s16 (akk3, vget_low_s16 (str_data), vget_low_s16 (str3_core_.val[1]));
    akk4 = vmlal_s16 (akk4, vget_high_s16 (str_data), vget_high_s16 (str3_core_.val[1]));

    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    tress[0] = vgetq_lane_s32 (akk1, 0);
    tress[0] += vgetq_lane_s32 (akk1, 1);
    tress[0] += vgetq_lane_s32 (akk1, 2);

    tress[1] = vgetq_lane_s32 (akk1, 3);
    tress[1] += vgetq_lane_s32 (akk2, 0);
    tress[1] += vgetq_lane_s32 (akk2, 1);

    tress[2] = vgetq_lane_s32 (akk1, 3);
    tress[2] += vgetq_lane_s32 (akk2, 0);
    tress[2] += vgetq_lane_s32 (akk2, 1);

    tress[3] = vgetq_lane_s32 (akk1, 3);
    tress[3] += vgetq_lane_s32 (akk2, 0);
    tress[3] += vgetq_lane_s32 (akk2, 1);
  }


  int16x8x2_t str1_core_;       //<
  int16x8x2_t str2_core_;       //<
  int16x8x2_t str3_core_;       //<
  int8x8_t    permute8_low_;    //<
  int8x8_t    permute8_high_;   //<
};


struct TModNeonCalcObj : public TNeonCalcObj {
  TModNeonCalcObj () = default;

  void
  init (::libs::optim::io::MCallInfo& info, const cores::values_core_type** pmask)
  {
    TNeonCalcObj::init (info, pmask);
  }

  void
  get_res (
    const std::int16_t             mul_koeff,
    const std::int16_t*            csstr,
    const cores::values_core_type* mask,
    const std::uint32_t            stride,
    std::int32_t*                  tress,
    std::int16_t*                  dstr)
  {
    int16x4_t str_data8;
    int16x8_t str_data;
    int16x4_t str_data_low;
    int16x4_t str_data_high;
    // int16x8_t   str_himul;
    // int16x8_t   str_lomul;
    // int16x8_t   str_mul1;
    // int16x8_t   str_mul2;
    int32x4x4_t akk;

    akk.val[0] = vdupq_n_s32 (0);
    akk.val[1] = akk.val[0];
    akk.val[2] = akk.val[0];
    akk.val[3] = akk.val[0];

    str_data8     = vld1_s16 (csstr);                                                                   // AxBxCxDx
    str_data_low  = vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_low_));    // AxBxCxBx
    str_data_high = vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_high_));   // CxDxCxDx
    str_data      = vcombine_s16 (str_data_low, str_data_high);                                         // CxDxCxDxAxBxCxBx
    // permute8_low_ = vcreate_s8( 0x0302050403020100LL );
    // permute8_high_  = vcreate_s8( 0x0706050407060504LL );

    akk.val[0] = vmlal_s16 (akk.val[0], vget_low_s16 (str_data), vget_low_s16 (str1_core_.val[0]));     // AXBXCXBX
    akk.val[1] = vmlal_s16 (akk.val[1], vget_high_s16 (str_data), vget_high_s16 (str1_core_.val[0]));   //
    akk.val[2] = vmlal_s16 (akk.val[2], vget_low_s16 (str_data), vget_low_s16 (str1_core_.val[1]));
    akk.val[3] = vmlal_s16 (akk.val[3], vget_high_s16 (str_data), vget_high_s16 (str1_core_.val[1]));

    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    str_data8     = vld1_s16 (csstr);
    str_data_low  = vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_low_));
    str_data_high = vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_high_));
    str_data      = vcombine_s16 (str_data_low, str_data_high);

    akk.val[0] = vmlal_s16 (akk.val[0], vget_low_s16 (str_data), vget_low_s16 (str2_core_.val[0]));
    akk.val[1] = vmlal_s16 (akk.val[1], vget_high_s16 (str_data), vget_high_s16 (str2_core_.val[0]));
    akk.val[2] = vmlal_s16 (akk.val[2], vget_low_s16 (str_data), vget_low_s16 (str2_core_.val[1]));
    akk.val[3] = vmlal_s16 (akk.val[3], vget_high_s16 (str_data), vget_high_s16 (str2_core_.val[1]));

    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    str_data8     = vld1_s16 (csstr);
    str_data_low  = vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_low_));
    str_data_high = vreinterpret_s16_s8 (vtbl1_s8 (vreinterpret_s8_s16 (str_data8), permute8_high_));
    str_data      = vcombine_s16 (str_data_low, str_data_high);

    akk.val[0] = vmlal_s16 (akk.val[0], vget_low_s16 (str_data), vget_low_s16 (str3_core_.val[0]));
    akk.val[1] = vmlal_s16 (akk.val[1], vget_high_s16 (str_data), vget_high_s16 (str3_core_.val[0]));
    akk.val[2] = vmlal_s16 (akk.val[2], vget_low_s16 (str_data), vget_low_s16 (str3_core_.val[1]));
    akk.val[3] = vmlal_s16 (akk.val[3], vget_high_s16 (str_data), vget_high_s16 (str3_core_.val[1]));

    csstr = ::libs::helpers::mem::move_cptr (csstr, stride);

    tress[0] = vgetq_lane_s32 (akk.val[0], 0);
    tress[0] += vgetq_lane_s32 (akk.val[0], 1);
    tress[0] += vgetq_lane_s32 (akk.val[0], 2);

    tress[1] = vgetq_lane_s32 (akk.val[0], 3);
    tress[1] += vgetq_lane_s32 (akk.val[1], 0);
    tress[1] += vgetq_lane_s32 (akk.val[1], 1);

    tress[2] = vgetq_lane_s32 (akk.val[0], 3);
    tress[2] += vgetq_lane_s32 (akk.val[1], 0);
    tress[2] += vgetq_lane_s32 (akk.val[1], 1);

    tress[3] = vgetq_lane_s32 (akk.val[0], 3);
    tress[3] += vgetq_lane_s32 (akk.val[1], 0);
    tress[3] += vgetq_lane_s32 (akk.val[1], 1);

    TNeonCalcObj::get_res (mul_koeff, csstr, mask, stride, tress, dstr);

    tress[0] = std::abs (tress[0]);
    tress[1] = std::abs (tress[1]);
    tress[2] = std::abs (tress[2]);
    tress[3] = std::abs (tress[3]);
    tress[4] = std::abs (tress[4]);

#  if 0
    tres[indxr] = (tres[indxr] * mul_koeff) >> U3_SHIFT_MUL_KOEFF_CONVOLUTION;

    tres[indxr] = tres[indxr] > 255 ? 255 : tres[indxr];
    tres[indxr] = tres[indxr] < -255 ? -255 : tres[indxr];

    dstr[indxx + indxr] = s1tatic_cast< short > (tres[indxr]);
#  endif
  }
};


void
mod_neon (::libs::optim::io::MCallInfo& info)
{
  move_alg< TModNeonCalcObj, cores::values_core_type, TPostProcessor, consts::size_core, consts::pxs_per_cycle, 12 > (info);
}


void
neon (::libs::optim::io::MCallInfo& info)
{
  move_alg< TNeonCalcObj, cores::values_core_type, TPostProcessor, consts::size_core, consts::pxs_per_cycle, 12 > (info);
}
}   // namespace libs::optim::s16bit::conv::base::c3x3

#endif
