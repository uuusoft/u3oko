/**
\file       all2hsl-dll-convert_from_rgb_funct.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_all2hsl
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "all2hsl-dll-includes_int.hpp"
#include "all2hsl-dll-info-filter-dll.hpp"
#include "all2hsl-dll-filter-dll.hpp"

namespace dlls::convertors::all2hsl
{
void
Filter::convert_bufs_from_rgb ()
{
  syn::IVideoBuf::raw_ptr hsl[3] = {
    finfo_.strip_color_ ? nullptr : (*pbuf_)[::utils::dbufs::video::consts::offs::hue],
    finfo_.strip_color_ ? nullptr : (*pbuf_)[::utils::dbufs::video::consts::offs::sat],
    (*pbuf_)[::utils::dbufs::video::consts::offs::lit]
  };

  syn::IVideoBuf::raw_ptr           rcbuf = (*pbuf_)[::utils::dbufs::video::consts::offs::raw];
  ::libs::optim::io::MCallInfo      cinfo;
  ::libs::optim::mcalls::InfoMFunct tfunct;

  cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (rcbuf, "rcbuf convertors::all2hsl"));

  if (finfo_.strip_color_)
  {
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (hsl[2], "hsl 2 convertors::all2hsl"));

    tfunct.pfunc_           = ::libs::ievents::props::videos::generic::convert::Accuracys::best == finfo_.rprops_->atype_ ? &rgb24_to_l_accurate_ : &rgb24_to_l_fast_;
    tfunct.src_align_.px_x_ = 1;
    tfunct.dst_align_.px_x_ = 1;
    tfunct.src_align_.px_y_ = 1;
    tfunct.dst_align_.px_y_ = 1;
  }
  else
  {
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (hsl[0], "hsl 0 convertors::all2hsl"));
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (hsl[1], "hsl 1 convertors::all2hsl"));
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (hsl[2], "hsl 2 convertors::all2hsl"));

    tfunct.pfunc_           = &rgb24_to_hsl_;
    tfunct.src_align_.px_x_ = 1;
    tfunct.dst_align_.px_x_ = 1;
    tfunct.src_align_.px_y_ = 1;
    tfunct.dst_align_.px_y_ = 1;
  }

  if (!finfo_.rprops_->debug_skip_transform_)
  {
    pthreads_->mthreads_call (id_obj_, tfunct, cinfo, transinfo_->exptimes_);
  }

  for (syn::IVideoBuf::raw_ptr cbuf : hsl)
  {
    if (!cbuf)
    {
      continue;
    }

    cbuf->set_mem_var (
      ::utils::dbufs::MemVars::size_data,
      cbuf->get_dim_var (::utils::dbufs::video::Dims::height) * cbuf->get_dim_var (::utils::dbufs::video::Dims::stride));
    // cbuf->fill( rand() % 255 );//debug
  }
}
}   // namespace dlls::convertors::all2hsl
