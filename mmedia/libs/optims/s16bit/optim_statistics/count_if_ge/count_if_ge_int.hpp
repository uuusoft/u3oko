#pragma once
/**
\file       count_if_ge_int.hpp
\date       01.05.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_statistic
*/

namespace libs::optim::s16bit::statistics::count_if_ge
{
inline void
get_params (::libs::optim::io::MCallInfo& cinfo, int*& freq, std::int16_t& bound)
{
  freq  = 0;
  bound = 0;

  U3_CHECK (0 == cinfo.dsts_.size (), "not empty dsts");
  U3_CHECK (1 == cinfo.srcs_.size (), "dsts not equal 1");

  const auto& src = cinfo.srcs_[0];

  src.check ("src 0 count_if_ge");

  U3_CHECK (::libs::helpers::mem::check_align16_ptr (src.buf ()), "unalign ptr src");
  U3_CHECK (::libs::helpers::mem::check_align16 (src.stride_), "unalign stride src");
  U3_CHECK (2 == cinfo.params_.evals_.size (), "size evals not equal 2");

  std::vector< int >* pfreqs    = boost::any_cast< std::vector< int >* > (cinfo.params_.evals_[0]);
  const std::int16_t  raw_bound = boost::any_cast< std::int16_t > (cinfo.params_.evals_[1]);

  U3_CHECK (pfreqs, "empty freq array");
  U3_CHECK (pfreqs->size () >= cinfo.count_threads_, VTOLOG (pfreqs->size ()) + " less count threads " + VTOLOG (cinfo.count_threads_));

  freq  = &(*pfreqs)[cinfo.indx_thread_];
  bound = raw_bound;
}
}   // namespace libs::optim::s16bit::statistics::count_if_ge
