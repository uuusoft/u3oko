/**
\file       all2rgb-dll-alloc-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    uuu_all2rgb
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "all2rgb-dll-includes_int.hpp"
#include "all2rgb-dll-info-filter-dll.hpp"
#include "all2rgb-dll-filter-dll.hpp"

namespace dlls::convertors::all2rgb
{
void
Filter::alloc_bufs ()
{
}


void
Filter::alloc_temp_bufs ()
{
  const syn::IVideoBuf::raw_ptr sbuf          = (*pbuf_)[finfo_.rprops_->buf_.indx_sbuf_];
  const auto                    source_format = sbuf->get_format ();
  const auto                    px_format     = is_result_mono (source_format) ? ::libs::helpers::uids::minor::id_val::y16 : ::libs::helpers::uids::minor::id_val::rgb24;
  const std::uint32_t           byte2px       = ::libs::helpers::uids::helpers::get_count_bytes_from_format (px_format);
  const auto                    swidth        = sbuf->get_dim_var (::utils::dbufs::video::Dims::width);
  const auto                    sheight       = sbuf->get_dim_var (::utils::dbufs::video::Dims::height);
  const std::uint32_t           req_stride    = ::libs::helpers::mem::get_align64 (swidth * byte2px, true);
  const std::uint32_t           req_size      = req_stride * sheight;

  const ::utils::dbufs::video::consts::offs::off_buf_type indx_bufs[] = {
    ::utils::dbufs::video::consts::offs::temp1
  };

  for (const ::utils::dbufs::video::consts::offs::off_buf_type& indx_buf : indx_bufs)
  {
    syn::IVideoBuf::raw_ptr tbuf = (*pbuf_)[indx_buf];

    if (is_result_mono (source_format))
    {
      //  буфер Y16 напрямую используется далее, поэтому выделяем сразу со всеми отступами.
      //  U3-REFACT: compressed buf
      auto alloc_info = ::utils::dbufs::video::AllocBufInfo (
        swidth,
        sheight,
        0,
        ::libs::helpers::uids::minor::id_val::y16,
        utils::dbufs::video::DimChecks::enable);

      alloc_info.flags_[::utils::dbufs::BufFlags::convolution_support] = true;
      tbuf->buf_alloc (alloc_info);
      tbuf->set_mem_var (::utils::dbufs::MemVars::size_data, req_size);
    }
    else
    {
      tbuf->buf_alloc (
        ::utils::dbufs::video::AllocBufInfo (
          swidth, sheight, req_stride, px_format));

      ::utils::dbufs::video::helpers::override_data (*tbuf, 0, req_size);
    }
  }
}
}   // namespace dlls::convertors::all2rgb
