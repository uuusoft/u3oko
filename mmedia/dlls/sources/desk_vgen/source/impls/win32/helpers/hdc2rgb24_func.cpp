/**
\file     hdc2rgb24_funct.cpp
\brief    function for convert anybody hdc to rgb24, if needed buf relloc from ::base_funcs::mem::arealloc
\author   Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date     26.07.2016
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../desk-vgen-includes_int.hpp"
#include "hdc2rgb24_func.hpp"

#ifdef U3_OS_WIN32_DESKTOP

namespace dlls::sources::desk_vgen::impls::win32::helpers
{
void
hdc2buf_alu (Hdc2BmpCallInfo& info)
{
  U3_ASSERT (info.check ());
  *info.active_dest_buf_ = 0;

  bool          ret          = 0;
  std::uint32_t min_mem_size = 0;
  std::uint8_t* tbuf         = nullptr;
  BITMAP        bitmap_info;

  // получаем информацию от источника
  {
    auto loc_bitmap = ::libs::helpers::casts::static_cast_helper< HBITMAP > (GetCurrentObject (info.source_hdc_, OBJ_BITMAP));
    U3_CHECK_WIN32_STATE (loc_bitmap, "GetCurrentObject");
    memset (&bitmap_info, 0, sizeof (bitmap_info));
    U3_CHECK_WIN32_CALL (GetObject (loc_bitmap, sizeof (bitmap_info), &bitmap_info), "GetObject");
  }

  // проверка полученных параметров
  const std::int32_t loc_width  = bitmap_info.bmWidth;
  const std::int32_t loc_height = bitmap_info.bmHeight;
  U3_CHECK_WIN32_STATE (loc_width > 0 && loc_height > 0, "source info" + VTOLOG (loc_width) + VTOLOG (loc_height));

  const std::int32_t loc_support_hdc = GetDeviceCaps (info.source_hdc_, RASTERCAPS);
  U3_CHECK_WIN32_STATE (loc_support_hdc & (RC_BITBLT | RC_DI_BITMAP), "raster caps RC_BITBLT | RC_DI_BITMAP not support");

  // create temporarely hdc for system convert to RGB24
  ::libs::helpers::platforms::win32::HandlerGdiObj< HBITMAP > temp_hbitmap;   // должен быть до temp_hdc
  ::libs::helpers::platforms::win32::HandlerCompatibleDC      temp_hdc (info.source_hdc_);
  U3_CHECK_WIN32_STATE (temp_hdc, "create dc" + ::libs::helpers::platforms::win32::last_error2string (GetLastError ()));

  min_mem_size = U3_CAST_UINT32 ((loc_width * (info.dest_count_bits_ / 8)) * loc_height);

  info.dest_buf_->resize (min_mem_size);

  {
    BITMAPINFO temp_bitmapinfo;

    memset (&temp_bitmapinfo, 0, sizeof (temp_bitmapinfo));
    temp_bitmapinfo.bmiHeader.biSize  = sizeof (temp_bitmapinfo.bmiHeader);
    temp_bitmapinfo.bmiHeader.biWidth = loc_width;

    if (!info.vinvert_)
    {
      temp_bitmapinfo.bmiHeader.biHeight = loc_height;
    }
    else
    {
      temp_bitmapinfo.bmiHeader.biHeight = -loc_height;
    }

    temp_bitmapinfo.bmiHeader.biPlanes      = 1;
    temp_bitmapinfo.bmiHeader.biBitCount    = U3_CAST_UINT16 (info.dest_count_bits_);
    temp_bitmapinfo.bmiHeader.biCompression = BI_RGB;
    temp_bitmapinfo.bmiHeader.biSizeImage   = 0;

    temp_hbitmap.change_gdi_object (CreateDIBSection (
      info.source_hdc_,
      &temp_bitmapinfo,
      DIB_RGB_COLORS,
      ::libs::helpers::casts::reinterpret_cast_helper< void** > (&tbuf),
      0,
      0));

    U3_CHECK_WIN32_STATE (temp_hbitmap, "create dib section");
  }

  temp_hdc.select_object (*temp_hbitmap);

  ret = BitBlt (*temp_hdc, 0, 0, loc_width, loc_height, info.source_hdc_, 0, 0, SRCCOPY) ? true : false;
  U3_CHECK_WIN32_STATE (ret, "BitBlt");

  if (info.width_dest_ && info.height_dest_)
  {
    *info.width_dest_  = loc_width;
    *info.height_dest_ = loc_height;
  }

  ::libs::helpers::mem::u3copy (tbuf, info.dest_buf_->get (), min_mem_size);
  info.dest_buf_->set_data_size (min_mem_size);

  *info.active_dest_buf_ = min_mem_size;
  *info.stride_dest_     = loc_width * (info.dest_count_bits_ / 8);
}
}   // namespace dlls::sources::desk_vgen::impls::win32::helpers

#endif
