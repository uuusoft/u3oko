#pragma once
/**
\file       gt_const_int.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits
*/

namespace libs::optim::s16bit::bits::cmp::gt_const
{
inline void
get_params (
  ::libs::optim::io::MCallInfo& info,
  const std::uint16_t*&         mask_dest8,
  std::int16_t&                 const1,
  std::int16_t&                 const2)
{
  mask_dest8 = 0;
  const1     = 0;
  const2     = 0;

  U3_CHECK (3 == info.params_.evals_.size (), "evals not equal 3");
  U3_CHECK (0 == info.srcs_.size (), "src not equal 0");
  U3_CHECK (1 == info.dsts_.size (), "dsts not equal 1");

  mask_dest8 = boost::any_cast< const std::uint16_t* > (info.params_.evals_[0]);
  const1     = boost::any_cast< std::int16_t > (info.params_.evals_[1]);
  const2     = boost::any_cast< std::int16_t > (info.params_.evals_[2]);
}

}   // namespace libs::optim::s16bit::bits::cmp::gt_const
