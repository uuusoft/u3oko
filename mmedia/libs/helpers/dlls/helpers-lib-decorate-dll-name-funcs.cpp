/**
\file       helpers-lib-decorate-dll-name-funcs.cpp
\date       25.02.2022
\author     Erashov Anton erashov2026@proton.me
\project    uuu_mem_funcs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"
#include "helpers-lib-decorate-dll-name-funcs.hpp"

namespace libs::helpers::dlls
{
std::string
decorate_dll_name (const std::string& dll)
{
  const auto prefix       = get_prefix ();
  const auto suffix       = get_dll_suffix ();
  const bool prefix_exist = 0 == dll.find (prefix);
  const bool suffix_exist = dll.length () - suffix.length () == dll.find (suffix);

  return (prefix_exist ? "" : prefix) + dll + (suffix_exist ? "" : suffix);
}

std::string
undecorate_dll_name (const std::string& dll)
{
  const auto  prefix       = get_prefix ();
  const auto  suffix       = get_dll_suffix ();
  const bool  prefix_exist = 0 == dll.find (prefix);
  const bool  suffix_exist = dll.length () - suffix.length () == dll.find (suffix);
  std::string res          = prefix_exist ? dll.substr (prefix.length ()) : dll;

  res = suffix_exist ? res.substr (0, res.length () - suffix.length ()) : res;
  return res;
}


std::string
get_prefix ()
{
#if defined(U3_OS_ANDROID) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
  const std::string prefix = "lib";
#elif defined(U3_OS_WIN32_DESKTOP)
  const std::string prefix = "";
#elif defined(U3_OS_MACX_DESKTOP)
  const std::string prefix = "lib";
#else
#  error select OS
#endif
  return prefix;
}


std::string
get_dll_suffix ()
{
#if defined(U3_OS_ANDROID) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
  const std::string suffix = ".so";
#elif defined(U3_OS_WIN32_DESKTOP)
  const std::string suffix = ".dll";
#elif defined(U3_OS_MACX_DESKTOP)
  const std::string suffix = ".dylib";
#else
#  error select OS
#endif
  return suffix;
}
}   // namespace libs::helpers::dlls
