/**
\file       nv21_y16_base.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
get_params (
  ::libs::optim::io::MCallInfo&       info,
  const ::libs::optim::io::ProxyBuf** y8,
  ::libs::optim::io::ProxyBuf**       y16)
{
  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");

  *y8  = &info.srcs_[0];
  *y16 = &info.dsts_[0];

  U3_CHECK (*y8, "empty y8");
  U3_CHECK (y16, "empty y16");

  (*y8)->check ("y8 libs::optim::convert::nv21_y16");
  (*y16)->check ("y16 libs::optim::convert::nv21_y16");
}
}   // namespace libs::optim::convert::nv21_y16
