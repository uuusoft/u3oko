/**
\file     motion_est1_base.cpp
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date     28.08.2016
\project  u3_optim_libs_motion
\brief    Оценка движения в кадре
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "motion_est1.hpp"

namespace libs::optim::s16bit::motion::est1
{
void
get_params (
  ::libs::optim::io::MCallInfo& info,
  const io::ProxyBuf**          cur_src,
  const io::ProxyBuf**          prev_src,
  io::ProxyBuf**                dst_vecs,
  EventBufsInfoMotionEst**      ppparams)
{
  U3_CHECK (1 == info.params_.evals_.size (), "invald evals");
  U3_CHECK (2 == info.srcs_.size (), "src not equal 2");
  U3_CHECK (1 == info.dsts_.size (), "dsts not equal 1");

  *cur_src  = &info.srcs_[0];
  *prev_src = &info.srcs_[1];
  *dst_vecs = &info.dsts_[0];

  U3_CHECK (*cur_src, "empty cur_src");
  U3_CHECK (*prev_src, "empty prev_src");
  U3_CHECK (*dst_vecs, "empty dst_vecs");

  *ppparams = boost::any_cast< EventBufsInfoMotionEst* > (info.params_.evals_[0]);
  U3_CHECK (*ppparams, "empty params");
  (**ppparams).check ();
  U3_CHECK (!(**ppparams).search_vecs_.empty (), "empty search vecs");
}
}   // namespace libs::optim::s16bit::motion::est1
