/**
\file       x16_x8_base.cpp
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
get_params (::libs::optim::io::MCallInfo& info, const ::libs::optim::io::ProxyBuf** x16, ::libs::optim::io::ProxyBuf** x8)
{
  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");

  *x16 = &info.srcs_[0];
  *x8  = &info.dsts_[0];

  U3_CHECK (*x16, "empty x16");
  U3_CHECK (x8, "empty x8");

  (*x16)->check ("y16 convert::x16_x8");
  (*x8)->check ("y8 convert::x16_x8");
}
}   // namespace libs::optim::convert::x16_x8
