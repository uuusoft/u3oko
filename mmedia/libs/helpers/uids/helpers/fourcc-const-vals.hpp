#pragma once
/**
\file       fourcc-const-vals.hpp
\brief      FOURCC constans
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.02.2026
\project    u3_helpers_lib
*/

namespace libs::helpers::uids::helpers::consts::fourcc
{
constexpr std::uint32_t mjpg      = 0x4D4A5047;
constexpr std::uint32_t MJPG      = 0x47504A4D;
constexpr std::uint32_t I420      = 0x49343230;
constexpr std::uint32_t YUY2      = 0x32595559;
constexpr std::uint32_t YUYV      = 0x56595559;
constexpr std::uint32_t YVYU      = 0x55595659;
constexpr std::uint32_t RGBA      = 0x41424752;
constexpr std::uint32_t RAW       = 0x00000000;
constexpr std::uint32_t GREY      = 0x59455247;
constexpr std::uint32_t IRAW      = 0x57615349;
constexpr std::uint32_t IUYV      = 0x56595549;
constexpr std::uint32_t IY41      = 0x31345949;
constexpr std::uint32_t IYU1      = 0x31555949;
constexpr std::uint32_t IYU2      = 0x32555949;
constexpr std::uint32_t UYNV      = 0x564E5955;
constexpr std::uint32_t UYVP      = 0x50565955;
constexpr std::uint32_t V210      = 0x30313256;
constexpr std::uint32_t V422      = 0x32323456;
constexpr std::uint32_t V655      = 0x35353656;
constexpr std::uint32_t VYUY      = 0x59555956;
constexpr std::uint32_t Y422      = 0x32323459;
constexpr std::uint32_t YUNV      = 0x564E5559;
constexpr std::uint32_t Y41P      = 0x50313459;
constexpr std::uint32_t Y411      = 0x31313459;
constexpr std::uint32_t Y211      = 0x31313259;
constexpr std::uint32_t Y41T      = 0x54313459;
constexpr std::uint32_t Y42T      = 0x54323459;
constexpr std::uint32_t YUVP      = 0x50565559;
constexpr std::uint32_t Y800      = 0x30303859;
constexpr std::uint32_t Y8        = 0x20203859;
constexpr std::uint32_t bitfields = 0x3;    // BI_BITFIELDS
constexpr std::uint32_t png       = 0x05;   // BI_PNG;
constexpr std::uint32_t rle8      = 0x1;    // BI_RLE8
constexpr std::uint32_t rle4      = 0x2;    // BI_RLE4

#ifdef U3_FAKE_DISABLE
BI_RGB (0) : Uncompressed RGB.BI_RLE8 (1) : Run - length encoded 8 - bpp.BI_RLE4 (2) : Run - length encoded 4 - bpp.BI_BITFIELDS (3) : Uncompressed RGB with color masks.BI_JPEG (4) : JPEG image.BI_PNG (5) : PNG image.constexpr unsigned long rgb = BI_RGB;
constexpr unsigned long jpeg                                                                                                                                                                                                                         = BI_JPEG;
#endif
}   // namespace libs::helpers::uids::helpers::consts::fourcc
