/**
\file       x8_x16_neon.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "x8_x16.hpp"
#include "x8_x16_int.hpp"

#if defined(U3_CPU_ARM)

namespace libs::optim::convert::x8_x16
{
U3_SET_TARGET_CPU (+simd)
void
neon (::libs::optim::io::MCallInfo& info)
{
#  if 1
  return alu (info);
#  else
  X16_TO_X8_PREFIX (8);

  const int16x8_t mask = vdupq_n_s16 (0x00FF);

  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += ppc)
    {
      int16x8_t data = vld1q_s16 (U3_CAST_REINTERPRET< const std::int16_t* > (yuy2_buf));

      data = vandq_s16 (data, mask);

      vst1q_s16 (y16_buf, data);

      yuy2_buf += dppc;
      y16_buf += ppc;
    }

    U3_FAST_MOVE_CPTR (yuy2_buf, leak_yuy2);
    U3_FAST_MOVE_PTR (y16_buf, leak_y16);
  }
#  endif
}
}   // namespace libs::optim::convert::x8_x16

#endif
