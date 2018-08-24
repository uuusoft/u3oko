#pragma once
/**
\file       convert-format-functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.07.2018
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/

namespace libs { namespace helpers { namespace dshow {

#if defined(UUU_OS_WIN32_DESKTOP)

void
convert2format (
  const utils::cuuid& _format,
  const int           _width,
  const int           _height,
  const int           _bits_count,
  VIDEOINFOHEADER*    _res);

void
convert2format (
  const utils::cuuid& _format,
  const int           _width,
  const int           _height,
  const int           _bits_count,
  VIDEOINFOHEADER2*   _res);

unsigned long guid2dword_compression (const utils::cuuid& _guid);

utils::cuuid dword_compression2guid (const unsigned long _val, const BITMAPINFOHEADER* _bmp);
#endif

}}}      // namespace libs::helpers::dshow
