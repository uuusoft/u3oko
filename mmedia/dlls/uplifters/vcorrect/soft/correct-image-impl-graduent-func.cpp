/**
\file       correct-image-impl-graduent-funct.cpp
\brief      Filter for correct image
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vcorrect_vdd
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../vcorrect-includes_int.hpp"
#include "correct-image-impl.hpp"

namespace dlls::uplifters::vcorrect::soft
{
void
CorrectImageImpl::graduent_correct (
  syn::IVideoBuf&                        buf,
  const std::array< std::int16_t, 256 >& vals2vals)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (&buf, "buf dlls::uplifters::vcorrect::soft"));
  cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;
  cinfo.params_.consts_.push_back (&vals2vals[0]);
  cinfo.params_.ints_.push_back (U3_CAST_INT32 (vals2vals.size ()));

  ::libs::optim::mcalls::InfoMFunct tfunct (&mfunc_grad_func_);

  pthreads_->mthreads_call (
    *id_node_graph_,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::uplifters::vcorrect::soft
