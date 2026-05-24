#pragma once
/**
\file       get_params_func.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/

namespace libs::optim::s16bit::gen::vec2image1
{
void
get_params (
  ::libs::optim::io::MCallInfo&                                                 info,
  const io::ProxyBuf**                                                          src,
  io::ProxyBuf**                                                                dst,
  ::libs::ievents::props::videos::generic::vec2image::EventBufsInfoVec2Image1** ppparams)
{
  U3_CHECK (1 == info.params_.evals_.size (), "invalid evals");
  U3_CHECK (1 == info.srcs_.size (), "src not equal 1");
  U3_CHECK (1 == info.dsts_.size (), "dst not equal 1");

  *src = &info.srcs_[0];
  *dst = &info.dsts_[0];

  U3_CHECK (*src, "empty src");
  U3_CHECK (*dst, "empty dst");

  *ppparams = boost::any_cast< ::libs::ievents::props::videos::generic::vec2image::EventBufsInfoVec2Image1* > (info.params_.evals_[0]);
  U3_CHECK (*ppparams, "empty params");
  (**ppparams).check ();
}
}   // namespace libs::optim::s16bit::gen::vec2image1
