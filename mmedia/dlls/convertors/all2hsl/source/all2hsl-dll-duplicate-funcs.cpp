/**
\file       all2hsl-dll-duplicate_funcs.cpp
\author     Erashov Anton erashov2026@proton.me
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
Filter::duplicate_bufs ()
{
  if (!finfo_.rprops_->duplicate_image_)
  {
    return;
  }

  const syn::IVideoBuf::raw_ptr l16_buf      = (*pbuf_)[::utils::dbufs::video::consts::offs::lit];
  syn::IVideoBuf::raw_ptr       copy_l16_buf = (*pbuf_)[consts::dupl_l];

  copy_l16_buf->clone (l16_buf, 100.0f);

  if (finfo_.strip_color_)
  {
    return;
  }

  const syn::IVideoBuf::raw_ptr h16_buf      = (*pbuf_)[::utils::dbufs::video::consts::offs::hue];
  const syn::IVideoBuf::raw_ptr s16_buf      = (*pbuf_)[::utils::dbufs::video::consts::offs::sat];
  syn::IVideoBuf::raw_ptr       copy_h16_buf = (*pbuf_)[consts::dupl_h];
  syn::IVideoBuf::raw_ptr       copy_s16_buf = (*pbuf_)[consts::dupl_s];

  copy_h16_buf->clone (h16_buf, 100.0f);
  copy_s16_buf->clone (s16_buf, 100.0f);
}
}   // namespace dlls::convertors::all2hsl
