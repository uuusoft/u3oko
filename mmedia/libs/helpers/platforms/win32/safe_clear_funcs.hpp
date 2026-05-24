#pragma once
/**
\file       safe_clear_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#include <Unknwn.h>

namespace libs::helpers::platforms::win32
{
/// макросы безопасного освобождения
template< typename TTRelease = IUnknown >
inline void
safe_release (unsigned long& n, TTRelease*& p)
{
  if (p)
  {
    n = p->Release ();
  }
  else
  {
    n = 0;
  }

  if (0 == n)
  {
    p = nullptr;
  }
}


template< typename TTGraphObj >
inline bool
safe_delete_gdi_object (TTGraphObj& x)
{
  if (!x)
  {
    return true;
  }

  if (!DeleteObject (x))
  {
    U3_XLOG_ERROR ("DeleteObject" + VTOLOG (GetLastError ()));
    return false;
  }

  return true;
}

/// макрос для безопасного удаление идентификаторов объектов
inline void
close (HANDLE& h)
{
  if (!h)
  {
    return;
  }

  U3_CHECK_WIN32_CALL_NT (CloseHandle (h), "close handle");
  h = 0;
}
}   // namespace libs::helpers::platforms::win32
