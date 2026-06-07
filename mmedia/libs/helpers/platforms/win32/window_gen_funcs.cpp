/**
\file       window_gen_funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"

#ifdef U3_OS_WIN32_DESKTOP

#  include "window_gen_funcs.hpp"

namespace libs::helpers::platforms::win32::send_message
{
void
send (
  HWND         wnd,
  std::int32_t msg,
  WPARAM       wparam,
  LPARAM       lparam,
  std::int32_t timeout,
  bool         enable_block_call)
{
  DWORD_PTR res = S_OK;
  U3_CHECK (is_valid (wnd), "failed");
  //  23.11.2016 пробую так решить проблему разружения состояния объекта при ожиданни в синронизирующих функциях данного типа внутри обработки
  //  сообщения от внешнего агента, в ситуации когда пришло еще одно внешнее сообщение
  U3_CHECK_WIN32_CALL (0 != SendMessageTimeout (wnd, msg, wparam, lparam, enable_block_call ? SMTO_BLOCK : SMTO_NORMAL, timeout, &res), "SendMessageTimeout");
}
}   // namespace libs::helpers::platforms::win32::send_message


namespace libs::helpers::platforms::win32
{
bool
is_valid (HWND hwnd)
{
  if (!hwnd)
  {
    return false;
  }

  if (!::IsWindow (hwnd))
  {
    return false;
  }
  return true;
}


void
register_window_class (const WNDCLASSEX* lpwcx)
{
  WNDCLASSEX    wndclass;
  unsigned long last_error = 0;

  wndclass        = *lpwcx;
  wndclass.cbSize = sizeof (wndclass);

  if (!GetClassInfoEx (wndclass.hInstance, wndclass.lpszClassName, &wndclass))
  {
    wndclass        = *lpwcx;
    wndclass.cbSize = sizeof (wndclass);

    SetLastError (0);

    if (RegisterClassEx (&wndclass) == 0)
    {
      if (((last_error = GetLastError ()) != 0))
      {
        U3_ASSERT_SIGNAL ("failed");
      }
    }
  }
}


void
destroy_window (HWND wnd)
{
  std::uint32_t dw1 = 0;
  U3_CHECK (is_valid (wnd), "failed");
  // если данное окно нашего потока просто удаляем его иначе посылаем сообщение
  // окну с требованием удалить себя
  if (GetCurrentThreadId () == GetWindowThreadProcessId (wnd, 0))
  {
    if (DestroyWindow (wnd) == false)
    {
      U3_ASSERT_SIGNAL_NT ("failed");
      dw1 = GetLastError ();
    }
  }
  else
  {
    //  25.06.2016 - corrected to special function
    ::libs::helpers::platforms::win32::send_message::send (
      wnd,
      WM_CLOSE,
      0xFFFFFFFF,
      0xFFFFFFFF,
      60 * 1000,
      false);
  }
}


HWND
create_window (
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
  const TCHAR*  add_info)
{
  HWND ret = 0;

  if ((0 == lpClassName) || (0 == hInstance))
  {
    return 0;
  }

  U3_CHECK_WIN32_CALL (0 != (ret = CreateWindowEx (dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)), "CreateWindowEx");
  return ret;
}


void
reset_link (HWND hwnd)
{
  U3_CHECK (is_valid (hwnd), "failed");

  SetLastError (0);

  if (SetWindowLong (hwnd, GWLP_USERDATA, 0) == 0)
  {
    U3_CHECK (0 == GetLastError (), "failed SetWindowLong");
  }
}


void
add_link (HWND hwnd, const CREATESTRUCT* info)
{
  U3_CHECK (info, "failed");
  U3_CHECK (is_valid (hwnd), "failed");
  U3_CHECK (info->lpCreateParams, "failed")

  SetLastError (0);
  if (SetWindowLongPtr (hwnd, GWLP_USERDATA, ::libs::helpers::casts::reinterpret_cast_helper< LONG_PTR > (info->lpCreateParams)) == 0)
  {
    U3_CHECK (0 == GetLastError (), "failed SetWindowLongPtr");
  }
}
}   // namespace libs::helpers::platforms::win32

#endif
