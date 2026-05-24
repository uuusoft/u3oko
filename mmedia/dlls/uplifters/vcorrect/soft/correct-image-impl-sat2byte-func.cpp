/**
\file       correct-image-impl-sat2byte-funct.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_vcorrect_vdd
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../vcorrect-includes_int.hpp"
#include "correct-image-impl.hpp"

namespace dlls::uplifters::vcorrect::soft
{
void
CorrectImageImpl::sat2byte_correct (syn::IVideoBuf& buf)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (&buf, "buf dlls::uplifters::vcorrect::soft"));
  cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;

  ::libs::optim::mcalls::InfoMFunct tfunct (&mfunc_sat2byte_);
  pthreads_->mthreads_call (
    *id_node_graph_,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::uplifters::vcorrect::soft
