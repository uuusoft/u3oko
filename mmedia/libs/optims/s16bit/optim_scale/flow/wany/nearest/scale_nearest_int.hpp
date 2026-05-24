#pragma once
/**
\file       scale_nearest_int.hpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_scale
*/
#include "indexer-col-row.hpp"
#include "call-params.hpp"

namespace libs::optim::s16bit::scale::flow::wany::nearest
{
void get_params (::libs::optim::io::MCallInfo& info, CallParams& params);

void fill_end_leak_from_begin (
  unsigned char* buf,
  std::uint32_t  width_bytes,
  std::uint32_t  height,
  std::uint32_t  stride_bytes);


template< typename TTScaler >
void
nearest_scale (::libs::optim::io::MCallInfo& info)
{
  CallParams params;

  get_params (info, params);

  const bool    fill_leak = info.params_.bools_.size () ? info.params_.bools_[0] : true;
  std::uint32_t stride    = ::libs::helpers::mem::get_align32< std::uint32_t > (params.pdst_->width_ * sizeof (short));

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
}
}   // namespace libs::optim::s16bit::scale::flow::wany::nearest
