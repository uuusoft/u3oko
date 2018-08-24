#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/

namespace libs { namespace helpers { namespace dshow { namespace consts { namespace compression {

const unsigned long rgb       = BI_RGB;
const unsigned long bitfields = BI_BITFIELDS;
const unsigned long rle8      = BI_RLE8;
const unsigned long rle4      = BI_RLE4;
const unsigned long jpeg      = BI_JPEG;
const unsigned long png       = BI_PNG;
const unsigned long mjpg      = 0x4D4A5047;
const unsigned long MJPG      = 0x47504A4D;
const unsigned long i420      = 0x49343230;

}}}}}      // namespace libs::helpers::dshow::consts::compression
