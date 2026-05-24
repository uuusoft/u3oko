/**
\file       ycb_rgb24_base.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       30.07.2018
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "ycb_rgb24.hpp"
#include "ycb_rgb24_int.hpp"

namespace libs::optim::convert::ycb_rgb24
{
void
get_params (::libs::optim::io::MCallInfo& info, const ::libs::optim::io::ProxyBuf** yuy2, ::libs::optim::io::ProxyBuf** rgb24)
{
  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  U3_CHECK (1 == info.dsts_.size (), "dsts not equal 1");

  *yuy2  = &info.srcs_[0];
  *rgb24 = &info.dsts_[0];

  U3_CHECK (*yuy2, "tmpy yuy2");
  U3_CHECK (rgb24, "empty rgb24");

  (*yuy2)->check ("yuy2 convert::ycb_rgb24");
  (*rgb24)->check ("rgb24 convert::ycb_rgb24");
}
}   // namespace libs::optim::convert::ycb_rgb24
