#pragma once
/**
\file       lib-helpers-dshow-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_dshow_vgen
*/

namespace libs::utility::dshow::consts::compression
{
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
inline constexpr unsigned long rgb       = BI_RGB;
inline constexpr unsigned long bitfields = BI_BITFIELDS;
inline constexpr unsigned long rle8      = BI_RLE8;
inline constexpr unsigned long rle4      = BI_RLE4;
inline constexpr unsigned long jpeg      = BI_JPEG;
inline constexpr unsigned long png       = BI_PNG;
inline constexpr unsigned long mjpg      = 0x4D4A5047;
inline constexpr unsigned long MJPG      = 0x47504A4D;
inline constexpr unsigned long i420      = 0x49343230;
inline constexpr unsigned long YUY2      = 0x32595559;
inline constexpr unsigned long VYUY      = 0x56595559;
#endif
}   // namespace libs::utility::dshow::consts::compression
