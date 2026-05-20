/**
\file       mjpeg-impl-decoder-iframe.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_vcodec_mjpg
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcodec-mjpg-includes_int.hpp"
#include "mjpeg-impl.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buf_helpers_funcs.hpp"

namespace dlls::codecs::vcodec_mjpg
{
::libs::helpers::uids::minor::id_val
convert_jpeg2guid_px_format (const std::int32_t jpeg_px)
{
  auto ret = ::libs::helpers::uids::minor::id_val::rgb24;

  switch (jpeg_px)
  {
  case TJCS_RGB:
    ret = ::libs::helpers::uids::minor::id_val::rgb24;
    break;
  case TJCS_YCbCr:
    ret = ::libs::helpers::uids::minor::id_val::ycb;
    break;
  case TJCS_GRAY:
    ret = ::libs::helpers::uids::minor::id_val::y8;
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


bool
MjpegImpl::decomp_iframe (
  const syn::HeaderIFrame*           head,
  const ::libs::optim::io::ProxyBuf& src,
  const std::int32_t                 src_size)
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
    const auto stride_res = info_head.width_ * ::libs::helpers::uids::helpers::get_count_bytes_from_format (px_format);
    const auto size_res   = info_head.height_ * stride_res;

    temp_buf_->set_flag (utils::dbufs::BufFlags::empty, false);
    temp_buf_->set_mem_var (::utils::dbufs::MemVars::size_data, size_res);
    temp_buf_->set_dim_var (utils::dbufs::video::Dims::stride, stride_res);
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (std::string (e.what ()) + ", " + tjGetErrorStr () + VTOLOG (codec_error));
    return false;
  }
  return true;
}
}   // namespace dlls::codecs::vcodec_mjpg
