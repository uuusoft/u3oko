/**
\file				*.cpp
\author			Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date				01.01.2017
\project		u3_optim_conv
*/
#include "cond_convolution_3x3.hpp"

#ifndef MODUL_2D_CONV_IMPL

namespace libs::optim::s16bit::conv::cond
{
inline bool
get_cond_conv_params (
  ::libs::optim::io::MCallInfo&   info,
  std::array< std::int16_t, 9 >*& mask1,
  std::array< std::int16_t, 9 >*& mask2,
  std::int16_t&                   mul_koeff,
  std::int16_t&                   bound_condition)
{
  if (4 != info.params_.evals_.size ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  if (2 != info.srcs_.size ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  if (1 != info.dsts_.size ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  try
  {
    mask1           = boost::any_cast< std::array< std::int16_t, 9 >* > (info.params_.evals_[0]);
    mask2           = boost::any_cast< std::array< std::int16_t, 9 >* > (info.params_.evals_[1]);
    mul_koeff       = boost::any_cast< std::int16_t > (info.params_.evals_[2]);
    bound_condition = boost::any_cast< std::int16_t > (info.params_.evals_[3]);

    if (!mask1 || !mask2)
    {
      U3_ASSERT_SIGNAL_NT ("failed");
      return false;
    }
  }
  catch (boost::bad_any_cast& /*e*/)
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }
  return true;
}
}   // namespace libs::optim::s16bit::conv::cond

#endif
