/**
\file       x8_x16_base.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
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
get_params (
  ::libs::optim::io::MCallInfo&       info,
  const ::libs::optim::io::ProxyBuf** x8,
  ::libs::optim::io::ProxyBuf**       x16)
{
  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");

  *x8  = &info.srcs_[0];
  *x16 = &info.dsts_[0];

  U3_CHECK (*x8, "empty x8");
  U3_CHECK (x16, "empty x16");

  (*x8)->check ("x8 convert::x8_x16");
  (*x16)->check ("x16 convert::x8_x16");
}
}   // namespace libs::optim::convert::x8_x16
