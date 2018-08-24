//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       androidos_id.cpp
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
#if defined(UUU_OS_GNU_LINUX) || defined(UUU_OS_RASPBERRY)
#include <sys/sysinfo.h>
#endif

namespace libs { namespace helpers { namespace sys { namespace os { namespace lnux {

#if defined(UUU_OS_GNU_LINUX) || defined(UUU_OS_RASPBERRY)
/**
  \brief  empty brief
  */
inline std::string
get_os_info ()
{
  std::string _ret;
  std::string _type_os = "unknown";
  UASSERT_SIGNAL ("failed");
  return _ret;
}
/**
  \brief  empty brief
  */
inline std::string
get_mem_info ()
{
  std::string _ret;
  const int   _b2mb = 1024 * 1024;
  UASSERT_SIGNAL ("failed");
  return _ret;
}
/**
  \brief  empty brief
  */
inline std::string
get_display_info ()
{
  std::string _ret;
  UASSERT_SIGNAL ("failed");
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
  short _ret = UUU_ICAST_SHORT (get_nprocs ());
  UASSERT (_ret > 0);
  return _ret;
}
#endif

}}}}}      // namespace libs::helpers::sys::os::lnux
