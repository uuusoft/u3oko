/**
\file       diff-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgen_diff_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vgen-diff-lib-includes_int.hpp"
#include "diff-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::gens::vgen_diff::lib
{
void
DiffImpl::set_props (syn::VideoDiffProp::craw_ptr props)
{
  props_ = props;
}


void
DiffImpl::init ()
{
  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  cmp_get_const_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CCmpGTConstAlg::val_key));
  abs_diff_      = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CAbsDiffAlg::val_key));
  pthreads_      = U3_CAST_PROP (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ())->get_mcalls_lockfree ();
}


void
DiffImpl::set_transform_info (syn::TransformInfo* tranform_info)
{
  transinfo_ = tranform_info;
}


void
DiffImpl::itransform (const syn::NodeID& id_node, ::libs::bufs::Bufs& pbufs)
{
  U3_ASSERT (props_);
  auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ();

  for (const syn::VideoDiffProp::buf2info_type& b2b : props_->diffs_)
  {
    const ::utils::dbufs::video::consts::offs::off_buf_type sindx = b2b.first;
    const ::utils::dbufs::video::consts::offs::off_buf_type dindx = b2b.second.bindx_diff_;
    syn::IVideoBuf::raw_ptr                                 psrc  = pbufs[sindx];

    if (!psrc || psrc->get_flag (::utils::dbufs::BufFlags::empty))
    {
      continue;
    }

    ::libs::bufs::alloc_buf_by_indx (&pbufs, dindx, psrc);

    bool                    copy2prev = true;
    const bool              copy2temp = sindx == dindx ? true : false;
    syn::IVideoBuf::raw_ptr pdst      = pbufs[dindx];
    syn::IVideoBuf::ptr&    prevbuf   = indx2prev_buf_[sindx];

    pdst->clone (psrc, 100.0F);

    prevbuf   = prevbuf ? prevbuf : ibuf->create (0);
    temp_buf_ = temp_buf_ ? temp_buf_ : ibuf->create (0);

    if (prevbuf->get_flag (::utils::dbufs::BufFlags::empty) || !utils::dbufs::video::helpers::is_equal_dim (*prevbuf, *psrc))
    {
      prevbuf->clone (psrc, 100.0F);
      copy2prev = false;
    }

    if (copy2temp)
    {
      temp_buf_->clone (psrc, 100.0F);
    }

    make_diff_buf (id_node, *prevbuf, *pdst);

    if (copy2prev)
    {
      prevbuf->clone (copy2temp ? temp_buf_.get () : psrc, 100.0F);
    }

    if (b2b.second.op_.enable_)
    {
      bin_buf (
        id_node,
        b2b.second.op_.bound_filling_,
        b2b.second.op_.val_filling_,
        pdst);
    }
  }
}


void
DiffImpl::make_diff_buf (
  const syn::NodeID&    id_obj,
  const syn::IVideoBuf& src1,
  syn::IVideoBuf&       src2res)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.srcs_.emplace_back (const_cast< syn::IVideoBuf::raw_ptr > (&src1), "src1 dlls::gens::vgen_diff::lib");
  cinfo.dsts_.emplace_back (&src2res, "src2res dlls::gens::vgen_diff::lib");

  cinfo.params_.dest_mask_ = ::libs::optim::s16bit::consts::us_all_xffff;

  ::libs::optim::mcalls::MTFuncInfo tfunc (&abs_diff_);

  pthreads_->mthreads_call (
    id_obj,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}


void
DiffImpl::bin_buf (
  const syn::NodeID& id_node,
  const std::int16_t bound,
  const std::int16_t val,
  syn::IVideoBuf*    pdst)
{
  ::libs::optim::io::MCallInfo cinfo;

  cinfo.dsts_.emplace_back (pdst, "pdst dlls::gens::vgen_diff::lib");

  cinfo.params_.evals_.emplace_back (boost::any (::libs::optim::s16bit::consts::us_all_xffff));
  cinfo.params_.evals_.emplace_back (boost::any (bound));
  cinfo.params_.evals_.emplace_back (boost::any (val));

  ::libs::optim::mcalls::MTFuncInfo tfunc (&cmp_get_const_);

  pthreads_->mthreads_call (
    id_node,
    tfunc,
    cinfo,
    transinfo_->exptimes_);
}
}   // namespace dlls::gens::vgen_diff::lib
