/**
\file       sys-info-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../helpers-lib-includes_int.hpp"
#include "sys-info-impl.hpp"

#if defined(U3_OS_WIN32_DESKTOP)

namespace libs::helpers::sys::os::win32
{
inline std::string
get_os_info ()
{
  std::string    ret;
  OSVERSIONINFOA info;

  memset (&info, 0, sizeof (info));

  info.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);

  if (!GetVersionExA (&info))
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    ret = "GetVersionEx failed";
    ret += ::libs::helpers::consts::new_line;
    return ret;
  }

  ret = "OS ";
  ret += std::to_string (info.dwMajorVersion);
  ret += ".";
  ret += std::to_string (info.dwMinorVersion);
  ret += " ";
  ret += info.szCSDVersion;
  ret += ".";
  ret += ::libs::helpers::consts::new_line;

  return ret;
}


inline std::string
get_mem_info ()
{
  std::string        ret;
  const std::int32_t b2mb = 1024 * 1024;
  MEMORYSTATUSEX     info;

  memset (&info, 0, sizeof (info));
  info.dwLength = sizeof (info);

  if (!GlobalMemoryStatusEx (&info))
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    ret = "GlobalMemoryStatusEx failed";
    ret += ::libs::helpers::consts::new_line;
    return ret;
  }

  ret += "Mem load ";
  ret += std::to_string (info.dwMemoryLoad);
  ret += ", ";
  ret += std::to_string (info.ullAvailPhys / b2mb);
  ret += "/";
  ret += std::to_string (info.ullTotalPhys / b2mb);
  ret += ", ";
  ret += std::to_string (info.ullAvailPageFile / b2mb);
  ret += "/";
  ret += std::to_string (info.ullTotalPageFile / b2mb);
  ret += "." + ::libs::helpers::consts::new_line;

  return ret;
}


inline std::string
get_display_info ()
{
  std::string ret;

  ret += "Display, ";
  ret += std::to_string (GetSystemMetrics (SM_CMONITORS));
  ret += ", ";
  ret += std::to_string (GetSystemMetrics (SM_CXFULLSCREEN));
  ret += "x";
  ret += std::to_string (GetSystemMetrics (SM_CYFULLSCREEN));
  ret += ", ";
  ret += std::to_string (GetSystemMetrics (SM_CXSCREEN));
  ret += "x";
  ret += std::to_string (GetSystemMetrics (SM_CYSCREEN));
  ret += ", ";
  ret += std::to_string (GetSystemMetrics (SM_CXVIRTUALSCREEN));
  ret += "x";
  ret += std::to_string (GetSystemMetrics (SM_CYVIRTUALSCREEN));

  HWND    hwnd = GetDesktopWindow ();
  HBITMAP hbmp = 0;

  if (!hwnd)
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    ret += ".";
    ret += ::libs::helpers::consts::new_line;
    return ret;
  }

  HDC hdc = GetDC (hwnd);

  if (!hdc)
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    ret += ".";
    ret += ::libs::helpers::consts::new_line;
    return ret;
  }

  const std::int32_t func_ids[] = {
    BITSPIXEL,
    SHADEBLENDCAPS,
    RASTERCAPS,
    CURVECAPS,
    LINECAPS,
    POLYGONALCAPS,
    TEXTCAPS,
    COLORMGMTCAPS
  };

  std::array< int, 12 > funcs;

  for (std::size_t indx1 = 0; indx1 < std::size (func_ids); ++indx1)
  {
    funcs[indx1] = GetDeviceCaps (hdc, func_ids[indx1]);
  }

  hbmp = U3_CAST_STATIC< HBITMAP > (GetCurrentObject (hdc, OBJ_BITMAP));

  if (hbmp)
  {
    ret += ", bits ";
    ret += std::to_string (funcs[0]);
    ret += ", shade ";
    ret += std::to_string (funcs[1]);
    ret += ", raster ";
    ret += std::to_string (funcs[2]);
    ret += ", curve ";
    ret += std::to_string (funcs[3]);
    ret += ", line ";
    ret += std::to_string (funcs[4]);
    ret += ", polygon ";
    ret += std::to_string (funcs[5]);
    ret += ", text ";
    ret += std::to_string (funcs[6]);
    ret += ", color ";
    ret += std::to_string (funcs[7]);
    ret += ".";
  }

  ret += ::libs::helpers::consts::new_line;
  U3_CHECK (ReleaseDC (hwnd, hdc), "release dc");
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


std::int16_t
SysInfoImpl::count_cpu () const
{
  std::int16_t ret = 0;

  do
  {
    DWORD_PTR process_mask = 0;
    DWORD_PTR system_mask  = 0;

    if (!GetProcessAffinityMask (GetCurrentProcess (), &process_mask, &system_mask))
    {
      ret = 1;
      break;
    }

    for (std::size_t indx_bit = 0; indx_bit < sizeof (system_mask) * 8; ++indx_bit)
    {
      if (system_mask & 0x1)
      {
        ret++;
      }

      system_mask >>= 1;
    }

#  if 1

#  elif defined(MAC_OSX)
    int    mib[2];
    int    maxproc = 0;
    size_t len     = 0;

    mib[0] = CTL_KERN;
    mib[1] = KERN_MAXPROC;
    len    = sizeof (maxproc);
    sysctl (mib, 2, &maxproc, &len, 0, 0);

    ret += len;
#  else
    cpu_set_t cpu_info;
    int       ResFunct = sched_getaffinity (getpid (), sizeof (cpu_info), &cpu_info);
    for (uint32_t indx_cpu = 0; indx_cpu < sizeof (cpu_info); ++indx_cpu)
    {
      ret += CPU_ISSET (indx_cpu, &cpu_info);
    }
#  endif
  } while (false);

  return ret;
}
}   // namespace libs::helpers::sys::os::win32

#endif
