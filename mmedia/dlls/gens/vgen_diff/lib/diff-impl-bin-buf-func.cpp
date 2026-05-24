/**
\file       diff-impl-bin-buf-funct.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgen_diff_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-diff-lib-includes_int.hpp"
#include "diff-impl.hpp"

namespace dlls::gens::vgen_diff::lib
{
void
DiffImpl::bin_buf (
  const syn::NodeID& id_node,
  const std::int16_t bound,
  const std::int16_t val,
  syn::IVideoBuf*    pdst)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (pdst, "pdst dlls::gens::vgen_diff::lib"));

  cinfo.params_.evals_.push_back (boost::any (::libs::optim::s16bit::consts::us_all_xffff));
  cinfo.params_.evals_.push_back (boost::any (bound));
  cinfo.params_.evals_.push_back (boost::any (val));

  ::libs::optim::mcalls::InfoMFunct tfunct (&cmp_get_const_);

  pthreads_->mthreads_call (
    id_node,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::gens::vgen_diff::lib
