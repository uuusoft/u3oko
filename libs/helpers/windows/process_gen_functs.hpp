#pragma once
/**
\file       process_gen_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       07.11.2016.
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Функции для работы с процессами в win32.
*/

namespace libs { namespace helpers { namespace windows {
#if defined(UUU_OS_WIN32_DESKTOP)
/**
  \brief
  */
inline void
add_process_privilage ()
{
  HANDLE _htk = 0;

  CHECK_CALL (OpenProcessToken (GetCurrentProcess (), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &_htk), "failed open process token");

  UASSERT (_htk);

  bool         _res        = true;
  const TCHAR* _text_ids[] = {
    SE_DEBUG_NAME,
    SE_LOCK_MEMORY_NAME,
    SE_INC_BASE_PRIORITY_NAME,
    SE_INCREASE_QUOTA_NAME,
    SE_LOAD_DRIVER_NAME
  };

  for (std::size_t indx1 = 0; indx1 < COUNT_OF (_text_ids); ++indx1)
    {
      TOKEN_PRIVILEGES _tkp;

      if (!LookupPrivilegeValue (0, _text_ids[indx1], &_tkp.Privileges[0].Luid))
        {
          UASSERT_SIGNAL ("failed");
          _res = false;
          continue;
        }

      _tkp.PrivilegeCount           = 1;
      _tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      if (!AdjustTokenPrivileges (_htk, false, &_tkp, 0, UUU_MEM_CAST<PTOKEN_PRIVILEGES> (0), 0))
        {
          UASSERT_SIGNAL ("failed");
          _res = false;
          continue;
        }
    }

  CloseHandle (_htk);
  _htk = 0;

  CHECK_STATE (_res, "failed");

  return;
}
#endif
}}}      // namespace libs::helpers::windows
