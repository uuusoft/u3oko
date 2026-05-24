/**
\file       vcodec-x264-impl-decoder-generic.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.08.2018
\project    u3_vcodec_x264
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "vcodec-x264-impl.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buf_helpers_funcs.hpp"

namespace dlls::codecs::vcodec_x264
{
bool
x264Impl::decode_int (
  const ::libs::bufs::Bufs*         src,
  ::libs::bufs::Bufs*               dst,
  syn::TransformInfo::tevents_type* events)
{
  const syn::IVideoBuf::craw_ptr compbuf   = (*src)[cinfo_.bufs_.indx_sbuf_];
  const auto                     compsize  = (*compbuf)[::utils::dbufs::MemVars::size_data];
  const syn::HeaderIFrame*       head      = U3_CAST_CODECS< const syn::HeaderIFrame* > (utils::dbufs::video::helpers::get_const_data (compbuf));
  const auto&                    base_head = head->base_part_;
  const auto&                    info_head = base_head.sinfo_;

#if 0
  // const bool                                         use_color = !head->cinfo_.nocolor_;
  // debug
  ::dlls::codecs::codec_gen::dump (head);
  ::utils::dbufs::video::helpers::dump (compbuf);
#endif

  if (compsize < sizeof (syn::HeaderIFrame) || !head->check ())
  {
    U3_XLOG_ERROR ("data less header" + VTOLOG (compsize) + VTOLOG (sizeof (syn::HeaderIFrame)));
    U3_XLOG_ERROR ("invalid header compress frame");
    return false;
  }

  // auto dbuf = (*dst)[cinfo_.bufs_.indx_dbuf_];
  auto dbuf = (*dst)[::utils::dbufs::video::consts::offs::lit];   // debug
  if (!dbuf)
  {
    U3_LOG_DATA_WRN ("receive invalid destination buf, skip" + TOLOG (cinfo_.bufs_.indx_dbuf_));
    return false;
  }

  const auto stride_alloc = info_head.width_ * ::libs::helpers::uids::helpers::get_count_bytes_from_format (::libs::helpers::uids::minor::id_val::ycb);
  const auto px_preformat = ::libs::helpers::uids::minor::id_val::ycb;

  dbuf->buf_alloc (syn::AllocBufInfo (info_head.width_, info_head.height_, stride_alloc, px_preformat));
  dbuf->set_flag (utils::dbufs::BufFlags::empty, true);
  // dbuf->set_flag (utils::dbufs::BufFlags::empty, true);
  //::utils::dbufs::video::helpers::dump (&*src_buf_);      // debug

  ::libs::optim::io::ProxyBuf tsrc (compbuf, "tsrc x264Impl::decode_int");
  // debug
  //::utils::dbufs::video::helpers::fill (src_buf_.get (), 0);
  // src_buf_->set_flag (utils::dbufs::BufFlags::empty, false);
  //::utils::dbufs::video::helpers::fill_buf<char> (src_buf_.get (), [](long long indx, char& val) {
  // val = 0 + U3_CAST_INT8 (rand () % 101);
  // val = U3_CAST_INT8 (indx);
  //  return;
  // });
  //  src_buf_->set_flag (utils::dbufs::BufFlags::empty, true);
  std::uint8_t* ret_dst    = nullptr;
  std::uint32_t dst_stride = 0;
  std::uint32_t dst_width  = 0;
  std::uint32_t dst_height = 0;
  const bool    ret        = coder_impl_->decompress_frame (head, tsrc, compsize, dbuf, &ret_dst, dst_stride, dst_width, dst_height);

  if (ret_dst)
  {
    ::libs::optim::io::MCallInfo cinfo;
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (ret_dst, dst_stride, dst_width, dst_height, "lbuf x264Impl::code_int"));
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (dbuf, "src_buf x264Impl::code_int"));

    ::libs::optim::mcalls::InfoMFunct tfunct (&fx8_x16_);

    pthreads_->mthreads_call (*id_node_graph_, tfunct, cinfo, transinfo_->exptimes_);

    dbuf->set_mem_var (::utils::dbufs::MemVars::size_data, dst_stride * dst_height);
    dbuf->set_flag (utils::dbufs::BufFlags::empty, false);
  }

  if (src_buf_->get_flag (utils::dbufs::BufFlags::empty))
  {
    U3_LOG_DATA_WRN ("empty decompress buf, skip");
    return false;
  }
  // debug
  //::utils::dbufs::video::helpers::fill (src_buf_.get (), 0);
  // src_buf_->set_flag (utils::dbufs::BufFlags::empty, false);
  //::utils::dbufs::video::helpers::fill_buf<char> (src_buf_.get (), [](long long indx, char& val) {
  // val = 155 + U3_CAST_INT8 (rand () % 101);
  // val = U3_CAST_INT8 (indx);
  //  return;
  // });
  //::utils::dbufs::video::helpers::fill (src_buf_.get (), 0);
  //::utils::dbufs::video::helpers::fill<char> (src_buf_.get (), [](int x, int y, char& val) {
  // val = 155 + U3_CAST_INT8 (rand () % 101);
  //  return;
  // });
  // dbuf->clone (src_buf_.get (), 100.0f);
  dst->set_flag (::libs::bufs::BufsFlags::request2hsl, true);
  //  debug
  //::utils::dbufs::video::helpers::dump (&*src_buf_);
  //::utils::dbufs::video::helpers::dump (dbuf);
  // utils::dbufs::video::helpers::fill( braw, rand() % 256 );
  //::utils::dbufs::video::helpers::fill (dbuf, 0);      //   debug
  //::utils::dbufs::video::helpers::fill<char> (dbuf, [](int x, int y, char& val) {
  // val = 155 + U3_CAST_INT8 (rand () % 101);
  //  return;
  // });
  return ret;
}
}   // namespace dlls::codecs::vcodec_x264
