#pragma once
/**
\file       window_gen_functs.hpp
\brief      Функции для работы с окнами
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs {
namespace helpers {
namespace windows {
namespace send_message {
#if defined(UUU_OS_WIN32_DESKTOP)
/**
  \brief  23.11.2016 т.к. данная функция должна применять с предельной осторожностью, т.к. может разрушить состояние вызывающего объекта
  \brief  поэтому спрятана в собственно простраство имен.
  */
bool send (
  HWND   window,
  int    msg,
  WPARAM wparam,
  LPARAM lparam,
  int    timeout           = 120 * 1000,
  bool   enable_block_call = false);
#endif
}
}}}      // namespace libs::helpers::windows::send_message


namespace libs { namespace helpers { namespace windows {
#if defined(UUU_OS_WIN32_DESKTOP)
/**
  \brief  empty brief
  */
bool is_valid (HWND _hwnd);
/**
  \brief  функция регитрирует указанный класс окна с обработкой всех возможных ошибок
  */
bool register_window_class (const WNDCLASSEX* lpwcx);
/**
  \brief  empty brief
  */
bool destroy_window (HWND _hwnd);
/**
  \brief  empty brief
  */
HWND create_window (
  unsigned long dwExStyle,
  LPCTSTR       lpClassName,
  LPCTSTR       lpWindowName,
  unsigned long dwStyle,
  int           x,
  int           y,
  int           nWidth,
  int           nHeight,
  HWND          hWndParent,
  HMENU         hMenu,
  HINSTANCE     hInstance,
  void*         lpParam,
  const TCHAR*  add_info);
/**
  \brief  empty brief
  */
bool reset_link (HWND _hwnd);
/**
  \brief  empty brief
  */
bool add_link (HWND _hwnd, const CREATESTRUCT* _info);
#endif
}}}      // namespace libs::helpers::windows
