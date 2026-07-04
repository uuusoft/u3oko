/**
\file       x16_x8_alu.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "x16_x8.hpp"
#include "x16_x8_int.hpp"

namespace libs::optim::convert::x16_x8
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  X16_TO_X8_PREFIX (1);

  for (std::uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::uint32_t indx_x = 0; indx_x < width; indx_x += ppc)
    {
      x8_buf[0] = U3_CAST_UINT8 (x16_buf[0] < 0 ? 0 : (x16_buf[0] > 255 ? 255 : x16_buf[0]));

      x16_buf += dppc;
      x8_buf += ppc;
    }

    x16_buf = ::libs::utility::mem::move_cptr (x16_buf, leak_x16);
    x8_buf  = ::libs::utility::mem::move_ptr (x8_buf, leak_x8);
  }
}
}   // namespace libs::optim::convert::x16_x8
