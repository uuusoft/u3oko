/**
\file       androidos_id.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "../../../utility-lib-includes_int.hpp"
#include "sys-info-impl.hpp"

#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
#  include <sys/sysinfo.h>

namespace libs::utility::sys::os::linux
{
inline auto
get_os_info () -> std::string
{
  std::string ret;
  std::string type_os = "unknown";
  U3_ASSERT_SIGNAL ("failed");
  return ret;
}

inline auto
get_mem_info () -> std::string
{
  std::string ret;
  // const std::int32_t b2mb = 1024 * 1024;
  U3_ASSERT_SIGNAL ("failed");
  return ret;
}

inline auto
get_display_info () -> std::string
{
  std::string ret;
  U3_ASSERT_SIGNAL ("failed");
  return ret;
}

SysInfoImpl::~SysInfoImpl () = default;

auto
SysInfoImpl::get (const HardwareType& type) const -> std::string
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

auto
SysInfoImpl::count_cpu () const -> short
{
  auto ret = U3_CAST_INT16 (get_nprocs ());
  U3_ASSERT (ret > 0);
  return ret;
}
}   // namespace libs::utility::sys::os::linux

#endif
