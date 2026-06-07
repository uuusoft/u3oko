/**
\file       x16_x8_neon.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "x16_x8.hpp"
#include "x16_x8_int.hpp"

#ifdef U3_CPU_ARM

namespace libs::optim::convert::x16_x8
{
U3_SET_TARGET_CPU (+simd)
void
neon (::libs::optim::io::MCallInfo& info)
{
#  if 1
  alu (info);
#  else
  X16_TO_X8_PREFIX (8);

  const int16x8_t mask = vdupq_n_s16 (0x00FF);

  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += ppc)
    {
      int16x8_t data = vld1q_s16 (::libs::helpers::casts::reinterpret_cast_helper< const std::int16_t* > (yuy2_buf));

      data = vandq_s16 (data, mask);

      vst1q_s16 (y16_buf, data);

      yuy2_buf += dppc;
      y16_buf += ppc;
    }

    yuy2_buf = ::libs::helpers::mem::move_cptr (yuy2_buf, leak_yuy2);
    y16_buf  = ::libs::helpers::mem::move_ptr (y16_buf, leak_y16);
  }
#  endif
}
}   // namespace libs::optim::convert::x16_x8

#endif
