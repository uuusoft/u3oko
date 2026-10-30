/**
\file       window_gen_funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
#include "../../utility-lib-includes_int.hpp"

#ifdef U3_OS_WIN32_DESKTOP

#  include "window_gen_funcs.hpp"

namespace libs::utility::platforms::win32::send_message
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
  ::libs::utility::checks::throw_ifn (is_valid (wnd), "failed");
  //  23.11.2016 пробую так решить проблему разружения состояния объекта при ожиданни в синронизирующих функциях данного типа внутри обработки
  //  сообщения от внешнего агента, в ситуации когда пришло еще одно внешнее сообщение
  ::libs::utility::checks::throw_ifn_WIN32_CALL (0 != SendMessageTimeout (wnd, msg, wparam, lparam, enable_block_call ? SMTO_BLOCK : SMTO_NORMAL, timeout, &res), "SendMessageTimeout");
}
}   // namespace libs::utility::platforms::win32::send_message


namespace libs::utility::platforms::win32
{
bool
is_valid (HWND hwnd)
{
  return !hwnd || !::IsWindow (hwnd) ? false : true;
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
        ::libs::utility::checks::throw_exception ("failed");
      }
    }
  }
}


void
destroy_window (HWND wnd)
{
  std::uint32_t dw1 = 0;
  ::libs::utility::checks::throw_ifn (is_valid (wnd), "failed");
  // если данное окно нашего потока просто удаляем его иначе посылаем сообщение
  // окну с требованием удалить себя
  if (GetCurrentThreadId () == GetWindowThreadProcessId (wnd, 0))
  {
    if (DestroyWindow (wnd) == false)
    {
      ::libs::utility::checks::mark ("failed");
      dw1 = GetLastError ();
    }
  }
  else
  {
    //  25.06.2016 - corrected to special function
    ::libs::utility::platforms::win32::send_message::send (
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
  if ((0 == lpClassName) || (0 == hInstance))
  {
    return 0;
  }

  const HWND ret = CreateWindowEx (
    dwExStyle,
    lpClassName,
    lpWindowName,
    dwStyle,
    x,
    y,
    nWidth,
    nHeight,
    hWndParent,
    hMenu,
    hInstance,
    lpParam);

  ::libs::utility::checks::throw_ifn_WIN32_CALL (0 == ret, "CreateWindowEx");
  return ret;
}


void
reset_link (HWND hwnd)
{
  ::libs::utility::checks::throw_ifn (is_valid (hwnd), "failed");

  SetLastError (0);

  if (SetWindowLong (hwnd, GWLP_USERDATA, 0) == 0)
  {
    ::libs::utility::checks::throw_ifn (0 == GetLastError (), "failed SetWindowLong");
  }
}


void
add_link (HWND hwnd, const CREATESTRUCT* info)
{
  ::libs::utility::checks::throw_ifn (info, "failed");
  ::libs::utility::checks::throw_ifn (is_valid (hwnd), "failed");
  ::libs::utility::checks::throw_ifn (info->lpCreateParams, "failed")

    SetLastError (0);
  if (SetWindowLongPtr (hwnd, GWLP_USERDATA, ::libs::utility::casts::reinterpret_cast_helper< LONG_PTR > (info->lpCreateParams)) == 0)
  {
    ::libs::utility::checks::throw_ifn (0 == GetLastError (), "failed SetWindowLongPtr");
  }
}
}   // namespace libs::utility::platforms::win32

#endif
