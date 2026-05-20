/**
\file       mjpeg-impl-coder-iframe.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
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
MjpegImpl::comp_iframe (
  bool                         colored,
  ::libs::optim::io::ProxyBuf& dst,
  std::int32_t&                out_size)
{
  U3_LOG_DATA_DBG ("START dlls::codecs::vcodec_mjpg::MjpegImpl::comp_iframe" + PTR_TOLOG (hjpeg_));
  dst.check ("dst dlls::codecs::vcodec_mjpg");

  std::uint8_t*                     dbuf        = dst.ubuf ();
  auto                              head        = U3_CAST_CODECS< syn::HeaderIFrame* > (dbuf);
  std::int32_t                      from_header = 0;
  const ::libs::optim::io::ProxyBuf lsrc (temp_buf_.get (), "temp_buf dlls::codecs::vcodec_mjpg");
  const std::uint8_t*               cur_buf = temp_buf_->get_cbuf ();
  // EAI-REFACT
#ifdef U3_CPU_X86
  const std::int32_t in_format = colored ? TJPF_RGB : TJPF_GRAY;
#elif defined(U3_CPU_ARM)
  const std::int32_t in_format = colored ? TJPF_BGR : TJPF_GRAY;
#elif
#  error "unknown cpu type"
#endif
  const std::int32_t out_format = colored ? TJSAMP_444 : TJSAMP_GRAY;
  unsigned long      jpeg_size  = 0;
  unsigned long      max_size   = tjBufSize (lsrc.width_, lsrc.height_, out_format);

  out_size = sizeof (syn::HeaderIFrame);
  head->reset ();

  update_coder (max_size);

  const std::int32_t res_jpeg = tjCompress2 (
    hjpeg_,
    U3_CAST_REINTERPRET< const std::uint8_t* > (cur_buf),
    lsrc.width_,
    lsrc.stride_,
    lsrc.height_,
    in_format,
    &jpeg_buf_,
    &jpeg_size,
    out_format,
    cinfo_.plane_.quality_,
    TJFLAG_NOREALLOC | TJFLAG_FASTDCT | TJFLAG_BOTTOMUP);

  U3_CHECK_TURBO_JPEG_RET (-1 != res_jpeg, "tjCompress2", false);
  U3_LOG_DATA_DBG (VTOLOG (jpeg_size) + VTOLOG (out_size) + VTOLOG (dst.width_) + VTOLOG (dst.height_) + VTOLOG (dst.stride_));
  ::libs::helpers::mem::u3copy (jpeg_buf_, dbuf + out_size, jpeg_size);

  head->csize_ = jpeg_size;
  head->coff_  = from_header;
  from_header += jpeg_size;
  out_size += jpeg_size;
  U3_ASSERT (out_size > 0);

  auto& base_header = head->base_part_;
  auto& base_size   = base_header.sinfo_;

  base_header.size_compress_ = out_size;
  base_size.width_           = lsrc.width_;
  base_size.height_          = lsrc.height_;
  base_size.stride_          = lsrc.width_ * (colored ? 3 : 1);

  head->cinfo_          = cinfo_.plane_;
  head->cinfo_.nocolor_ = colored ? false : true;   // переопределяем по факту, т.к. у пользователя может быть установлено сжатие с цветом при его фактическом отсутствии и наоборот.

  // libs::helpers::utils::cuuid_to_buf (::libs::helpers::uids::codecs::mjpeg, head->base_part_.guid_);
  head->base_part_.guid_ = ::libs::helpers::uids::minor::id_val::mjpeg;

  U3_ASSERT (head->check ());
  statistic_.update ("iframe", jpeg_size);
  return true;
}
}   // namespace dlls::codecs::vcodec_mjpg
