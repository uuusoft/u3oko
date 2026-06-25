/**
\file       window2rgb.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_desk_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../desk-vgen-includes_int.hpp"
#include "hdc2rgb24_func.hpp"
#include "window2rgb.hpp"

#ifdef U3_OS_WIN32_DESKTOP

namespace dlls::sources::desk_vgen::impls::win32::helpers
{
void
hdc2rgb (
  const HDC&                            whdc,
  ::libs::helpers::mem::IBlockMem::ptr& rgb_buf,
  const std::int32_t                    offset_x,
  const std::int32_t                    offset_y,
  std::uint32_t&                        active_dest_buf,
  std::uint32_t&                        width_dest,
  std::uint32_t&                        height_dest,
  std::uint32_t&                        stride_dest,
  const std::uint32_t                   dest_bits)
{
  ::libs::helpers::platforms::win32::HandlerCompatibleDC      thdc (whdc);
  ::libs::helpers::platforms::win32::HandlerGdiObj< HBITMAP > hbmp (CreateCompatibleBitmap (whdc, width_dest, height_dest));
  U3_CHECK_WIN32_STATE (thdc && hbmp, "create compatible dc" + VTOLOG (width_dest) + VTOLOG (height_dest));

  thdc.select_object (*hbmp);

  U3_CHECK_WIN32_CALL (
    BitBlt (*thdc, 0, 0, width_dest, height_dest, whdc, offset_x, offset_y, SRCCOPY),
    "BitBlt" + VTOLOG (width_dest) + VTOLOG (height_dest));

  // конвертируем образ окна в формат RGB32
  ::dlls::sources::desk_vgen::impls::win32::helpers::Hdc2BmpCallInfo call_info (*thdc, rgb_buf, dest_bits, &active_dest_buf, &width_dest, &height_dest, &stride_dest, false);
  ::dlls::sources::desk_vgen::impls::win32::helpers::hdc2buf_alu (call_info);
  U3_CHECK_WIN32_STATE (rgb_buf->get (), "convert to rgb32");
}


void
window2rgb (
  HWND                                  hwnd,
  ::libs::helpers::mem::IBlockMem::ptr& rgb_buf,
  const std::int32_t                    offset_x,
  const std::int32_t                    offset_y,
  std::uint32_t&                        active_dest_buf,
  std::uint32_t&                        width_dest,
  std::uint32_t&                        height_dest,
  std::uint32_t&                        stride_dest,
  const std::uint32_t                   dest_bits)
{
  if ((::libs::helpers::consts::iinvalid == width_dest) || (::libs::helpers::consts::iinvalid == height_dest))
  {
    RECT trect1;
    GetClientRect (hwnd, &trect1);

    width_dest  = trect1.right - trect1.left;
    height_dest = trect1.bottom - trect1.top;
  }

  ::libs::helpers::platforms::win32::HandlerWindowDC whdc (hwnd);
  U3_CHECK_WIN32_STATE (whdc, "get dc from window" + VTOLOG (::libs::helpers::casts::reinterpret_cast_helper< std::uint64_t > (hwnd)));

  hdc2rgb (*whdc, rgb_buf, offset_x, offset_y, active_dest_buf, width_dest, height_dest, stride_dest, dest_bits);
}
}   // namespace dlls::sources::desk_vgen::impls::win32::helpers

#endif
