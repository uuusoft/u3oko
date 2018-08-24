//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       window_gen_functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "window_gen_functs.hpp"

namespace libs { namespace helpers { namespace windows {
#if defined(UUU_OS_WIN32_DESKTOP)
bool
is_valid (HWND _hwnd)
{
  if (!_hwnd)
    {
      return false;
    }
#if 0
    if( UUU_MEM_CAST<HWND>( ::libs::helpers::consts::uinvalid) == _hwnd )
    {
      return false;
    }
#endif
  if (!::IsWindow (_hwnd))
    {
      return false;
    }

  return true;
}


bool
send_message::send (
  HWND   _wnd,
  int    msg,
  WPARAM wparam,
  LPARAM lparam,
  int    timeout,
  bool   enable_block_call)
{
  LRESULT   lr   = 0;
  DWORD_PTR _res = S_OK;

  if (!is_valid (_wnd))
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }
  /*
    23.11.2016 пробую так решить проблему разружения состояния объекта при ожиданни в синронизирующих функциях данного типа внутри обработки
    сообщения от внешнего агента, в ситуации когда пришло еще одно внешнее сообщение
    */
  lr = SendMessageTimeout (
    _wnd, msg, wparam, lparam, enable_block_call ? SMTO_BLOCK : SMTO_NORMAL, timeout, &_res);

  //dw1 = GetLastError ();
  if (0 == lr)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  return true;
}


bool
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
              UASSERT_SIGNAL ("failed");
              return false;
            }
        }
    }

  return true;
}


bool
destroy_window (HWND _wnd)
{
  unsigned long dw1 = 0;

  if (!is_valid (_wnd))
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }
  //если данное окно нашего потока просто удаляем его иначе посылаем сообщение
  //окну с требованием удалить себя
  if (GetCurrentThreadId () == GetWindowThreadProcessId (_wnd, 0))
    {
      if (DestroyWindow (_wnd) == false)
        {
          UASSERT_SIGNAL ("failed");
          dw1 = GetLastError ();
          return false;
        }
    }
  else
    {
      //  25.06.2016 - corrected to special function
      ::libs::helpers::windows::send_message::send (
        _wnd,
        WM_CLOSE,
        0xFFFFFFFF,
        0xFFFFFFFF,
        60 * 1000,
        false);
    }

  return true;
}


HWND
create_window (
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
  const TCHAR*  add_info)
{
  HWND ret = 0;

  if ((0 == lpClassName) || (0 == hInstance))
    {
      return 0;
    }

  ret = CreateWindowEx (
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

  //_lerror = ret;
  if (0 == ret)
    {
      UASSERT_SIGNAL ("failed");
      return 0;
    }

  return ret;
}


bool
reset_link (HWND hwnd)
{
  if (!is_valid (hwnd))
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  SetLastError (0);

  if (SetWindowLong (hwnd, GWLP_USERDATA, 0) == 0)
    {
      if (GetLastError () != 0)
        {
          UASSERT_SIGNAL ("failed");
          return false;
        }
    }

  return true;
}


bool
add_link (HWND _hwnd, const CREATESTRUCT* _info)
{
  if (0 == _info)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if (!is_valid (_hwnd))
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if (0 == _info->lpCreateParams)
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  SetLastError (0);

  if (SetWindowLongPtr (_hwnd, GWLP_USERDATA, UUU_MEM_CAST<LONG_PTR> (_info->lpCreateParams)) == 0)
    {
      if (GetLastError () != 0)
        {
          UASSERT_SIGNAL ("failed");
          return false;
        }
    }

  return true;
}
#endif
}}}      // namespace libs::helpers::windows
