//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mjpeg-impl-coder-iframe.cpp
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

namespace dlls { namespace codecs { namespace vcodec_mjpg {

bool
MjpegImpl::comp_iframe (
  bool       _colored,
  ProxyBuff& _dst,
  int&       _out_size)
{
  XULOG_TRACE ("MjpegImpl::comp_iframe: beg");
  _dst.check ();

  unsigned char*       _dbuff       = _dst.ubuff ();
  HeaderIFrame*        _head        = UUU_CODECS_CAST<HeaderIFrame*> (_dbuff);
  int                  _from_header = 0;
  const ProxyBuff      _lsrc (temp_buff_.get ());
  const unsigned char* _cur_buff   = temp_buff_->get_cbuff ();
  const int            _in_format  = _colored ? TJPF_BGR : TJPF_GRAY;
  const int            _out_format = _colored ? TJSAMP_444 : TJSAMP_GRAY;
  unsigned long        _jpeg_size  = 0;
  unsigned long        _max_size   = tjBufSize (_lsrc.width_, _lsrc.height_, _out_format);

  _out_size = sizeof (HeaderIFrame);
  _head->reset ();

  update_coder( _max_size );

  const int _res_jpeg = tjCompress2 (
    hjpeg_,
    UUU_MEM_CAST<const unsigned char*> (_cur_buff),
    _lsrc.width_,
    _lsrc.stride_,
    _lsrc.height_,
    _in_format,
    &jpeg_buff_,
    &_jpeg_size,
    _out_format,
    cinfo_.plane_.quality_,
    TJFLAG_NOREALLOC | TJFLAG_FASTDCT | TJFLAG_BOTTOMUP);

  if (-1 == _res_jpeg)
    {
      char* _jerr = tjGetErrorStr ();
      XULOG_ERROR ("failed, jpeg coder, " << std::string (_jerr ? _jerr : "unknown null error"));
      return false;
    }

  XULOG_TRACE ("MjpegImpl::comp_iframe: size compress " << to_str (_jpeg_size));
  ::libs::helpers::mem::acopy (jpeg_buff_, _dbuff + _out_size, _jpeg_size);

  _head->csize_ = _jpeg_size;
  _head->coff_  = _from_header;
  _from_header += _jpeg_size;
  _out_size += _jpeg_size;

  UASSERT (_out_size > 0);

  auto& _base_header = _head->base_part_;
  auto& _base_size   = _base_header.sinfo_;

  _base_header.size_compress_ = _out_size;
  _base_size.width_           = _lsrc.width_;
  _base_size.height_          = _lsrc.height_;
  _base_size.stride_          = _lsrc.width_ * (_colored ? 3 : 1);

  _head->cinfo_             = cinfo_.plane_;
  _head->cinfo_.monochrome_ = _colored ? false : true;      //переопределяем по факту, т.к. у пользователя может быть установлено сжатие с цветом при его фактическом отсутствии и наоборот.

  std::copy (::libs::helpers::uids::codecs::mjpeg.get_vals ().begin (), ::libs::helpers::uids::codecs::mjpeg.get_vals ().end (), _head->base_part_.guid_);

  UASSERT (_head->check ());
  statistic_.update ("iframe", _jpeg_size);
  XULOG_TRACE ("MjpegImpl::comp_iframe: end");
  return true;
}

}}}      // namespace dlls::codecs::vcodec_mjpg
