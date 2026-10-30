/**
\file       androidos_id.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
#include "../../../utility-lib-includes_int.hpp"
#include "sys-info-impl.hpp"

#ifdef U3_OS_ANDROID
#  include "cpu-features.h"

namespace libs::utility::sys::os::android
{
inline std::string
get_os_info ()
{
  std::string ret;
  std::string type_os = "unknown";
  ::libs::utility::checks::throw_exception ("failed");
  return ret;
}

inline std::string
get_mem_info ()
{
  std::string ret;
  // const std::int32_t b2mb = 1024 * 1024;
  ::libs::utility::checks::throw_exception ("failed");
  return ret;
}

inline std::string
get_display_info ()
{
  std::string ret;
  ::libs::utility::checks::throw_exception ("failed");
  return ret;
}

SysInfoImpl::~SysInfoImpl ()
{
}

std::string
SysInfoImpl::get (const HardwareType& type) const
{
  std::string ret ("???");

  switch (type)
  {
  case HardwareType::os:
    ret = get_os_info ();
    break;
  case HardwareType::memory:
    ret = get_mem_info ();
    break;
  case HardwareType::display:
    ret = get_display_info ();
    break;
  case HardwareType::cpu:
    helper_.full_text (ret);
    break;
#  ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  case HardwareType::cpu_speed:
    // ret = helpers::sys::cpu::x86::get_speed();
    ret = "???";
    break;
#  endif
  default:
    ::libs::utility::checks::throw_exception ("failed");
    break;
  }
  return ret;
}

short
SysInfoImpl::count_cpu () const
{
  std::size_t ret = U3_CAST_INT16 (android_getCpuCount ());
  ::libs::utility::checks::throw_ifn (ret > 0);
  return ret;
}
}   // namespace libs::utility::sys::os::android
#endif
