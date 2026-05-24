#pragma once
/**
\file       histogram1_int.hpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_statistic
*/

namespace libs::optim::s16bit::statistics::histogram
{
inline void
get_params (::libs::optim::io::MCallInfo& cinfo, int*& freq, int& size_freq)
{
  freq      = 0;
  size_freq = 0;

  U3_CHECK (cinfo.dsts_.size (), "empty dsts");
  U3_CHECK (1 == cinfo.srcs_.size (), "dsts not equal 1");

  const auto& src = cinfo.srcs_[0];

  src.check ("src libs::optim::s16bit::statistics::histogram");

  U3_CHECK (::libs::helpers::mem::check_align16_ptr (src.buf ()), "unalign ptr src");
  U3_CHECK (::libs::helpers::mem::check_align16 (src.stride_), "unalign stride src");

  freq      = boost::any_cast< int* > (cinfo.params_.evals_[0]);
  size_freq = boost::any_cast< int > (cinfo.params_.evals_[1]);

  U3_CHECK (size_freq > 255, "size_freq > 255");
}
}   // namespace libs::optim::s16bit::statistics::histogram
