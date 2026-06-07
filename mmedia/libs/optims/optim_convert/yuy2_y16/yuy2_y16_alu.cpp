/**
\file       yuy2_y16_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "yuy2_y16.hpp"
#include "yuy2_y16_int.hpp"

namespace libs::optim::convert::yuy2_y16
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  YUY22Y16_PREFIX (2);

  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += ppc)
    {
      y16_buf[0] = yuy2_buf[0];
      y16_buf[1] = yuy2_buf[2];

      yuy2_buf += dppc;
      y16_buf += ppc;
    }

    yuy2_buf = ::libs::helpers::mem::move_cptr (yuy2_buf, leak_yuy2);
    y16_buf  = ::libs::helpers::mem::move_ptr (y16_buf, leak_y16);
  }
}
}   // namespace libs::optim::convert::yuy2_y16
