//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       update_register_lib_funct.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "update_register_lib_funct.hpp"
#include "../includes_int.hpp"
#include "includes.hpp"
#include "path_functs.hpp"
#if defined(UUU_OS_WIN32_DESKTOP)
#include "Shlobj.h"
#endif

namespace libs { namespace helpers { namespace files {

#if defined(UUU_OS_WIN32_DESKTOP)

typedef HRESULT (STDAPICALLTYPE* reg_funct_type) ();
typedef HRESULT (STDAPICALLTYPE* unreg_funct_type) ();

bool
update_register_lib (const std::string& path, bool need_reg)
{
  HMODULE _module = LoadLibraryA (path.c_str ());
  if (!_module)
    {
      XULOG_ERROR ("failed load lib, " << path);
      return false;
    }

  if (need_reg)
    {
      reg_funct_type reg_funct = UUU_MEM_FUNCT_CAST<reg_funct_type> (GetProcAddress (_module, "DllRegisterServer"));
      if (!reg_funct || FAILED ((*reg_funct) ()))
        {
          XULOG_ERROR ("failed register lib, " << path);
          return false;
        }
    }
  else
    {
      unreg_funct_type unreg_funct = UUU_MEM_FUNCT_CAST<unreg_funct_type> (GetProcAddress (_module, "DllUnregisterServer"));
      UASSERT (unreg_funct);
      if (!unreg_funct || (FAILED ((*unreg_funct) ())))
        {
          XULOG_ERROR ("failed unregister lib, " << path);
          return false;
        }
    }
  return true;
}
#endif

}}}      // namespace libs::helpers::files
