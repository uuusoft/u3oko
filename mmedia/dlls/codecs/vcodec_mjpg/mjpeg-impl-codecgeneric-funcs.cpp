/**
\file       mjpeg-impl-codecgeneric-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_vcodec_mjpg
*/
#include "vcodec-mjpg-includes_int.hpp"
#include "mjpeg-impl.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buf_helpers_funcs.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::codecs::vcodec_mjpg
{
void
MjpegImpl::set_codec_info_int (const syn::VideoCodecProp* cinfo)
{
  cinfo_.copy (cinfo);
}


void
MjpegImpl::get_codec_info_int (syn::VideoCodecProp* ret_info)
{
  ret_info->copy (&cinfo_);
}


void
MjpegImpl::set_cpu_int (::libs::utility::sys::cpu::CpuExts optim)
{
}


void
MjpegImpl::init_int (const codec_gen::InfoGenCodec& info)
{
  info.check ();
  iinfo_ = info;

  auto ioptim = ::libs::iproperties::helpers::cast_prop_demons ()->get_optim_lockfree ()->impl ();

  fx16_x8_       = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX16_X8Alg::val_key));
  fx8_x16_       = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CX8_X16Alg::val_key));
  fhsl_to_rgb24_ = ioptim->get (::libs::optim::io::qoptim (::dlls::doptim::impl::algs::CHSL2RgbAlg::val_key));

  auto ibuf = ::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ();
  temp_buf_ = ibuf->create (0);
}


auto
MjpegImpl::get_statistic_info_int () const -> const syn::StatisticInfo&
{
  return statistic_;
}


void
MjpegImpl::reset_statistic_info_int ()
{
  statistic_.reset ();
}


auto
MjpegImpl::code_int (
  const ::libs::bufs::Bufs*         src,
  ::libs::bufs::Bufs*               dst,
  syn::TransformInfo::tevents_type* events) -> bool
{
  U3_LOG_DATA_DBG ("MjpegImpl::code_int:---->");
  const syn::IVideoBuf::raw_ptr  obuf = (*dst)[cinfo_.bufs_.indx_dbuf_];
  const syn::IVideoBuf::craw_ptr hbuf = (*src)[utils::dbufs::video::consts::offs::hue];
  const syn::IVideoBuf::craw_ptr sbuf = (*src)[utils::dbufs::video::consts::offs::sat];
  const syn::IVideoBuf::craw_ptr lbuf = (*src)[cinfo_.bufs_.indx_sbuf_];
  U3_ASSERT (lbuf);

  const auto lbuf_width  = lbuf->get_dim_var (::utils::dbufs::video::Dims::width);
  const auto lbuf_height = lbuf->get_dim_var (::utils::dbufs::video::Dims::height);
  const auto lbuf_stride = lbuf->get_dim_var (::utils::dbufs::video::Dims::stride);

  obuf->buf_alloc (syn::AllocParams (lbuf_width, lbuf_height, 0, ::libs::utility::uids::minor::id_val::rgb24));
  ::utils::dbufs::video::helpers::replace_buf_params (*obuf, 0, 0);

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
      syn::AllocParams (
        lbuf_width,
        lbuf_height,
        0,
        ::libs::utility::uids::minor::id_val::rgb24));

    const auto                        stride_temp_buf = temp_buf_->get_dim_var (utils::dbufs::video::Dims::stride);
    std::int32_t                      stride_rgb24    = stride_temp_buf;
    ::libs::optim::io::MCallInfo      cinfo;
    ::libs::optim::mcalls::MTFuncInfo tfunc (&fhsl_to_rgb24_);

    cinfo.dsts_.emplace_back (temp_buf_.get (), "temp_buf dlls::codecs::vcodec_mjpg");
    cinfo.srcs_.emplace_back (hbuf, "hbuf dlls::codecs::vcodec_mjpg");
    cinfo.srcs_.emplace_back (sbuf, "sbuf dlls::codecs::vcodec_mjpg");
    cinfo.srcs_.emplace_back (lbuf, "lbuf dlls::codecs::vcodec_mjpg");

    cinfo.params_.pints_.push_back (&stride_rgb24);

    U3_LOG_DATA_DBG ("MjpegImpl::code_int: call fhsl_to_rgb24");
    pthreads_->mthreads_call (*id_node_graph_, tfunc, cinfo, transinfo_->exptimes_, 0);
    U3_ASSERT (stride_rgb24 == U3_CAST_INT32 (stride_temp_buf));
  }
  else
  {
    temp_buf_->buf_alloc (
      syn::AllocParams (
        lbuf_width,
        lbuf_height,
        lbuf_stride,
        ::libs::utility::uids::minor::id_val::y8));

    ::libs::optim::io::MCallInfo cinfo;

    cinfo.srcs_.emplace_back (lbuf, "lbuf dlls::codecs::vcodec_mjpg");
    cinfo.dsts_.emplace_back (temp_buf_.get (), "temp_buf dlls::codecs::vcodec_mjpg");

    U3_LOG_DATA_DBG ("MjpegImpl::code_int: call fx16_x8");
    ::libs::optim::mcalls::MTFuncInfo tfunc (&fx16_x8_);
    pthreads_->mthreads_call (*id_node_graph_, tfunc, cinfo, transinfo_->exptimes_);
  }

  const bool ret = comp_iframe (use_color, tout_buf, out_size);
  U3_ASSERT (out_size > 0);
  obuf->set_mem_var (::utils::dbufs::MemVars::size_data, out_size);
  U3_LOG_DATA_DBG ("MjpegImpl::code_int:<----");
  return ret;
}


auto
MjpegImpl::decode_int (
  const ::libs::bufs::Bufs*         src,
  ::libs::bufs::Bufs*               dst,
  syn::TransformInfo::tevents_type* events) -> bool
{
  const syn::IVideoBuf::craw_ptr compbuf   = (*src)[cinfo_.bufs_.indx_sbuf_];
  const auto                     compsize  = (*compbuf)[::utils::dbufs::MemVars::size_data];
  const auto*                    head      = ::libs::utility::casts::reinterpret_cast_helper< const syn::HeaderIFrame* > (utils::dbufs::video::helpers::get_const_data (compbuf));
  const bool                     use_color = !head->cinfo_.nocolor_;
  const auto&                    base_head = head->base_part_;
  const auto&                    info_head = base_head.sinfo_;

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
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

  auto* const dbuf = (*dst)[cinfo_.bufs_.indx_dbuf_];
  if (!dbuf)
  {
    // U3_LOG_DATA_WRN ("receive invalid destination buf, skip" + TOLOG (cinfo_.bufs_.indx_dbuf_));
    return false;
  }

  const auto stride_alloc = info_head.width_ * ::libs::utility::uids::helpers::get_count_bytes_from_format (::libs::utility::uids::minor::id_val::rgb32);   //
  const auto px_preformat = use_color ? ::libs::utility::uids::minor::id_val::rgb24 : ::libs::utility::uids::minor::id_val::y8;

  temp_buf_->buf_alloc (syn::AllocParams (info_head.width_, info_head.height_, stride_alloc, px_preformat));
  temp_buf_->set_flag (utils::dbufs::BufFlags::empty, true);
  dbuf->set_flag (utils::dbufs::BufFlags::empty, true);

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  // debug
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

  dbuf->clone (temp_buf_.get (), 100.0F);
  dst->set_flag (::libs::bufs::BufsFlags::request2hsl, true);
  return ret;
}
}   // namespace dlls::codecs::vcodec_mjpg
