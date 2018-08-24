//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       get-current-folders-functs.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "includes.hpp"
#include "get-current-folders-functs.hpp"

namespace libs { namespace iproperties { namespace appl_paths {
//  syn
using ::libs::iproperties::vers::system::ISystemProperty;
using ::libs::properties::ISharedProperty;

std::string
get_current_folder ()
{
  ISystemProperty::raw_ptr    _orinfo = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ());
  ISharedProperty::guard_type _guard (_orinfo->get_sync ());
  const std::string           _ret = _orinfo->get_appl_path_lockfree ();
  XULOG_TRACE ("get_current_folder=" << _ret);
  UASSERT (!_ret.empty ());
  return _ret;
}


std::string
get_current_lib_folder ()
{
  auto _ret = get_current_folder ();
#ifdef UUU_OS_ANDROID
  _ret += "/lib";
#endif
  return _ret;
}

}}}      // namespace libs::iproperties::appl_paths
