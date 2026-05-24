/**
\file       all2hsl-dll-convert_from_y8_funct.cpp
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
Filter::convert_bufs_from_y8 ()
{
  syn::IVideoBuf::raw_ptr l     = (*pbuf_)[::utils::dbufs::video::consts::offs::lit];
  syn::IVideoBuf::raw_ptr rcbuf = (*pbuf_)[::utils::dbufs::video::consts::offs::raw];

  {
    ::libs::optim::io::MCallInfo cinfo;

    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (rcbuf, "rcbuf convertors::all2hsl"));
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (l, "l convertors::all2hsl"));

    ::libs::optim::mcalls::InfoMFunct tfunct (&fx8_to_x16_);

    pthreads_->mthreads_call (
      id_obj_,
      tfunct,
      cinfo,
      transinfo_->exptimes_);
  }

  l->set_mem_var (
    ::utils::dbufs::MemVars::size_data,
    l->get_dim_var (::utils::dbufs::video::Dims::height) * l->get_dim_var (::utils::dbufs::video::Dims::stride));
  // utils::dbufs::video::helpers::fill( l, rand() % 256 );//debug
}
}   // namespace dlls::convertors::all2hsl
