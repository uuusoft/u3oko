/**
\file       vcodec-x264-impl-coder-generic.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.08.2018
\project    u3_vcodec_x264
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "vcodec-x264-impl.hpp"

namespace dlls::codecs::vcodec_x264
{
bool
x264Impl::code_int (
  const ::libs::bufs::Bufs*         src,
  ::libs::bufs::Bufs*               dst,
  syn::TransformInfo::tevents_type* events)
{
  const syn::IVideoBuf::raw_ptr  obuf = (*dst)[cinfo_.bufs_.indx_dbuf_];
  const syn::IVideoBuf::craw_ptr hbuf = (*src)[utils::dbufs::video::consts::offs::hue];
  const syn::IVideoBuf::craw_ptr sbuf = (*src)[utils::dbufs::video::consts::offs::sat];
  const syn::IVideoBuf::craw_ptr lbuf = (*src)[cinfo_.bufs_.indx_sbuf_];
  U3_ASSERT (lbuf);
  const syn::AllocBufInfo current_frame_info (lbuf->get_dim_vars (), ::libs::helpers::uids::minor::id_val::rgb32);

  if (coder_frame_info_.geom_dims_[::utils::dbufs::video::Dims::width] != current_frame_info.geom_dims_[::utils::dbufs::video::Dims::width] ||
      coder_frame_info_.geom_dims_[::utils::dbufs::video::Dims::height] != current_frame_info.geom_dims_[::utils::dbufs::video::Dims::height])
  {
    coder_frame_info_ = current_frame_info;
    coder_impl_->destroy_coder ();
    coder_impl_->create_coder (cinfo_, coder_frame_info_);
  }

  obuf->buf_alloc (current_frame_info);

  ::utils::dbufs::video::helpers::override_data (*obuf, 0, 0);

  ::libs::optim::io::ProxyBuf thbuf (hbuf && (*hbuf)[::utils::dbufs::MemVars::size_data] ? hbuf : nullptr, "hbuf x264Impl::code_int");
  ::libs::optim::io::ProxyBuf tsbuf (sbuf && (*sbuf)[::utils::dbufs::MemVars::size_data] ? sbuf : nullptr, "sbuf x264Impl::code_int");
  ::libs::optim::io::ProxyBuf tlbuf (lbuf, "tlbuf x264Impl::code_int");
  const bool                  exist_color = thbuf.self_test () && tsbuf.self_test ();
  const bool                  nocolor     = !exist_color || cinfo_.plane_.nocolor_;

  if (nocolor)
  {
    src_buf_->buf_alloc (syn::AllocBufInfo (lbuf->get_dim_vars (), ::libs::helpers::uids::minor::id_val::y8));

    ::libs::optim::io::MCallInfo cinfo;

    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (lbuf, "lbuf x264Impl::code_int"));
    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (src_buf_.get (), "src_buf x264Impl::code_int"));

    ::libs::optim::mcalls::InfoMFunct tfunct (&fx16_x8_);

    pthreads_->mthreads_call (*id_node_graph_, tfunct, cinfo, transinfo_->exptimes_);
#if 0
    // debug
    ::utils::dbufs::video::helpers::fill (src_buf_.get (), rand () % 256);
#endif
  }
  else
  {
#if 1
    src_buf_->buf_alloc (
      syn::AllocBufInfo (
        lbuf->get_dim_var (::utils::dbufs::video::Dims::width),
        lbuf->get_dim_var (::utils::dbufs::video::Dims::height),
        0,
        ::libs::helpers::uids::minor::id_val::rgb24));

    int32_t                           stride_rgb24 = 0;
    ::libs::optim::io::MCallInfo      cinfo;
    ::libs::optim::mcalls::InfoMFunct tfunct (&fhsl_to_rgb24_);

    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (src_buf_.get (), "src_buf x264Impl::code_int"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (hbuf, "hbuf x264Impl::code_int"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (sbuf, "sbuf x264Impl::code_int"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (lbuf, "lbuf"));

    cinfo.params_.pints_.push_back (&stride_rgb24);

    pthreads_->mthreads_call (
      *id_node_graph_,
      tfunct,
      cinfo,
      transinfo_->exptimes_,
      0);

    U3_ASSERT (stride_rgb24 == U3_CAST_INT32 (src_buf_->get_dim_var (utils::dbufs::video::Dims::stride)));
#else
    src_buf_->buf_alloc (
      syn::AllocBufInfo (
        lbuf->get_dim_var (::utils::dbufs::video::Dims::width),
        lbuf->get_dim_var (::utils::dbufs::video::Dims::height),
        0,
        ::libs::helpers::uids::minor::id_val::rgb24));

    int                               stride_rgb24 = 0;
    ::libs::optim::io::MCallInfo      cinfo;
    ::libs::optim::mcalls::InfoMFunct tfunct (&fhsl_to_rgb24_);

    cinfo.dsts_.push_back (::libs::optim::io::ProxyBuf (src_buf_.get (), "src_buf x264Impl::code_int"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (hbuf, "hbuf x264Impl::code_int"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (sbuf, "sbuf x264Impl::code_int"));
    cinfo.srcs_.push_back (::libs::optim::io::ProxyBuf (lbuf, "lbuf"));

    cinfo.params_.pints_.push_back (&stride_rgb24);

    pthreads_->mthreads_call (*id_node_graph_, tfunct, cinfo, transinfo_->exptimes_, 0);
    U3_ASSERT (stride_rgb24 == U3_CAST_INT32 (src_buf_->get_dim_var (utils::dbufs::video::Dims::stride)));
#endif
  }

  impls::EncodeFrameState state (src_buf_.get (), obuf, nocolor);
  const bool              ret = coder_impl_->compress_frame (cinfo_, state);
  return ret;
}
}   // namespace dlls::codecs::vcodec_x264
