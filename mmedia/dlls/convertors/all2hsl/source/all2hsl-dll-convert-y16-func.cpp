/**
\file       all2hsl-dll-convert_from_y16_funct.cpp
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
Filter::convert_bufs_from_y16 ()
{
  syn::IVideoBuf::raw_ptr l     = (*pbuf_)[::utils::dbufs::video::consts::offs::lit];
  syn::IVideoBuf::raw_ptr rcbuf = (*pbuf_)[::utils::dbufs::video::consts::offs::raw];

  l->clone (rcbuf, 100.0f);
  l->set_mem_var (
    ::utils::dbufs::MemVars::size_data,
    l->get_dim_var (::utils::dbufs::video::Dims::height) * l->get_dim_var (::utils::dbufs::video::Dims::stride));

#if 0
  //debug
  l->fill (rand () % 255);
#endif
}
}   // namespace dlls::convertors::all2hsl
