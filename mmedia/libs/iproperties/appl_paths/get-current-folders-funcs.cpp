/**
\file       get-current-folders-funcs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_iproperties_lib
*/
#include "../libs-iproperties-includes_int.hpp"
#include "libs-iproperties-appl-paths-includes.hpp"
#include "get-current-folders-funcs.hpp"

namespace libs::iproperties::appl_paths
{
auto
get_current_folder () -> std::string
{
  auto*                           orinfo = iproperties::helpers::get_shared_prop_os ();
  syn::ISharedProperty::lock_type lock (orinfo->get_sync ());
  const std::string               ret = orinfo->get_appl_path_lockfree ();
  U3_ASSERT (!ret.empty ());
  return ret;
}


auto
get_current_lib_folder () -> std::string
{
  std::string ret = get_current_folder ();

#ifdef U3_OS_ANDROID
  ret = "";
  // ret += "/lib";
  // ret += "/lib/arm64-v8a";
#endif
  return ret;
}
}   // namespace libs::iproperties::appl_paths
