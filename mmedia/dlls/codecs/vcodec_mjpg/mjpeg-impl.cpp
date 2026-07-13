/**
\file       mjpeg-impl.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2017
\project    u3_vcodec_mjpg
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "vcodec-mjpg-includes_int.hpp"
#include "mjpeg-impl.hpp"
#include "mmedia/dlls/doptim/algs/all_algs.hpp"

namespace dlls::codecs::vcodec_mjpg
{
MjpegImpl::MjpegImpl ()
{
  pthreads_ = ::libs::iproperties::helpers::get_shared_prop_os ()->get_mcalls_lockfree ();
  simd_     = ::libs::utility::sys::cpu::CpuExts::usual;
}


MjpegImpl::~MjpegImpl ()
{
  if (jpeg_buf_)
  {
    tjFree (jpeg_buf_);
    jpeg_buf_ = nullptr;
  }

  if (hjpeg_)
  {
    tjDestroy (hjpeg_);
    hjpeg_ = nullptr;
  }
}


void
MjpegImpl::update_coder (const unsigned long max_size)
{
  if (!hjpeg_)
  {
    hjpeg_ = tjInitCompress ();
    U3_CHECK_TURBO_JPEG (hjpeg_, "tjInitCompress");
  }

  if (!jpeg_buf_ || max_size > size_jpeg_buf_)
  {
    if (jpeg_buf_)
    {
      tjFree (jpeg_buf_);
      jpeg_buf_ = nullptr;
    }

    jpeg_buf_      = tjAlloc (U3_CAST_INT32 (max_size));
    size_jpeg_buf_ = max_size;
  }
}


void
MjpegImpl::update_decoder ()
{
  if (hjpeg_)
  {
    return;
  }

  hjpeg_ = tjInitDecompress ();
  U3_CHECK_TURBO_JPEG (hjpeg_, "tjInitDecompress");
}


auto
MjpegImpl::comp_iframe (
  bool                         colored,
  ::libs::optim::io::ProxyBuf& dst,
  std::int32_t&                out_size) -> bool
{
  dst.check ("dst dlls::codecs::vcodec_mjpg");

  std::uint8_t*                     dbuf        = dst.ubuf ();
  auto*                             head        = ::libs::utility::casts::reinterpret_cast_helper< syn::HeaderIFrame* > (dbuf);
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
    libs::utility::casts::reinterpret_cast_helper< const std::uint8_t* > (cur_buf),
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
  ::libs::utility::mem::mem_copy_raw (jpeg_buf_, dbuf + out_size, jpeg_size);

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

  // libs::utility::utils::cuuid_to_buf (::libs::utility::uids::codecs::mjpeg, head->base_part_.guid_);
  head->base_part_.guid_ = ::libs::utility::uids::minor::id_val::mjpeg;

  U3_ASSERT (head->check ());
  statistic_.update ("iframe", jpeg_size);
  return true;
}


auto
convert_jpeg2guid_px_format (const std::int32_t jpeg_px) -> ::libs::utility::uids::minor::id_val
{
  auto ret = ::libs::utility::uids::minor::id_val::rgb24;

  switch (jpeg_px)
  {
  case TJCS_RGB:
    ret = ::libs::utility::uids::minor::id_val::rgb24;
    break;
  case TJCS_YCbCr:
    ret = ::libs::utility::uids::minor::id_val::ycb;
    break;
  case TJCS_GRAY:
    ret = ::libs::utility::uids::minor::id_val::y8;
    break;
  case TJCS_CMYK:
  case TJCS_YCCK:
    // U3_LOG_DATA_WRN ("unsupported color space jpeg" + VTOLOG (jpeg_px));
    break;
  default:
    // U3_LOG_DATA_WRN ("unkown color space jpeg" + VTOLOG (jpeg_px));
    break;
  }
  return ret;
}


auto
MjpegImpl::decomp_iframe (
  const syn::HeaderIFrame*           head,
  const ::libs::optim::io::ProxyBuf& src,
  const std::int32_t                 src_size) -> bool
{
  const auto&         base_head    = head->base_part_;
  const auto&         info_head    = base_head.sinfo_;
  const std::uint8_t* sdata        = src.ubuf () + head->base_part_.size_;
  const std::uint8_t* cdata        = sdata + head->coff_;
  std::uint32_t       src_size_res = head->csize_;
  std::int32_t        codec_error  = 0;

  try
  {
    // debug
    //::dlls::codecs::codec_gen::dump (head);
    update_decoder ();

    {
      std::int32_t jpeg_width   = 0;
      std::int32_t jpeg_height  = 0;
      std::int32_t jpeg_subsamp = 0;
      std::int32_t jpeg_px      = 0;

      U3_CHECK_TURBO_JPEG (0 == tjDecompressHeader3 (hjpeg_, cdata, src_size_res, &jpeg_width, &jpeg_height, &jpeg_subsamp, &jpeg_px), "tjDecompressHeader3");
      temp_buf_->set_format (convert_jpeg2guid_px_format (jpeg_px));
    }

    const auto request_pixel_format = cinfo_.plane_.nocolor_ ? TJPF_GRAY : (head->cinfo_.nocolor_ ? TJPF_GRAY : TJPF_RGB);

    codec_error = tjDecompress2 (
      hjpeg_,
      cdata,
      src_size_res,
      temp_buf_->get_buf (),
      info_head.width_,
      info_head.stride_,
      info_head.height_,
      request_pixel_format,
      0);

    U3_CHECK_TURBO_JPEG (0 == codec_error, "tjDecompress2");

    const auto px_format  = temp_buf_->get_format ();
    const auto stride_res = info_head.width_ * ::libs::utility::uids::helpers::get_count_bytes_from_format (px_format);
    const auto size_res   = info_head.height_ * stride_res;

    temp_buf_->set_flag (utils::dbufs::BufFlags::empty, false);
    temp_buf_->set_mem_var (::utils::dbufs::MemVars::size_data, size_res);
    temp_buf_->set_dim_var (utils::dbufs::video::Dims::stride, stride_res);
  }
  catch (std::exception& excpt)
  {
    U3_LOG_DATA_EXCEPT (std::string (excpt.what ()) + ", " + tjGetErrorStr () + VTOLOG (codec_error));
    return false;
  }
  return true;
}
}   // namespace dlls::codecs::vcodec_mjpg
