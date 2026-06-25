#pragma once
/**
\file       window_gen_funcs.hpp
\brief      Функции для работы с окнами
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_helpers_lib
*/

namespace libs::helpers::platforms::win32::send_message
{
/// 23.11.2016 т.к. данная функция должна применять с предельной осторожностью, т.к. может разрушить состояние вызывающего объекта
/// \brief  поэтому спрятана в собственное пространство имен
/// \brief  U3-REFACT
void send (
  HWND         window,
  std::int32_t msg,
  WPARAM       wparam,
  LPARAM       lparam,
  std::int32_t timeout           = 120 * 1000,
  bool         enable_block_call = false);
}   // namespace libs::helpers::platforms::win32::send_message


namespace libs::helpers::platforms::win32
{
bool is_valid (HWND hwnd);
void register_window_class (const WNDCLASSEX* lpwcx);
void destroy_window (HWND hwnd);
void reset_link (HWND hwnd);
void add_link (HWND hwnd, const CREATESTRUCT* info);

HWND create_window (
  unsigned long dwExStyle,
  LPCTSTR       lpClassName,
  LPCTSTR       lpWindowName,
  unsigned long dwStyle,
  std::int32_t  x,
  std::int32_t  y,
  std::int32_t  nWidth,
  std::int32_t  nHeight,
  HWND          hWndParent,
  HMENU         hMenu,
  HINSTANCE     hInstance,
  void*         lpParam,
  const TCHAR*  add_info);
}   // namespace libs::helpers::platforms::win32
