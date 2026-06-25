/**
\file       convert-format-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2018
\project    u3_dshow_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "convert-format-funcs.hpp"

#ifdef U3_OS_WIN32_DESKTOP

namespace libs::helpers::dshow
{
void
convert2format (
  const ::libs::helpers::uids::minor::id_val& format,
  const std::int32_t                          width,
  const std::int32_t                          height,
  const std::int32_t                          bits_count,
  VIDEOINFOHEADER*                            vihead)
{
  U3_ASSERT (vihead);
  U3_ASSERT (width > 0);
  U3_ASSERT (height > 0);

  vihead->bmiHeader.biBitCount     = U3_CAST_INT16 (bits_count);
  vihead->bmiHeader.biClrImportant = 0;
  vihead->bmiHeader.biClrUsed      = 0;
  // vihead->bmiHeader.biCompression   = guid2dword_compression (format);
  vihead->bmiHeader.biCompression   = 0;   // libs::helpers::uids::helpers::idval2fourcc (format);
  vihead->bmiHeader.biPlanes        = 1;
  vihead->bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
  vihead->bmiHeader.biSizeImage     = width * height * bits_count / 8;
  vihead->bmiHeader.biWidth         = width;
  vihead->bmiHeader.biHeight        = height;
  vihead->bmiHeader.biXPelsPerMeter = 0;
  vihead->bmiHeader.biYPelsPerMeter = 0;
  vihead->AvgTimePerFrame           = 30 * 1000 * 10;
  vihead->dwBitErrorRate            = 0;
  vihead->dwBitRate                 = width * height * bits_count * 30;

  SetRect (&vihead->rcSource, 0, 0, width, height);
  SetRect (&vihead->rcTarget, 0, 0, width, height);
}


void
convert2format (
  const ::libs::helpers::uids::minor::id_val& format,
  const std::int32_t                          width,
  const std::int32_t                          height,
  const std::int32_t                          bits_count,
  VIDEOINFOHEADER2*                           vihead)
{
  U3_ASSERT (vihead);
  U3_ASSERT (width > 0);
  U3_ASSERT (height > 0);

  vihead->dwCopyProtectFlags = 0;
  vihead->dwInterlaceFlags   = 0;
  vihead->dwPictAspectRatioX = width;
  vihead->dwPictAspectRatioY = height;
  vihead->dwReserved1        = 0;
  vihead->dwReserved2        = 0;

  vihead->bmiHeader.biBitCount      = U3_CAST_INT16 (bits_count);
  vihead->bmiHeader.biClrImportant  = 0;
  vihead->bmiHeader.biClrUsed       = 0;
  vihead->bmiHeader.biCompression   = 0;   // libs::helpers::uids::helpers::idval2fourcc (format);
  vihead->bmiHeader.biPlanes        = 1;
  vihead->bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
  vihead->bmiHeader.biSizeImage     = width * height * bits_count / 8;
  vihead->bmiHeader.biWidth         = width;
  vihead->bmiHeader.biHeight        = height;
  vihead->bmiHeader.biXPelsPerMeter = 0;
  vihead->bmiHeader.biYPelsPerMeter = 0;
  vihead->AvgTimePerFrame           = 30 * 1000 * 10;
  vihead->dwBitErrorRate            = 0;
  vihead->dwBitRate                 = width * height * bits_count * 30;

  SetRect (&vihead->rcSource, 0, 0, width, height);
  SetRect (&vihead->rcTarget, 0, 0, width, height);
}

#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
unsigned long
guid2dword_compression (const utils::cuuid& guid)
{
  static const std::unordered_map< utils::cuuid, const unsigned long > guid2dword = {
    { uids::minor::mjpg, consts::compression::mjpg },
    { uids::minor::id_val::rgb24, consts::compression::rgb },
    { uids::minor::id_val::rgb32, consts::compression::rgb },
    { uids::minor::rgb555, consts::compression::rgb },
    { uids::minor::rgb565, consts::compression::rgb },
    { uids::minor::id_val::y8, consts::compression::rgb },
    { uids::minor::id_val::i420, consts::compression::i420 },
    { uids::minor::id_val::yuy2, consts::compression::YUY2 },
    { uids::minor::iyuv, consts::compression::VYUY }
  };

  auto find = guid2dword.find (guid);
  if (guid2dword.end () == find)
  {
    U3_XLOG_WARN ("guid2dword_compression: guid not found, default value for " + uids::helpers::get_readable_name (guid) + " guid=" + ::libs::helpers::utils::to_string (guid));
    return consts::compression::bitfields;
  }
  return find->second;
}
#  endif
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
utils::cuuid
dword_compression2guid (const unsigned long val, const BITMAPINFOHEADER* bmp)
{
  U3_ASSERT (bmp);

  static const std::unordered_map< unsigned long, std::function< utils::cuuid (const BITMAPINFOHEADER*) > > dword2guid = {
    { consts::compression::mjpg, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::mjpg; } },
    { consts::compression::MJPG, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::mjpg; } },
    { consts::compression::jpeg, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::mjpg; } },
    { consts::compression::i420, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::id_val::i420; } },
    { consts::compression::rle4, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::rgb8; } },
    { consts::compression::rle8, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::rgb8; } },
    { consts::compression::VYUY, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::id_val::yuyv; } },
    { consts::compression::YUY2, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::id_val::yuy2; } },
    { consts::compression::bitfields, [] (const BITMAPINFOHEADER* bmp) { return uids::minor::id_val::rgb32; } },
    { consts::compression::rgb,
      [val] (const BITMAPINFOHEADER* bmp) {
        switch (bmp->biBitCount)
        {
        case 32:
          return uids::minor::id_val::rgb32;
        case 24:
          return uids::minor::id_val::rgb24;
        case 16:
          return uids::minor::rgb565;
        default:
          U3_XLOG_WARN ("unknown compress id" + VTOLOG (val) + to_str_dword (val));
          break;
        }
        return uids::minor::id_val::rgb24;
      } }
  };

  auto find = dword2guid.find (val);
  if (dword2guid.end () == find)
  {
    U3_XLOG_WARN ("dword_compression2guid: compress id not found, default value for" + VTOLOG (val) + to_str_dword (val));
    return uids::minor::unknown;
  }

  return find->second (bmp);
}
#  endif
}   // namespace libs::helpers::dshow

#endif
