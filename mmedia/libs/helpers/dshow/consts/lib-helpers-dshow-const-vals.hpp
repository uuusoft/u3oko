#pragma once
/**
\file       lib-helpers-dshow-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_dshow_vgen
*/

namespace libs::helpers::dshow::consts::compression
{
#ifdef U3_FAKE_DISABLE
constexpr unsigned long rgb       = BI_RGB;
constexpr unsigned long bitfields = BI_BITFIELDS;
constexpr unsigned long rle8      = BI_RLE8;
constexpr unsigned long rle4      = BI_RLE4;
constexpr unsigned long jpeg      = BI_JPEG;
constexpr unsigned long png       = BI_PNG;
constexpr unsigned long mjpg      = 0x4D4A5047;
constexpr unsigned long MJPG      = 0x47504A4D;
constexpr unsigned long i420      = 0x49343230;
constexpr unsigned long YUY2      = 0x32595559;
constexpr unsigned long VYUY      = 0x56595559;
#endif
}   // namespace libs::helpers::dshow::consts::compression
