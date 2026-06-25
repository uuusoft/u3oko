/**
\file       nv21_y16_alu.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "nv21_y16.hpp"
#include "nv21_y16_int.hpp"

namespace libs::optim::convert::nv21_y16
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  NV212Y16_PREFIX (1);
  U3_MARK_UNUSED_HERE (leak_y16);
  U3_MARK_UNUSED_HERE (leak_y8);

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      y16_buf[indxx] = y8_buf[indxx];
    }

    y8_buf  = ::libs::helpers::mem::move_cptr (y8_buf, stride_y8);
    y16_buf = ::libs::helpers::mem::move_ptr (y16_buf, stride_y16);
  }
}
}   // namespace libs::optim::convert::nv21_y16
