#pragma once
/**
\file       process_gen_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       07.11.2016
\project    u3_helpers_lib
\brief      Функции для работы с процессами в win32
*/

namespace libs::helpers::platforms::win32
{
inline void
add_process_privilage ()
{
  HANDLE htk = 0;

  U3_CHECK (OpenProcessToken (GetCurrentProcess (), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &htk), "open process token");
  U3_ASSERT (htk);

  bool         res        = true;
  const TCHAR* text_ids[] = {
    SE_DEBUG_NAME,
    SE_LOCK_MEMORY_NAME,
    SE_INC_BASE_PRIORITY_NAME,
    SE_INCREASE_QUOTA_NAME,
    SE_LOAD_DRIVER_NAME
  };

  for (std::size_t indx1 = 0; indx1 < std::size (text_ids); ++indx1)
  {
    TOKEN_PRIVILEGES tkp;

    if (!LookupPrivilegeValue (0, text_ids[indx1], &tkp.Privileges[0].Luid))
    {
      U3_ASSERT_SIGNAL ("failed");
      res = false;
      continue;
    }

    tkp.PrivilegeCount           = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges (htk, false, &tkp, 0, ::libs::helpers::casts::reinterpret_cast_helper< PTOKEN_PRIVILEGES > (0), 0))
    {
      U3_ASSERT_SIGNAL ("failed");
      res = false;
      continue;
    }
  }

  CloseHandle (htk);
  htk = 0;
  U3_CHECK_WIN32_STATE (res, "CloseHandle");
}
}   // namespace libs::helpers::platforms::win32
