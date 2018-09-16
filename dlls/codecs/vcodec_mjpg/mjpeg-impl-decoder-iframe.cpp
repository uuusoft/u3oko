//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mjpeg-impl-decoder-iframe.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_vcodec_mjpg
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "mjpeg-impl.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buff_helpers_functs.hpp"

namespace dlls { namespace codecs { namespace vcodec_mjpg {
/**
  \brief  
  */
::libs::helpers::utils::cuuid
convert_jpeg2guid_px_format (const int _jpeg_px)
{
  ::libs::helpers::utils::cuuid _ret = ::libs::helpers::uids::minor::rgb24;

  switch (_jpeg_px)
    {
    case TJCS_RGB:
      _ret = ::libs::helpers::uids::minor::rgb24;
      break;
    case TJCS_YCbCr:
      _ret = ::libs::helpers::uids::minor::ycb;
      break;
    case TJCS_GRAY:
      _ret = ::libs::helpers::uids::minor::y8;
      break;
    case TJCS_CMYK:
    case TJCS_YCCK:
      XULOG_WARNING ("unsupported color space jpeg, " << _jpeg_px);
      break;
    default:
      XULOG_WARNING ("unkown color space jpeg, " << _jpeg_px);
      break;
    }
  return _ret;
}


bool
MjpegImpl::decomp_iframe (
  const HeaderIFrame* _head,
  const ProxyBuff&    _src,
  const int           _src_size)
{
  const auto&          _base_head    = _head->base_part_;
  const auto&          _info_head    = _base_head.sinfo_;
  const unsigned char* _sdata        = _src.ubuff () + _head->base_part_.size_;
  const unsigned char* _cdata        = _sdata + _head->coff_;
  unsigned int         _src_size_res = _head->csize_;
  int                  _codec_error  = 0;

  try
    {
      //::dlls::codecs::codec_gen::dump (_head);      //  debug
      update_decoder ();

      {
        int _jpeg_width   = 0;
        int _jpeg_height  = 0;
        int _jpeg_subsamp = 0;
        int _jpeg_px      = 0;

        _codec_error = tjDecompressHeader3 (hjpeg_, _cdata, _src_size_res, &_jpeg_width, &_jpeg_height, &_jpeg_subsamp, &_jpeg_px);
        XULOG_TRACE ("tjDecompressHeader3 say width=" << _jpeg_width << ", height=" << _jpeg_height << ", subsamp=" << _jpeg_subsamp << ", jpeg_px=" << _jpeg_px);
        temp_buff_->set_format (convert_jpeg2guid_px_format (_jpeg_px));
      }

      if (_codec_error)
        {
          throw std::runtime_error ("failed call tjDecompressHeader3");
        }

      _codec_error = tjDecompress2 (
        hjpeg_,
        _cdata,
        _src_size_res,
        temp_buff_->get_buff (),
        _info_head.width_,
        _info_head.stride_,
        _info_head.height_,
        cinfo_.plane_.monochrome_ ? TJPF_GRAY : (_head->cinfo_.monochrome_ ? TJPF_GRAY : TJPF_RGB),
        0);

      if (_codec_error)
        {
          throw std::runtime_error ("failed call tjDecompress2");
        }

      const auto _px_format  = temp_buff_->get_format ();      //  Уточняем формат, он может быть уже изменен.
      const auto _stride_res = _info_head.width_ * ::libs::helpers::uids::helpers::get_count_bytes_from_format (_px_format);
      const auto _size_res   = _info_head.height_ * _stride_res;

      temp_buff_->set_flag (utils::dbuffs::TypeFlagsBuff::empty, false);
      temp_buff_->set_mem_var (::utils::dbuffs::TypeMemVar::size_data, _size_res);
      temp_buff_->set_dim_var (utils::dbuffs::video::TypeDimVar::stride, _stride_res);
    }
  catch (std::exception& _e)
    {
      XULOG_FATAL ("exception: " << _e.what () << ", " << tjGetErrorStr () << ", " << _codec_error);
      return false;
    }
  return true;
}

}}}      // namespace dlls::codecs::vcodec_mjpg
