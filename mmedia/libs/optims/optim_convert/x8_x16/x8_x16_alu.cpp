/**
\file       x8_x16_alu.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "x8_x16.hpp"
#include "x8_x16_int.hpp"

namespace libs::optim::convert::x8_x16
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  X8_TO_X16_PREFIX (1);

  for (std::uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::uint32_t indx_x = 0; indx_x < width; indx_x += ppc)
    {
      x16_buf[0] = x8_buf[0];
      x16_buf += dppc;
      x8_buf += ppc;
    }

    x8_buf  = ::libs::helpers::mem::move_cptr (x8_buf, leak_x8);
    x16_buf = ::libs::helpers::mem::move_ptr (x16_buf, leak_x16);
  }
}
}   // namespace libs::optim::convert::x8_x16
