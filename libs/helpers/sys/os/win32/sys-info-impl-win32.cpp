//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       sys-info-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "sys-info-impl.hpp"

namespace libs { namespace helpers { namespace sys { namespace os { namespace win32 {
#if defined(UUU_OS_WIN32_DESKTOP)
/**
  \brief  empty brief
  */
inline std::string
get_os_info ()
{
  std::string    _ret;
  OSVERSIONINFOA _info;

  memset (&_info, 0, sizeof (_info));

  _info.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);

  if (!GetVersionExA (&_info))
    {
      UASSERT_SIGNAL ("failed");
      _ret = "GetVersionEx failed";
      _ret += ::libs::helpers::consts::new_line;
      return _ret;
    }

  _ret = "OS ";
  _ret += to_str (_info.dwMajorVersion);
  _ret += ".";
  _ret += to_str (_info.dwMinorVersion);
  _ret += " ";
  _ret += _info.szCSDVersion;
  _ret += ".";
  _ret += ::libs::helpers::consts::new_line;

  return _ret;
}
/**
  \brief  empty brief
  */
inline std::string
get_mem_info ()
{
  std::string    _ret;
  const int      _b2mb = 1024 * 1024;
  MEMORYSTATUSEX _info;

  memset (&_info, 0, sizeof (_info));
  _info.dwLength = sizeof (_info);

  if (!GlobalMemoryStatusEx (&_info))
    {
      UASSERT_SIGNAL ("failed");
      _ret = "GlobalMemoryStatusEx failed";
      _ret += ::libs::helpers::consts::new_line;
      return _ret;
    }

  _ret += "Mem load ";
  _ret += to_str (_info.dwMemoryLoad);
  _ret += ", ";
  _ret += to_str (_info.ullAvailPhys / _b2mb);
  _ret += "/";
  _ret += to_str (_info.ullTotalPhys / _b2mb);
  _ret += ", ";
  _ret += to_str (_info.ullAvailPageFile / _b2mb);
  _ret += "/";
  _ret += to_str (_info.ullTotalPageFile / _b2mb);
  _ret += "." + ::libs::helpers::consts::new_line;

  return _ret;
}
/**
  \brief  empty brief
  */
inline std::string
get_display_info ()
{
  std::string _ret;


  _ret += "Display, ";
  _ret += to_str (GetSystemMetrics (SM_CMONITORS));
  _ret += ", ";
  _ret += to_str (GetSystemMetrics (SM_CXFULLSCREEN));
  _ret += "x";
  _ret += to_str (GetSystemMetrics (SM_CYFULLSCREEN));
  _ret += ", ";
  _ret += to_str (GetSystemMetrics (SM_CXSCREEN));
  _ret += "x";
  _ret += to_str (GetSystemMetrics (SM_CYSCREEN));
  _ret += ", ";
  _ret += to_str (GetSystemMetrics (SM_CXVIRTUALSCREEN));
  _ret += "x";
  _ret += to_str (GetSystemMetrics (SM_CYVIRTUALSCREEN));

  HWND    _hwnd = GetDesktopWindow ();
  HBITMAP hbmp  = 0;

  if (!_hwnd)
    {
      UASSERT_SIGNAL ("failed");
      _ret += ".";
      _ret += ::libs::helpers::consts::new_line;
      return _ret;
    }

  HDC _hdc = GetDC (_hwnd);

  if (!_hdc)
    {
      UASSERT_SIGNAL ("failed");
      _ret += ".";
      _ret += ::libs::helpers::consts::new_line;
      return _ret;
    }

  const int _funct_ids[] = {
    BITSPIXEL,
    SHADEBLENDCAPS,
    RASTERCAPS,
    CURVECAPS,
    LINECAPS,
    POLYGONALCAPS,
    TEXTCAPS,
    COLORMGMTCAPS
  };

  std::array<int, 12> _functs;

  for (std::size_t indx1 = 0; indx1 < COUNT_OF (_funct_ids); ++indx1)
    {
      _functs[indx1] = GetDeviceCaps (_hdc, _funct_ids[indx1]);
    }

  hbmp = static_cast<HBITMAP> (GetCurrentObject (_hdc, OBJ_BITMAP));

  if (hbmp)
    {
      _ret += ", bits ";
      _ret += to_str (_functs[0]);
      _ret += ", shade ";
      _ret += to_str (_functs[1]);
      _ret += ", raster ";
      _ret += to_str (_functs[2]);
      _ret += ", curve ";
      _ret += to_str (_functs[3]);
      _ret += ", line ";
      _ret += to_str (_functs[4]);
      _ret += ", polygon ";
      _ret += to_str (_functs[5]);
      _ret += ", text ";
      _ret += to_str (_functs[6]);
      _ret += ", color ";
      _ret += to_str (_functs[7]);
      _ret += ".";
    }

  _ret += ::libs::helpers::consts::new_line;

  CHECK_CALL (ReleaseDC (_hwnd, _hdc), "failed release dc");

  return _ret;
}


SysInfoImpl::~SysInfoImpl ()
{}


std::string
SysInfoImpl::get (const TypeInfo& _type) const
{
  std::string _ret ("???");

  switch (_type)
    {
    case TypeInfo::os:
      _ret = get_os_info ();
      break;
    case TypeInfo::memory:
      _ret = get_mem_info ();
      break;
    case TypeInfo::display:
      _ret = get_display_info ();
      break;
    case TypeInfo::cpu:
      helper_.full_text (_ret);
      break;
#if 0
    case TypeInfo::cpu_speed:
      //_ret = helpers::sys::cpu::x86::get_speed();
      _ret = "???";
      break;
#endif
    default:
      UASSERT_SIGNAL ("failed");
      break;
    }

  return _ret;
}


short
SysInfoImpl::count_cpu () const
{
  short ret = 0;

  do
    {
      DWORD_PTR _process_mask = 0;
      DWORD_PTR _system_mask  = 0;

      if (!GetProcessAffinityMask (GetCurrentProcess (), &_process_mask, &_system_mask))
        {
          ret = 1;
          break;
        }

      for (std::size_t indx_bit = 0; indx_bit < sizeof (_system_mask) * 8; ++indx_bit)
        {
          if (_system_mask & 0x1)
            {
              ret++;
            }

          _system_mask >>= 1;
        }

#if 1

#elif defined(MAC_OSX)
      int    mib[2];
      int    maxproc = 0;
      size_t len     = 0;

      mib[0] = CTL_KERN;
      mib[1] = KERN_MAXPROC;
      len    = sizeof (maxproc);
      sysctl (mib, 2, &maxproc, &len, 0, 0);

      ret += len;
#else
      cpu_set_t cpu_info;
      int       ResFunct = sched_getaffinity (getpid (), sizeof (cpu_info), &cpu_info);
      for (unsigned int indx_cpu = 0; indx_cpu < sizeof (cpu_info); ++indx_cpu)
        {
          ret += CPU_ISSET (indx_cpu, &cpu_info);
        }
#endif
    }
  while (false);

  return ret;
}
#endif
}}}}}      // namespace libs::helpers::sys::os::win32
