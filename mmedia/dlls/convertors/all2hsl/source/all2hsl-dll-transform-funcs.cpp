/**
\file       all2hsl-dll-transform-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
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
Filter::itransform ()
{
  alloc_bufs ();

  auto       rcbuf  = (*pbuf_)[::utils::dbufs::video::consts::offs::raw];
  const auto format = rcbuf->get_format ();

  if (rcbuf->get_flag (::utils::dbufs::BufFlags::empty))
  {
    return;
  }

  if (::libs::helpers::uids::minor::id_val::rgb24 == format)
  {
    convert_bufs_from_rgb ();
  }
  else if (::libs::helpers::uids::minor::id_val::y8 == format)
  {
    convert_bufs_from_y8 ();
  }
  else if (::libs::helpers::uids::minor::id_val::y16 == format)
  {
    convert_bufs_from_y16 ();
  }
  else
  {
    U3_LOG_DATA_ERROR ("unknown raw format - skip convert: " + ::libs::helpers::uids::helpers::get_readable_name (format));
    return;
  }

  flip_y_bufs ();
  duplicate_bufs ();
  alloc_temp_bufs ();

  if (finfo_.strip_color_)
  {
    (*pbuf_)[::utils::dbufs::video::consts::offs::hue]->flush ();
    (*pbuf_)[::utils::dbufs::video::consts::offs::sat]->flush ();
  }
  else
  {
    ::utils::dbufs::video::helpers::fill_edges ((*pbuf_)[::utils::dbufs::video::consts::offs::hue]);
    ::utils::dbufs::video::helpers::fill_edges ((*pbuf_)[::utils::dbufs::video::consts::offs::sat]);
  }

  ::utils::dbufs::video::helpers::fill_edges ((*pbuf_)[::utils::dbufs::video::consts::offs::lit]);
}
}   // namespace dlls::convertors::all2hsl
