/**
\file       i420_rgb24_base.cpp
\author     Erashov Anton erashov2026@proton.me
\date       05.04.2022
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"

namespace libs::optim::convert::i420_rgb24
{
void
get_params (
  ::libs::optim::io::MCallInfo&       info,
  const ::libs::optim::io::ProxyBuf** y,
  ::libs::optim::io::ProxyBuf**       rgb24)
{
  ::libs::utility::checks::throw_ifn (1 == info.srcs_.size (), "src not equal 1");
  ::libs::utility::checks::throw_ifn (1 == info.dsts_.size (), "dst not equal 1");

  *y     = &info.srcs_[0];
  *rgb24 = &info.dsts_[0];

  ::libs::utility::checks::throw_ifn (*y, "empty y");
  ::libs::utility::checks::throw_ifn (rgb24, "empty rgb24");

  (*y)->check ("y convert::i420_rgb24");
  (*rgb24)->check ("rgb24 convert::i420_rgb24");
}
}   // namespace libs::optim::convert::i420_rgb24
