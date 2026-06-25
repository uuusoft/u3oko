/**
\file       factory_about_sys.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"

namespace libs::helpers::sys
{
ISysInfo::raw_ptr
get_impl ()
{
  static ISysInfo::ptr ret = nullptr;

  if (!ret)
  {
#ifdef U3_OS_WIN32_DESKTOP
    ret = std::make_shared< os::win32::SysInfoImpl > ();
#elif defined(U3_OS_ANDROID)
    ret = std::make_shared< os::android::SysInfoImpl > ();
#elif defined(U3_OS_GNU_LINUX)
    ret = std::make_shared< os::linux::SysInfoImpl > ();
#elif defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
    ret = std::make_shared< os::linux::SysInfoImpl > ();
#elif defined(U3_OS_MACX_DESKTOP)
    ret = std::make_shared< os::mac::SysInfoImpl > ();
#else
#  error select OS
#endif
  }
  return ret.get ();
}
}   // namespace libs::helpers::sys
