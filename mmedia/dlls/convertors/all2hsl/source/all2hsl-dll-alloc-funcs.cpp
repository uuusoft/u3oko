/**
\file       all2hsl-dll-alloc-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "all2hsl-dll-includes_int.hpp"
#include "all2hsl-dll-info-filter-dll.hpp"
#include "all2hsl-dll-filter-dll.hpp"

namespace dlls::convertors::all2hsl
{
void
Filter::alloc_bufs ()
{
  syn::IVideoBuf::raw_ptr braw     = (*pbuf_)[::utils::dbufs::video::consts::offs::raw];
  auto                    base_buf = (*pbuf_)[pbuf_->get_base_index ()];
  const auto              width    = base_buf->get_dim_var (::utils::dbufs::video::Dims::width);
  const auto              height   = base_buf->get_dim_var (::utils::dbufs::video::Dims::height);
  // const auto              format    = base_buf->get_format ();

  finfo_.strip_color_ = finfo_.rprops_->strip_color_ || (::libs::helpers::uids::minor::id_val::rgb24 != braw->get_format ());

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

    auto alloc_info = ::utils::dbufs::video::AllocBufInfo (
      width,
      height,
      0,
      ::libs::helpers::uids::minor::id_val::y16,
      utils::dbufs::video::DimChecks::enable);

    alloc_info.flags_[::utils::dbufs::BufFlags::convolution_support] = true;
    cbuf->buf_alloc (alloc_info);
  }
}


void
Filter::alloc_temp_bufs ()
{
  //  Резервируем память под второстепенные буфера, связанные с основным.
#if 0
  const syn::IVideoBuf::raw_ptr                            l16_buf     = (*pbuf_)[::utils::dbufs::video::consts::offs::lit];
  const ::utils::dbufs::video::consts::offs::off_buf_type indx_bufs[] = { ::utils::dbufs::video::consts::offs::temp1, ::utils::dbufs::video::consts::offs::temp2 };

  for (const ::utils::dbufs::video::consts::offs::off_buf_type& indx_buf : indx_bufs)
  {
    syn::IVideoBuf::raw_ptr tbuf = (*pbuf_)[indx_buf];
    tbuf->clone (l16_buf, 0.0f);
  }
#endif
}
}   // namespace dlls::convertors::all2hsl
