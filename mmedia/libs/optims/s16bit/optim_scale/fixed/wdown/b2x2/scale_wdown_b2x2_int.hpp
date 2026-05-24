#pragma once
/**
\file       scale_wdown_b2x2_int.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_scale
*/
#include "mmedia/libs/optims/s16bit/optim_scale/fixed/call-params.hpp"

namespace libs::optim::s16bit::scale::fixed::wdown::b2x2
{
void get_params (::libs::optim::io::MCallInfo& info, CallParams& params);

void fill_end_leak_from_begin (
  unsigned char* buf,
  std::size_t    width_bytes,
  std::size_t    height,
  std::size_t    stride_bytes);


template< typename TTScaler >
void
b2b_scale (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_SIGNAL ("failed");
#if 0
  CallParams params;

  get_params (info, params);

  const bool  fill_leak = info.params_.bools_.size () ? info.params_.bools_[0] : true;
  std::size_t stride    = ::libs::helpers::mem::get_align32 (params.pdst_->width_ * sizeof (short));

  if (0 == *params.stride_output_)
  {
    *params.stride_output_ = stride;
  }

  if ((*params.stride_output_) * params.pdst_->height_ > (*params.max_out_size_))
  {
    U3_ASSERT_SIGNAL ("failed");

    (*params.max_out_size_) = (*params.stride_output_) * params.pdst_->height_;

    return;
  }

  TTScaler obj;
  obj (params);

  if (fill_leak)
  {
    fill_end_leak_from_begin (
      params.pdst_->ubuf (),
      params.pdst_->width_ * sizeof (short),
      params.pdst_->height_,
      *params.stride_output_);
  }
#endif
}
}   // namespace libs::optim::s16bit::scale::fixed::wdown::b2x2
