/**
\file       update-home-folder-func.cpp
\date       25.02.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"
#include "update_register_lib_func.hpp"
#include "libs-helpers-files-includes.hpp"
#include "update-home-folder-func.hpp"

#ifdef U3_OS_WIN32_DESKTOP
#  include <Shlobj.h>
#endif

namespace libs::utility::files
{
auto
get_home_folder () -> std::string
{
#ifdef U3_OS_WIN32_DESKTOP
  PWSTR path = nullptr;
  if (SUCCEEDED (SHGetKnownFolderPath (FOLDERID_Profile, 0, NULL, &path)))
  {
    const auto  path_len   = std::wcslen (path);
    const auto  sizeNeeded = WideCharToMultiByte (CP_ACP, 0, path, U3_CAST_INT32 (path_len), NULL, 0, NULL, NULL);
    std::string home_folder (sizeNeeded, 0);
    WideCharToMultiByte (CP_ACP, 0, path, U3_CAST_INT32 (path_len), &home_folder[0], U3_CAST_INT32 (sizeNeeded), NULL, NULL);
    CoTaskMemFree (path);
    return home_folder;
  }
  return "";
#else
  const char* home_folder = std::getenv ("HOME");
  return home_folder ? home_folder : "";
#endif
}


auto
update_home_folder (const std::string& path) -> std::string
{
  if (path.empty () || path[0] != '~')
  {
    return path;
  }

  const auto home_folder = get_home_folder ();
  if (home_folder.empty ())
  {
    U3_XLOG_WARN ("get null home folder from enviroment for" + TOLOG (path));
    return path;
  }
  return std::string (home_folder) + path.substr (1, std::string::npos);
}
}   // namespace libs::utility::files
