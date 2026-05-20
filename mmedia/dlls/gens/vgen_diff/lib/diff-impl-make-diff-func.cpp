/**
\file       diff-impl-make-diff-funct.cpp
\author     Erashov Anton erashov2026@proton.me
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
DiffImpl::make_diff_buf (
  const syn::NodeID&    id_obj,
  const syn::IVideoBuf& src1,
  syn::IVideoBuf&       src2res)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (const_cast< syn::IVideoBuf::raw_ptr > (&src1), "src1 dlls::gens::vgen_diff::lib"));
  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (&src2res, "src2res dlls::gens::vgen_diff::lib"));

  cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;

  ::libs::optim::mcalls::InfoMFunct tfunct (&abs_diff_);

  pthreads_->mthreads_call (
    id_obj,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::gens::vgen_diff::lib
