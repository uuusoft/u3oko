/**
\file       decorate-dll-name-funcs.cpp
\date       25.02.2022
\author     Erashov Anton erashov2026@proton.me
\project    uuu_mems
*/
#include "../utility-lib-includes_int.hpp"
#include "decorate-dll-name-funcs.hpp"

namespace libs::utility::dlls
{
auto
make_func_name_lib (const std::string& lib_name, const std::string& prefix_func) -> std::string
{
  return prefix_func + "_" + undecorate_dll_name (lib_name);
}


auto
decorate_dll_name (const std::string& dll) -> std::string
{
  const auto prefix       = get_prefix ();
  const auto suffix       = get_dll_suffix ();
  const bool prefix_exist = dll.starts_with (prefix);
  const bool suffix_exist = dll.length () - suffix.length () == dll.find (suffix);

  return (prefix_exist ? "" : prefix) + dll + (suffix_exist ? "" : suffix);
}

auto
undecorate_dll_name (const std::string& dll) -> std::string
{
  const auto  prefix       = get_prefix ();
  const auto  suffix       = get_dll_suffix ();
  const bool  prefix_exist = dll.starts_with (prefix);
  const bool  suffix_exist = dll.length () - suffix.length () == dll.find (suffix);
  std::string res          = prefix_exist ? dll.substr (prefix.length ()) : dll;

  res = suffix_exist ? res.substr (0, res.length () - suffix.length ()) : res;
  return res;
}


auto
get_prefix () -> std::string
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


auto
get_dll_suffix () -> std::string
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
}   // namespace libs::utility::dlls
