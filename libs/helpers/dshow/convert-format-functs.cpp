//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       convert-format-functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2018
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "../includes_int.hpp"
#include "convert-format-functs.hpp"

namespace libs { namespace helpers { namespace dshow {

#if defined(UUU_OS_WIN32_DESKTOP)

void
convert2format (
  const utils::cuuid& _format,
  const int           _width,
  const int           _height,
  const int           _bits_count,
  VIDEOINFOHEADER*    _res)
{
  XULOG_TRACE ("convert2format: beg");
  UASSERT (_res);
  UASSERT (_width > 0);
  UASSERT (_height > 0);
  UASSERT (!_format.empty ());

  _res->bmiHeader.biBitCount     = static_cast<signed short> (_bits_count);
  _res->bmiHeader.biClrImportant = 0;
  _res->bmiHeader.biClrUsed      = 0;
  _res->bmiHeader.biCompression  = guid2dword_compression (_format);
  _res->bmiHeader.biPlanes       = 1;
  _res->bmiHeader.biSize         = sizeof (BITMAPINFOHEADER);
  _res->bmiHeader.biSizeImage    = _width * _height * _bits_count / 8;

  _res->bmiHeader.biWidth         = _width;
  _res->bmiHeader.biHeight        = _height;
  _res->bmiHeader.biXPelsPerMeter = 0;
  _res->bmiHeader.biYPelsPerMeter = 0;

  _res->AvgTimePerFrame = 30 * 1000 * 10;
  _res->dwBitErrorRate  = 0;

  _res->dwBitRate = _width * _height * _bits_count * 30;

  SetRect (&_res->rcSource, 0, 0, _width, _height);
  SetRect (&_res->rcTarget, 0, 0, _width, _height);
  XULOG_TRACE ("convert2format: end");
  return;
}


void
convert2format (
  const utils::cuuid& _format,
  const int           _width,
  const int           _height,
  const int           _bits_count,
  VIDEOINFOHEADER2*   _res)
{
  XULOG_TRACE ("convert2format: beg");
  UASSERT (_res);
  UASSERT (_width > 0);
  UASSERT (_height > 0);
  UASSERT (!_format.empty ());

  _res->dwCopyProtectFlags = 0;
  _res->dwInterlaceFlags   = 0;
  _res->dwPictAspectRatioX = _width;
  _res->dwPictAspectRatioY = _height;
  _res->dwReserved1        = 0;
  _res->dwReserved2        = 0;

  _res->bmiHeader.biBitCount     = static_cast<signed short> (_bits_count);
  _res->bmiHeader.biClrImportant = 0;
  _res->bmiHeader.biClrUsed      = 0;
  _res->bmiHeader.biCompression  = guid2dword_compression (_format);
  _res->bmiHeader.biPlanes       = 1;
  _res->bmiHeader.biSize         = sizeof (BITMAPINFOHEADER);
  _res->bmiHeader.biSizeImage    = _width * _height * _bits_count / 8;

  _res->bmiHeader.biWidth         = _width;
  _res->bmiHeader.biHeight        = _height;
  _res->bmiHeader.biXPelsPerMeter = 0;
  _res->bmiHeader.biYPelsPerMeter = 0;

  _res->AvgTimePerFrame = 30 * 1000 * 10;
  _res->dwBitErrorRate  = 0;

  _res->dwBitRate = _width * _height * _bits_count * 30;

  SetRect (&_res->rcSource, 0, 0, _width, _height);
  SetRect (&_res->rcTarget, 0, 0, _width, _height);
  XULOG_TRACE ("convert2format: end");
  return;
}


unsigned long
guid2dword_compression (const utils::cuuid& _guid)
{
  static const std::map<utils::cuuid, unsigned long> guid2dword = {
    { uids::minor::mjpg, consts::compression::mjpg },
    { uids::minor::rgb24, consts::compression::rgb },
    { uids::minor::rgb32, consts::compression::rgb },
    { uids::minor::rgb555, consts::compression::rgb },
    { uids::minor::rgb565, consts::compression::rgb }
  };

  auto _find = guid2dword.find (_guid);
  if (guid2dword.end () == _find)
    {
      XULOG_WARNING ("guid2dword_compression: guid not found, default value for " << uids::helpers::get_readable_name (_guid));
      return consts::compression::bitfields;
    }

  return _find->second;
}


utils::cuuid
dword_compression2guid (const unsigned long _val, const BITMAPINFOHEADER* _bmp)
{
  UASSERT (_bmp);

  static const std::map<unsigned long, std::function<utils::cuuid (const BITMAPINFOHEADER*)>> dword2guid = {
    { consts::compression::mjpg, [](const BITMAPINFOHEADER* _bmp) { return uids::minor::mjpg; } },
    { consts::compression::MJPG, [](const BITMAPINFOHEADER* _bmp) { return uids::minor::mjpg; } },
    { consts::compression::jpeg, [](const BITMAPINFOHEADER* _bmp) { return uids::minor::mjpg; } },
    { consts::compression::i420, [](const BITMAPINFOHEADER* _bmp) { return uids::minor::i420; } },
    { consts::compression::rle4, [](const BITMAPINFOHEADER* _bmp) { return uids::minor::rgb8; } },
    { consts::compression::rle8, [](const BITMAPINFOHEADER* _bmp) { return uids::minor::rgb8; } },
    { consts::compression::bitfields, [](const BITMAPINFOHEADER* _bmp) { return uids::minor::rgb32; } },
    { consts::compression::rgb,
      [_val](const BITMAPINFOHEADER* _bmp) {
        switch (_bmp->biBitCount)
          {
          case 32:
            return uids::minor::rgb32;
          case 24:
            return uids::minor::rgb24;
          case 16:
            return uids::minor::rgb565;
          default:
            XULOG_WARNING ("unknown compress id, 0x" << std::hex << _val << ", " << to_str_dword (_val));
            break;
          }
        return uids::minor::rgb24;
      } }


  };

  auto _find = dword2guid.find (_val);
  if (dword2guid.end () == _find)
    {
      XULOG_WARNING ("dword_compression2guid: compress id not found, default value for 0x" << std::hex << _val << ", " << to_str_dword (_val));
      return uids::minor::unknow;
    }

  return _find->second (_bmp);
}
#endif

}}}      // namespace libs::helpers::dshow
