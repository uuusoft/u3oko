/**
\file       get-current-folders-funcs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../libs-iproperties-includes_int.hpp"
#include "libs-iproperties-appl-paths-includes.hpp"
#include "get-current-folders-funcs.hpp"

namespace libs::iproperties::appl_paths
{
auto
get_current_folder () -> std::string
{
  // U3_XLOG_DEV ("get_current_folder:0");
  auto* orinfo = iproperties::helpers::get_shared_prop_os ();
  // U3_XLOG_DEV ("get_current_folder:1");
  syn::ISharedProperty::lock_type lock (orinfo->get_sync ());
  // U3_XLOG_DEV ("get_current_folder:2");
  const std::string ret = orinfo->get_appl_path_lockfree ();
  // U3_XLOG_DEV ("get_current_folder:3" + TOLOG (ret));
  ::libs::utility::checks::throw_ifn (!ret.empty ());
  // U3_XLOG_DEV ("get_current_folder:4");
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
