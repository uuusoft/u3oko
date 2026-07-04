/**
\file       update_register_lib_func.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"
#include "update_register_lib_func.hpp"
#include "libs-helpers-files-includes.hpp"
#include "path_funcs.hpp"

#ifdef U3_OS_WIN32_DESKTOP
#  include "Shlobj.h"

namespace libs::utility::files
{
typedef HRESULT (STDAPICALLTYPE* reg_func_type) ();
typedef HRESULT (STDAPICALLTYPE* unreg_func_type) ();

bool
update_register_lib (const std::string& path, bool need_reg)
{
  HMODULE module = LoadLibraryA (path.c_str ());
  if (!module)
  {
    U3_XLOG_ERROR ("load lib" + TOLOG (path));
    return false;
  }

  if (need_reg)
  {
    reg_func_type reg_funct = ::libs::utility::casts::reinterpret_cast_helper< reg_func_type > (GetProcAddress (module, "DllRegisterServer"));
    if (!reg_funct || FAILED ((*reg_funct) ()))
    {
      U3_XLOG_ERROR ("register lib" + TOLOG (path));
      return false;
    }
  }
  else
  {
    unreg_func_type unreg_funct = ::libs::utility::casts::reinterpret_cast_helper< unreg_func_type > (GetProcAddress (module, "DllUnregisterServer"));
    U3_ASSERT (unreg_funct);
    if (!unreg_funct || (FAILED ((*unreg_funct) ())))
    {
      U3_XLOG_ERROR ("unregister lib" + TOLOG (path));
      return false;
    }
  }
  return true;
}
}   // namespace libs::utility::files

#endif
