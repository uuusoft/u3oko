//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       AppPaths.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "includes.hpp"
#include "app-paths.hpp"
#include "helpers/get_appl_folder.hpp"

namespace libs { namespace iproperties { namespace appl_paths {

AppPaths::AppPaths ()
{}


AppPaths::~AppPaths ()
{}


void
AppPaths::load (
  const std::string& _name_company,
  const std::string& _name_app,
  const std::string& _ver_app)
{
  XULOG_TRACE ("AppPaths::load::_name_company=" << _name_company);
  XULOG_TRACE ("AppPaths::load::_name_app=" << _name_app);
  XULOG_TRACE ("AppPaths::load::_ver_app=" << _ver_app);

  paths_.clear ();

  CHECK_STATE (!_name_company.empty (), "failed, empty name company");

  const std::string _sub_appl = ::libs::helpers::files::make_path (_name_company, _name_app);
  std::string       _data_path;

  helpers::get_appl_folder (_sub_appl, paths_[TypePath::generic_appl]);
  helpers::get_data_folder (_sub_appl, _data_path);

  XULOG_TRACE ("AppPaths::load, paths_[ TypePath::generic_appl]=" << paths_[TypePath::generic_appl]);

  paths_[TypePath::images]          = ::libs::helpers::files::make_path (paths_[TypePath::generic_appl], get_suffix (TypePath::images));
  paths_[TypePath::logs]            = ::libs::helpers::files::make_path (_data_path, get_suffix (TypePath::logs));
  paths_[TypePath::temp]            = ::libs::helpers::files::make_path (_data_path, get_suffix (TypePath::temp));
  paths_[TypePath::work]            = ::libs::helpers::files::make_path (_data_path, get_suffix (TypePath::work));
  paths_[TypePath::default_storage] = ::libs::helpers::files::make_path (_data_path, get_suffix (TypePath::default_storage));

  paths_[TypePath::appl_xml] = ::libs::helpers::files::make_path (paths_[TypePath::generic_appl], get_suffix (TypePath::appl_xml));
  paths_[TypePath::data_xml] = ::libs::helpers::files::make_path (paths_[TypePath::generic_appl], get_suffix (TypePath::data_xml));
  paths_[TypePath::gui_xml]  = ::libs::helpers::files::make_path (paths_[TypePath::generic_appl], get_suffix (TypePath::gui_xml));
  paths_[TypePath::web]      = ::libs::helpers::files::make_path (paths_[TypePath::generic_appl], get_suffix (TypePath::web));

  paths_[TypePath::main_exe] = ::libs::iproperties::appl_paths::get_current_folder ();
  paths_[TypePath::bins]     = ::libs::helpers::files::make_path (paths_[TypePath::main_exe], get_suffix (TypePath::bins));

  XULOG_TRACE ("AppPaths::load, paths_[ TypePath::main_exe]=" << paths_[TypePath::main_exe]);

#if defined(UUU_OS_ANDROID)
  paths_[TypePath::main_exe] = paths_[TypePath::bins];
#endif

  for (const path2string_type::value_type& _path : paths_)
    {
      XULOG_INFO ("AppPaths::prepare make " << to_str (_path.first) << ", value=" << _path.second);
      ::libs::helpers::files::create_folder (_path.second);
    }
  return;
}


std::string
AppPaths::get_suffix (const TypePath& _type) const
{
  switch (_type)
    {
    case TypePath::generic_appl:
    case TypePath::main_exe:
      return "";
    case TypePath::bins:
#if defined(UUU_OS_WIN32_DESKTOP)
      return "";
#elif defined(UUU_OS_ANDROID)
      return "lib";
#elif defined(UUU_OS_GNU_LINUX)
      return "";
#elif defined(UUU_OS_RASPBERRY)
      return "";
#else
#error select OS
#endif
    case TypePath::logs:
      return "log";
    case TypePath::images:
      return "res/default";
    case TypePath::media:
      return "res/default";
    case TypePath::data_xml:
      return "xmls/data";
    case TypePath::gui_xml:
      return "xmls/gui";
    case TypePath::appl_xml:
      return "xmls/appl";
    case TypePath::web:
      return "web";
    case TypePath::temp:
      return "utemp";
    case TypePath::work:
      return "work";
    case TypePath::default_storage:
      return "storage";
    }

  XULOG_ERROR ("failed get suffix for " << to_str (_type));
  return "";
}


std::string
AppPaths::get_path (const TypePath& _type) const
{
  switch (_type)
    {
    case TypePath::generic_appl:
    case TypePath::logs:
    case TypePath::main_exe:
    case TypePath::bins:
    case TypePath::data_xml:
    case TypePath::images:
    case TypePath::media:
    case TypePath::gui_xml:
    case TypePath::appl_xml:
    case TypePath::web:
    case TypePath::temp:
    case TypePath::work:
    case TypePath::default_storage:
      {
        XULOG_TRACE ("AppPaths::get_path, " << paths_[_type]);
        return paths_[_type];
      }
    }
  XULOG_ERROR ("failed get path for " << to_str (_type));
  return std::string ();
}

}}}      // namespace libs::iproperties::appl_paths
