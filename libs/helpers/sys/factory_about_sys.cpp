//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       factory_about_sys.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"

namespace libs { namespace helpers { namespace sys {

const ISysInfo::raw_ptr
get_impl ()
{
  static ISysInfo::ptr _ret = nullptr;

  if (!_ret)
    {
#if defined(UUU_OS_WIN32_DESKTOP)
      _ret = std::make_shared<os::win32::SysInfoImpl> ();
#elif defined(UUU_OS_ANDROID)
      _ret = std::make_shared<os::android::SysInfoImpl> ();
#elif defined(UUU_OS_GNU_LINUX)
      _ret = std::make_shared<os::lnux::SysInfoImpl> ();
#elif defined(UUU_OS_RASPBERRY)
      _ret = std::make_shared<os::lnux::SysInfoImpl> ();
#else
#error select OS
#endif
    }

  return _ret.get ();
}

}}}      // namespace libs::helpers::sys
