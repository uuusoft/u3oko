/**
\file       mjpeg-impl-decoder-generic.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_vcodec_mjpg
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcodec-mjpg-includes_int.hpp"
#include "mjpeg-impl.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buf_helpers_funcs.hpp"

namespace dlls::codecs::vcodec_mjpg
{
bool
MjpegImpl::decode_int (
  const ::libs::bufs::Bufs*         src,
  ::libs::bufs::Bufs*               dst,
  syn::TransformInfo::tevents_type* events)
{
  const syn::IVideoBuf::craw_ptr compbuf   = (*src)[cinfo_.bufs_.indx_sbuf_];
  const auto                     compsize  = (*compbuf)[::utils::dbufs::MemVars::size_data];
  auto                           head      = U3_CAST_CODECS< const syn::HeaderIFrame* > (utils::dbufs::video::helpers::get_const_data (compbuf));
  const bool                     use_color = !head->cinfo_.nocolor_;
  const auto&                    base_head = head->base_part_;
  const auto&                    info_head = base_head.sinfo_;

#if 0
  //debug
  ::dlls::codecs::codec_gen::dump (head);
  ::utils::dbufs::video::helpers::dump (compbuf);
#endif

  if (compsize < sizeof (syn::HeaderIFrame) || !head->check ())
  {
    U3_XLOG_ERROR ("data less header" + VTOLOG (compsize) + VTOLOG (sizeof (syn::HeaderIFrame)));
    U3_XLOG_ERROR ("invalid header compress frame");
    return false;
  }

  auto dbuf = (*dst)[cinfo_.bufs_.indx_dbuf_];
  if (!dbuf)
  {
    // U3_LOG_DATA_WRN ("receive invalid destination buf, skip" + TOLOG (cinfo_.bufs_.indx_dbuf_));
    return false;
  }

  const auto stride_alloc = info_head.width_ * ::libs::helpers::uids::helpers::get_count_bytes_from_format (::libs::helpers::uids::minor::id_val::rgb32);   //
  const auto px_preformat = use_color ? ::libs::helpers::uids::minor::id_val::rgb24 : ::libs::helpers::uids::minor::id_val::y8;

  temp_buf_->buf_alloc (syn::AllocBufInfo (info_head.width_, info_head.height_, stride_alloc, px_preformat));
  temp_buf_->set_flag (utils::dbufs::BufFlags::empty, true);
  dbuf->set_flag (utils::dbufs::BufFlags::empty, true);

#if 0
  //debug
  ::utils::dbufs::video::helpers::dump (&*temp_buf_);
#endif

  ::libs::optim::io::ProxyBuf tsrc (compbuf, "compbuf dlls::codecs::vcodec_mjpg");
  tsrc.check ("tsrc dlls::codecs::vcodec_mjpg");

  const bool ret = decomp_iframe (head, tsrc, compsize);
  if (temp_buf_->get_flag (utils::dbufs::BufFlags::empty))
  {
    // U3_LOG_DATA_ERROR ("decompress buf, skip");
    return false;
  }

  dbuf->clone (temp_buf_.get (), 100.0f);
  dst->set_flag (::libs::bufs::BufsFlags::request2hsl, true);
  return ret;
}
}   // namespace dlls::codecs::vcodec_mjpg
