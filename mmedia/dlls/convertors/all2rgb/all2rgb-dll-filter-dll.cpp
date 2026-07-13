/**
\file       all2rgb-dll-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_all2rgb
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "all2rgb-dll-includes_int.hpp"
#include "all2rgb-dll-info-filter-dll.hpp"
#include "all2rgb-dll-filter-dll.hpp"

namespace dlls::convertors::all2rgb
{
void
Filter::alloc_temp_bufs ()
{
  const auto          sbuf          = (*pbuf_)[finfo_.rprops_->buf_.indx_sbuf_];
  const auto          source_format = sbuf->get_format ();
  const auto          px_format     = is_result_mono (source_format) ? syn::id_val::y16 : syn::id_val::rgb24;
  const std::uint32_t byte2px       = ::libs::utility::uids::helpers::get_count_bytes_from_format (px_format);
  const auto          swidth        = sbuf->get_dim_var (::utils::dbufs::video::Dims::width);
  const auto          sheight       = sbuf->get_dim_var (::utils::dbufs::video::Dims::height);
  const std::uint32_t req_stride    = ::libs::utility::mem::align_value (swidth * byte2px, 64U, true);
  const std::uint32_t req_size      = req_stride * sheight;

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
      auto alloc_info = ::utils::dbufs::video::AllocParams (
        swidth,
        sheight,
        0,
        syn::id_val::y16,
        utils::dbufs::video::DimChecks::enable);

      alloc_info.flags_[::utils::dbufs::BufFlags::convolution_support] = true;
      tbuf->buf_alloc (alloc_info);
      tbuf->set_mem_var (::utils::dbufs::MemVars::size_data, req_size);
    }
    else
    {
      tbuf->buf_alloc (
        ::utils::dbufs::video::AllocParams (
          swidth, sheight, req_stride, px_format));

      ::utils::dbufs::video::helpers::replace_buf_params (*tbuf, 0, req_size);
    }
  }
}


auto
Filter::is_result_mono (const syn::id_val& format) const -> bool
{
  //< see Filter::get_func_for_format
  const bool mono_support = format != syn::id_val::rgb32 && format != syn::id_val::rgb24;
  return finfo_.rprops_->strip_color_ && mono_support;
}


auto
Filter::get_func_for_format (const syn::id_val& format) -> ::libs::optim::io::hioptim*
{
  const auto mono = is_result_mono (format);
  if (syn::id_val::yuy2 == format || syn::id_val::yuyv == format)
  {
    return mono ? &yuy2_to_y16_ : &yuy2_to_rgb24_;
  }
  if (syn::id_val::ycb == format)
  {
    return mono ? &yuy2_to_y16_ : &ycb_to_rgb24_;
  }
  if (syn::id_val::uyvy == format)
  {
    return mono ? &uyvy_to_y16_ : &uyvy_to_rgb24_;
  }
  if (syn::id_val::nv21 == format)
  {
    return mono ? &nv21_to_y16_ : &nv21_to_rgb24_;
  }
  if (syn::id_val::i420 == format)
  {
    return mono ? &nv21_to_y16_ : &i420_to_rgb24_;
  }
  if (syn::id_val::rgb32 == format)
  {
    U3_CHECK (!mono, "result mono for rgb32");
    return &rgb32_to_rgb24_;
  }
  U3_LOG_DATA_ERROR ("unknown pixel format");
  return nullptr;
}


auto
Filter::get_out_format_from_format (const syn::id_val& format) -> syn::id_val
{
  return is_result_mono (format) ? syn::id_val::y16 : syn::id_val::rgb24;
}


void
Filter::init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info)
{
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);

  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}


void
Filter::convert_bufs ()
{
  auto       base_buf  = (*pbuf_)[finfo_.rprops_->buf_.indx_sbuf_];
  const auto pixformat = base_buf->get_format ();
  auto       rcbuf     = (*pbuf_)[finfo_.rprops_->buf_.indx_dbuf_];
  auto       tempbuf   = (*pbuf_)[::utils::dbufs::video::consts::offs::temp1];

  ::libs::optim::io::MCallInfo      cinfo;
  ::libs::optim::mcalls::MTFuncInfo tfunc;

  cinfo.srcs_.emplace_back (rcbuf, "rcbuf dlls::convertors::all2rgb");
  cinfo.dsts_.emplace_back (tempbuf, "tbuf dlls::convertors::all2rgb");

  tempbuf->set_format (get_out_format_from_format (pixformat));

  tfunc.pfunc_           = get_func_for_format (pixformat);
  tfunc.src_align_.px_x_ = tfunc.pfunc_->get_block_align_x ();
  tfunc.dst_align_.px_x_ = tfunc.pfunc_->get_block_align_x ();
  tfunc.src_align_.px_y_ = tfunc.pfunc_->get_block_align_y ();
  tfunc.dst_align_.px_y_ = tfunc.pfunc_->get_block_align_y ();

  if (!finfo_.rprops_->debug_skip_transform_)
  {
    pthreads_->mthreads_call (id_obj_, tfunc, cinfo, transinfo_->exptimes_);
  }

  // rcbuf->c1lone( tempbuf, 100.0F );
  rcbuf->swap (*tempbuf);

  if (is_result_mono (pixformat))
  {
    (*pbuf_)[::utils::dbufs::video::consts::offs::hue]->flush ();
    (*pbuf_)[::utils::dbufs::video::consts::offs::sat]->flush ();
  }
}


void
Filter::itransform ()
{
  alloc_temp_bufs ();
  convert_bufs ();
}
}   // namespace dlls::convertors::all2rgb
