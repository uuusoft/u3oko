/**
\file       sys-info-impl-mac.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.02.2022
\project    u3_helpers_lib
*/
#include "../../../utility-lib-includes_int.hpp"
#include "sys-info-impl.hpp"

#ifdef U3_OS_MACX_DESKTOP
namespace libs::utility::sys::os::mac
{
inline std::string
get_os_info ()
{
  std::string ret;
  std::string type_os = "unknown";
  U3_ASSERT_SIGNAL ("failed");
  return ret;
}

inline std::string
get_mem_info ()
{
  std::string        ret;
  const std::int32_t b2mb = 1024 * 1024;
  U3_ASSERT_SIGNAL ("failed");
  return ret;
}

inline std::string
get_display_info ()
{
  std::string ret;
  U3_ASSERT_SIGNAL ("failed");
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
    U3_ASSERT_SIGNAL ("failed");
    break;
  }
  return ret;
}

short
SysInfoImpl::count_cpu () const
{
  const std::int16_t ret = std::thread::hardware_concurrency ();
  U3_ASSERT (ret > 0);
  return ret;
}
}   // namespace libs::utility::sys::os::mac
#endif
