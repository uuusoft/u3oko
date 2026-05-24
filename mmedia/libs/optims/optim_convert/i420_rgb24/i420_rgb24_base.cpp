/**
\file       i420_rgb24_base.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       05.04.2022
\project    u3_optim_gen_convert
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
  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");

  *y     = &info.srcs_[0];
  *rgb24 = &info.dsts_[0];

  U3_CHECK (*y, "empty y");
  U3_CHECK (rgb24, "empty rgb24");

  (*y)->check ("y convert::i420_rgb24");
  (*rgb24)->check ("rgb24 convert::i420_rgb24");
}
}   // namespace libs::optim::convert::i420_rgb24
