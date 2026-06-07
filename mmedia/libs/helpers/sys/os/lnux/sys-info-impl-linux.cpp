/**
\file       androidos_id.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../helpers-lib-includes_int.hpp"
#include "sys-info-impl.hpp"

#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
#  include <sys/sysinfo.h>

namespace libs::helpers::sys::os::linux
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
  std::string ret;
  // const std::int32_t b2mb = 1024 * 1024;
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
SysInfoImpl::get (const TypeInfo& type) const
{
  std::string ret ("???");

  switch (type)
  {
  case TypeInfo::os:
    ret = get_os_info ();
    break;
  case TypeInfo::memory:
    ret = get_mem_info ();
    break;
  case TypeInfo::display:
    ret = get_display_info ();
    break;
  case TypeInfo::cpu:
    helper_.full_text (ret);
    break;
#  if 0
    case TypeInfo::cpu_speed:
      //ret = helpers::sys::cpu::x86::get_speed();
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
  auto ret = U3_CAST_INT16 (get_nprocs ());
  U3_ASSERT (ret > 0);
  return ret;
}
}   // namespace libs::helpers::sys::os::linux

#endif
