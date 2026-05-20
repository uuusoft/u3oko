/**
\file       diff-impl-transform-funct.cpp
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

    pdst->clone (psrc, 100.0f);

    prevbuf   = prevbuf ? prevbuf : ibuf->create (0);
    temp_buf_ = temp_buf_ ? temp_buf_ : ibuf->create (0);

    if (prevbuf->get_flag (::utils::dbufs::BufFlags::empty) || !utils::dbufs::video::helpers::is_equal_dim (*prevbuf, *psrc))
    {
      prevbuf->clone (psrc, 100.0f);
      copy2prev = false;
    }

    if (copy2temp)
    {
      temp_buf_->clone (psrc, 100.0f);
    }

    make_diff_buf (id_node, *prevbuf, *pdst);

    if (copy2prev)
    {
      prevbuf->clone (copy2temp ? temp_buf_.get () : psrc, 100.0f);
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
}   // namespace dlls::gens::vgen_diff::lib
