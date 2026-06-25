#pragma once
/**
\file     window2rgb.hpp
\brief    Функция сохраняет образ указанного окна в указанном BMP файле
\author   Erashov Anton erashov2026@proton.me
\date     26.05.2016
*/
#ifdef U3_OS_WIN32_DESKTOP

namespace dlls::sources::desk_vgen::impls::win32::helpers
{
void hdc2rgb (
  const HDC&                            whdc,
  ::libs::helpers::mem::IBlockMem::ptr& rgb_buf,
  const std::int32_t                    offset_x,
  const std::int32_t                    offset_y,
  std::uint32_t&                        active_dest_buf,
  std::uint32_t&                        width_dest,
  std::uint32_t&                        height_dest,
  std::uint32_t&                        stride_dest,
  const std::uint32_t                   dest_bits);


void window2rgb (
  HWND                                  hwnd,
  ::libs::helpers::mem::IBlockMem::ptr& rgb_buf,
  const std::int32_t                    offset_x,
  const std::int32_t                    offset_y,
  std::uint32_t&                        active_dest_buf,
  std::uint32_t&                        width_dest,
  std::uint32_t&                        height_dest,
  std::uint32_t&                        stride_dest,
  const std::uint32_t                   dest_bits);
}   // namespace dlls::sources::desk_vgen::impls::win32::helpers

#endif
