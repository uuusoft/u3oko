/**
\file       all2hsl-dll-flip_y_funct.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
Filter::flip_y_bufs ()
{
  if (!finfo_.rprops_->flip_y_)
  {
    return;
  }

  syn::IVideoBuf::raw_ptr hsl[3] = {
    finfo_.strip_color_ ? nullptr : (*pbuf_)[::utils::dbufs::video::consts::offs::hue],
    finfo_.strip_color_ ? nullptr : (*pbuf_)[::utils::dbufs::video::consts::offs::sat],
    (*pbuf_)[::utils::dbufs::video::consts::offs::lit]
  };

  for (syn::IVideoBuf::raw_ptr cbuf : hsl)
  {
    if (!cbuf)
    {
      continue;
    }

    //  sync y
    ::libs::optim::io::MCallInfo      cinfo;
    ::libs::optim::mcalls::InfoMFunct tfunct (&flip_y_);

    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (cbuf, "dst Filter::flip_y_bufs"));

    pthreads_->mthreads_call (
      id_obj_,
      tfunct,
      cinfo,
      transinfo_->exptimes_,
      1);
  }
}
}   // namespace dlls::convertors::all2hsl
