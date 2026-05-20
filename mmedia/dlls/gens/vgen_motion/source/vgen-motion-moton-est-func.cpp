/**
\file       vgen-motion-est-funct.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vgd_motion
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-motion-includes_int.hpp"
#include "vgen-motion-info-filter-dll.hpp"
#include "vgen-motion-filter-dll.hpp"

namespace dlls::gens::vgen_motion
{
void
Filter::make_motion_est_buf (
  syn::EventBufsInfoMotionEst& b2b,
  const syn::IVideoBuf&        cur_src,
  const syn::IVideoBuf&        prev_src,
  syn::IVideoBuf&              dst_vecs)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (const_cast< syn::IVideoBuf::raw_ptr > (&cur_src), "cur_src dlls::gens::vgen_motion"));
  cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (const_cast< syn::IVideoBuf::raw_ptr > (&prev_src), "prev_src dlls::gens::vgen_motion"));
  cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (&dst_vecs, "dst_vecs dlls::gens::vgen_motion"));

  cinfo.params_.evals_.push_back (boost::any (&b2b));

  ::libs::optim::mcalls::InfoMFunct tfunct (&motion_est1_);

  tfunct.src_align_.px_x_ = b2b.size_block_;
  tfunct.dst_align_.px_x_ = b2b.size_block_;
  tfunct.src_align_.px_y_ = b2b.size_block_;
  tfunct.dst_align_.px_y_ = 1;

  // tfunct.dest_div_koeffy_ = b2b.size_block_;
  // tfunct.dest_mul_koeffy_ = 1;

  pthreads_->mthreads_call (
    id_obj_,
    tfunct,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::gens::vgen_motion
