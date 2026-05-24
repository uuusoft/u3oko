/**
\file       freq_dct_b8x8_forward_generic.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_freq
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "freq_dct_b8x8_forward.hpp"
#include "freq_dct_b8x8_forward_int.hpp"

namespace libs::optim::s16bit::freq::dct::b8x8::forward
{
void
get_params (::libs::optim::io::MCallInfo& info, TCallParams& params)
{
  params.reset ();

  U3_CHECK (1 == info.srcs_.size (), "invalid size srcs");
  U3_CHECK (1 == info.dsts_.size (), "invalid size dsts");

  params.psrc_ = &info.srcs_[0];
  params.pdst_ = &info.dsts_[0];

  params.psrc_->check ("src 0 freq::dct::b8x8::forward");
  params.pdst_->check ("dst 0 freq::dct::b8x8::forward");

  U3_CHECK (2 == info.params_.evals_.size (), "invalid count params");

  params.pquanter_ = boost::any_cast< const b8x8::helpers::quant::CQuant* > (info.params_.evals_[0]);
  params.prets_    = boost::any_cast< std::vector< TThreadRetFromCall >* > (info.params_.evals_[1]);

  U3_CHECK (params.check (), "retrive params");
}
}   // namespace libs::optim::s16bit::freq::dct::b8x8::forward
