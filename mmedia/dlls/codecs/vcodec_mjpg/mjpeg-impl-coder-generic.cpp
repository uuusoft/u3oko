/**
\file       mjpeg-impl-coder-generic.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2017
\project    u3_vcodec_mjpg
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcodec-mjpg-includes_int.hpp"
#include "mjpeg-impl.hpp"

namespace dlls::codecs::vcodec_mjpg
{
bool
MjpegImpl::code_int (
  const ::libs::bufs::Bufs*         src,
  ::libs::bufs::Bufs*               dst,
  syn::TransformInfo::tevents_type* events)
{
  const syn::IVideoBuf::raw_ptr  obuf = (*dst)[cinfo_.bufs_.indx_dbuf_];
  const syn::IVideoBuf::craw_ptr hbuf = (*src)[utils::dbufs::video::consts::offs::hue];
  const syn::IVideoBuf::craw_ptr sbuf = (*src)[utils::dbufs::video::consts::offs::sat];
  const syn::IVideoBuf::craw_ptr lbuf = (*src)[cinfo_.bufs_.indx_sbuf_];
  U3_ASSERT (lbuf);

  const auto lbuf_width  = lbuf->get_dim_var (::utils::dbufs::video::Dims::width);
  const auto lbuf_height = lbuf->get_dim_var (::utils::dbufs::video::Dims::height);
  const auto lbuf_stride = lbuf->get_dim_var (::utils::dbufs::video::Dims::stride);

  obuf->buf_alloc (syn::AllocBufInfo (lbuf_width, lbuf_height, 0, ::libs::helpers::uids::minor::id_val::rgb24));
  ::utils::dbufs::video::helpers::override_data (*obuf, 0, 0);

  ::libs::optim::io::ProxyBuf thbuf (hbuf && (*hbuf)[::utils::dbufs::MemVars::size_data] ? hbuf : nullptr, "hbuf dlls::codecs::vcodec_mjpg");
  ::libs::optim::io::ProxyBuf tsbuf (sbuf && (*sbuf)[::utils::dbufs::MemVars::size_data] ? sbuf : nullptr, "sbuf dlls::codecs::vcodec_mjpg");
  ::libs::optim::io::ProxyBuf tlbuf (lbuf, "lbuf dlls::codecs::vcodec_mjpg");
  ::libs::optim::io::ProxyBuf tout_buf (obuf, "obuf dlls::codecs::vcodec_mjpg");

  std::int32_t out_size    = 0;
  const bool   exist_color = thbuf.self_test () && tsbuf.self_test ();
  const bool   use_color   = exist_color && !cinfo_.plane_.nocolor_;

  if (use_color)
  {
    temp_buf_->buf_alloc (
      syn::AllocBufInfo (
        lbuf_width,
        lbuf_height,
        0,
        ::libs::helpers::uids::minor::id_val::rgb24));

    const auto                        stride_temp_buf = temp_buf_->get_dim_var (utils::dbufs::video::Dims::stride);
    std::int32_t                      stride_rgb24    = stride_temp_buf;
    ::libs::optim::io::MCallInfo      cinfo;
    ::libs::optim::mcalls::InfoMFunct tfunct (&fhsl_to_rgb24_);

    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (temp_buf_.get (), "temp_buf dlls::codecs::vcodec_mjpg"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (hbuf, "hbuf dlls::codecs::vcodec_mjpg"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (sbuf, "sbuf dlls::codecs::vcodec_mjpg"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (lbuf, "lbuf dlls::codecs::vcodec_mjpg"));

    cinfo.params_.pints_.push_back (&stride_rgb24);

    pthreads_->mthreads_call (*id_node_graph_, tfunct, cinfo, transinfo_->exptimes_, 0);
    U3_ASSERT (stride_rgb24 == U3_CAST_INT32 (stride_temp_buf));
  }
  else
  {
    temp_buf_->buf_alloc (
      syn::AllocBufInfo (
        lbuf_width,
        lbuf_height,
        lbuf_stride,
        ::libs::helpers::uids::minor::id_val::y8));

    ::libs::optim::io::MCallInfo cinfo;

    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (lbuf, "lbuf dlls::codecs::vcodec_mjpg"));
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (temp_buf_.get (), "temp_buf dlls::codecs::vcodec_mjpg"));

    ::libs::optim::mcalls::InfoMFunct tfunct (&fx16_x8_);
    pthreads_->mthreads_call (*id_node_graph_, tfunct, cinfo, transinfo_->exptimes_);
  }

  const bool ret = comp_iframe (use_color, tout_buf, out_size);
  U3_ASSERT (out_size > 0);
  obuf->set_mem_var (::utils::dbufs::MemVars::size_data, out_size);
  return ret;
}
}   // namespace dlls::codecs::vcodec_mjpg
