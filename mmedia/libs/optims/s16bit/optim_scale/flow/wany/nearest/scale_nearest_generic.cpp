/**
\file       scale_nearest_generic.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_scale
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "scale_nearest.hpp"
#include "scale_nearest_int.hpp"

namespace libs::optim::s16bit::scale::flow::wany::nearest
{
void
fill_end_leak_from_begin (
  unsigned char* buf,
  std::uint32_t  width_bytes,
  std::uint32_t  height,
  std::uint32_t  stride_bytes)
{
  if (stride_bytes == width_bytes)
  {
    return;
  }

  std::int32_t leak = stride_bytes - width_bytes;
  for (std::uint32_t indx1 = 0; indx1 < height; ++indx1)
  {
    memmove (buf + width_bytes, buf, leak);
    buf = buf + stride_bytes;
  }
}


void
get_params (::libs::optim::io::MCallInfo& info, CallParams& params)
{
  params.reset ();

  U3_CHECK (1 == info.srcs_.size (), "invalid size srcs");
  U3_CHECK (1 == info.dsts_.size (), "invalid size dsts");

  params.psrc_ = &info.srcs_[0];
  params.pdst_ = &info.dsts_[0];

  params.psrc_->check ("psrc flow wany nearest");
  params.pdst_->check ("pdst flow wany nearest");

  U3_CHECK (3 == info.params_.evals_.size (), "invalid count params");

  params.stride_output_ = boost::any_cast< std::uint32_t* > (info.params_.evals_[0]);
  params.max_out_size_  = boost::any_cast< std::uint32_t* > (info.params_.evals_[1]);
  params.indxer_        = boost::any_cast< IndexerColRow* > (info.params_.evals_[2]);

  params.check ();
}
}   // namespace libs::optim::s16bit::scale::flow::wany::nearest
