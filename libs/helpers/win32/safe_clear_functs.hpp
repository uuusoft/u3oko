#pragma once
/**
\file       safe_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#if defined(UUU_OS_WIN32_DESKTOP)
#include <Unknwn.h>
#endif

namespace libs { namespace helpers { namespace win32 {
#if defined(UUU_OS_WIN32_DESKTOP)
/**
  \brief  макросы безопасного освобождения
  */
template <
  typename TTRelease = IUnknown>
inline void
safe_release (unsigned long& _n, TTRelease*& _p)
{
  if (_p)
    {
      _n = _p->Release ();
    }
  else
    {
      _n = 0;
    }

  if (0 == _n)
    {
      _p = nullptr;
    }
  return;
}


template <
  typename TTGraphObj>
inline bool
safe_delete_go (TTGraphObj& _x)
{
  if (!_x)
    {
      return true;
    }

  if (!DeleteObject (_x))
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  return true;
}
/**
  \brief  макрос для безопасного удаление идентификаторов объектов
  */
inline void
close (HANDLE& _h)
{
  if (!_h)
    {
      return;
    }

  CHECK_CALL_NO_THROW (CloseHandle (_h));
  _h = 0;
  return;
}
#endif
}}}      // namespace libs::helpers::win32
