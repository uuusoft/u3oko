//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       get_appl_folder.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/

namespace libs { namespace iproperties { namespace appl_paths { namespace helpers {
//  syn
using ::libs::iproperties::vers::system::ISystemProperty;
using ::libs::properties::ISharedProperty;
/**
\brief  ???
*/
inline void
get_appl_folder (const std::string& _name_appl, std::string& _folder)
{
  CHECK_STATE (!_name_appl.empty (), "failed, name_appl empty");

#if defined(UUU_OS_WIN32_DESKTOP)
  {
    char _tbuff[2 * MAX_PATH + 1];
    _tbuff[0] = '\0';

    if (FAILED (SHGetFolderPathA (0, CSIDL_LOCAL_APPDATA, 0, SHGFP_TYPE_DEFAULT, _tbuff)))
      {
        UASSERT_SIGNAL ("failed");
        return;
      }

    _folder = ::libs::helpers::files::make_path (std::string (_tbuff), _name_appl);
  }
#elif defined(UUU_OS_ANDROID)
  _folder = get_current_folder ();
  _folder.clear ();
#else
  _folder = get_current_folder ();
#endif
  //  Может быть и пустым это нормально, тогда ничего не добавляем.
  if (!_folder.empty ())
    {
      _folder += "/";
    }
  return;
}
/**
\brief  ???
*/
inline void
get_data_folder (const std::string& _name_appl, std::string& _folder)
{
#if defined(UUU_OS_WIN32_DESKTOP)
  get_appl_folder (_name_appl, _folder);
#elif defined(UUU_OS_GNU_LINUX)
  get_appl_folder (_name_appl, _folder);
#elif defined(UUU_OS_RASPBERRY)
  get_appl_folder (_name_appl, _folder);
#elif defined(UUU_OS_ANDROID)
  ISystemProperty::raw_ptr    _orinfo = UUU_PROP_CAST (ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ());
  ISharedProperty::guard_type _guard (_orinfo->get_sync ());

  _folder = _orinfo->get_data_path_lockfree ();
#else
#error select OS
#endif

  XULOG_TRACE ("get_data_folder=" << _folder);
  return;
}

}}}}      // namespace libs::iproperties::appl_paths::helpers
