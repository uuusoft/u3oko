/**
\file       app-paths.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../libs-iproperties-includes_int.hpp"
#include "libs-iproperties-appl-paths-includes.hpp"
#include "app-paths.hpp"
#include "helpers/get_appl_folder.hpp"

namespace libs::iproperties::appl_paths
{
void
AppPaths::load_paths (const ::libs::link::appl::InitApplication& appl_info)
{
  paths_.clear ();
  U3_XLOG_DEV (TOLOG (appl_info.appl_name_) + TOLOG (appl_info.company_name_) + TOLOG (appl_info.service_name_))
  U3_CHECK (appl_info.check (), "failed appl_info.check")

  const auto appl_subfolder = ::libs::helpers::files::make_path (appl_info.company_name_, appl_info.appl_name_);
  const auto service_path   = ::libs::iproperties::appl_paths::helpers::get_data_folder (appl_subfolder, appl_info.service_name_);

  paths_[Paths::generic_appl] = ::libs::iproperties::appl_paths::helpers::get_appl_folder (appl_subfolder);
  paths_[Paths::main_appl]    = ::libs::iproperties::appl_paths::get_current_folder ();
  paths_[Paths::bins]         = ::libs::helpers::files::make_path (paths_[Paths::main_appl], get_path_suffix (Paths::bins));
  paths_[Paths::emulate_bins] = ::libs::helpers::files::make_path (paths_[Paths::main_appl], get_path_suffix (Paths::emulate_bins));

  // private service folders
  paths_[Paths::logs]                  = ::libs::helpers::files::make_path (service_path, get_path_suffix (Paths::logs));
  paths_[Paths::temp]                  = ::libs::helpers::files::make_path (service_path, get_path_suffix (Paths::temp));
  paths_[Paths::active_data_module]    = ::libs::helpers::files::make_path (service_path, get_path_suffix (Paths::active_data_module));
  paths_[Paths::active_appl_module]    = ::libs::helpers::files::make_path (service_path, get_path_suffix (Paths::active_appl_module));
  paths_[Paths::active_event_module]   = ::libs::helpers::files::make_path (service_path, get_path_suffix (Paths::active_event_module));
  paths_[Paths::active_storage_module] = ::libs::helpers::files::make_path (service_path, get_path_suffix (Paths::active_storage_module));
  // shared folders between services
  paths_[Paths::templates_event_module] = ::libs::helpers::files::make_path (paths_[Paths::generic_appl], get_path_suffix (Paths::templates_event_module));
  paths_[Paths::templates_appl_module]  = ::libs::helpers::files::make_path (paths_[Paths::generic_appl], get_path_suffix (Paths::templates_appl_module));
  paths_[Paths::templates_data_module]  = ::libs::helpers::files::make_path (paths_[Paths::generic_appl], get_path_suffix (Paths::templates_data_module));
  paths_[Paths::templates_gui_module]   = ::libs::helpers::files::make_path (paths_[Paths::generic_appl], get_path_suffix (Paths::templates_gui_module));
  paths_[Paths::templates_http_module]  = ::libs::helpers::files::make_path (paths_[Paths::generic_appl], get_path_suffix (Paths::templates_http_module));

#ifdef U3_OS_ANDROID
  paths_[Paths::bins]         = "";
  paths_[Paths::emulate_bins] = ::libs::helpers::files::make_path (paths_[Paths::generic_appl], get_path_suffix (Paths::emulate_bins));
  paths_[Paths::main_appl]    = paths_[Paths::bins];
#endif

  for (const auto& path : paths_)
  {
    ::libs::helpers::files::create_folder (path.second);
  }
}


std::string
AppPaths::get_path_suffix (const Paths& type) const
{
  switch (type)
  {
  case Paths::emulate_bins: {
#ifdef U3_OS_WIN32_DESKTOP
    return "";
#elif defined(U3_OS_ANDROID)
    return "emulate_bins";
#elif defined(U3_OS_GNU_LINUX)
    return "";
#elif defined(U3_OS_RASPBERRY)
    return "";
#elif defined(U3_OS_ORANGE_PI)
    return "";
#elif defined(U3_OS_MACX_DESKTOP)
    return "";
#else
#  error select OS
#endif
  }
  case Paths::bins:
    return {};
  case Paths::generic_appl:
    return {};
  case Paths::main_appl:
    return {};
  case Paths::logs:
    return "logs";
  case Paths::templates_event_module:
    return "templates/events";
  case Paths::templates_storage_module:
    return "templates/storage";
  case Paths::templates_data_module:
    return "templates/data";
  case Paths::templates_gui_module:
    return "templates/gui";
  case Paths::templates_appl_module:
    return "templates/appl";
  case Paths::templates_http_module:
    return "templates/http-server";
  case Paths::temp:
    return "temporal";
  case Paths::active_event_module:
    return "configs/events";
  case Paths::active_storage_module:
    return "configs/storage";
  case Paths::active_data_module:
    return "configs/data";
  case Paths::active_appl_module:
    return "configs/appl";
  case Paths::active_configs:
    return "configs";
  case Paths::templates:
    return "templates";
  case Paths::debug_test:
    U3_XLOG_WARN ("get Paths::debug_test");
    return "debug_test";
  case Paths::unknown:
    U3_XLOG_WARN ("get Paths::unknown");
    return "unknown";
  }

  U3_XLOG_ERROR ("unknown get suffix for " + to_string (type));
  return {};
}


std::string
AppPaths::get_path (const Paths& type) const
{
  switch (type)
  {
  case Paths::generic_appl:
  case Paths::logs:
  case Paths::main_appl:
  case Paths::bins:
  case Paths::emulate_bins:
  case Paths::templates_data_module:
  case Paths::templates_event_module:
  case Paths::templates_storage_module:
  case Paths::templates_gui_module:
  case Paths::templates_appl_module:
  case Paths::templates_http_module:
  case Paths::temp:
  case Paths::active_event_module:
  case Paths::active_storage_module:
  case Paths::active_data_module:
  case Paths::active_appl_module:
  case Paths::active_configs:
  case Paths::templates:
    return paths_[type];
  case Paths::debug_test:
    U3_ASSERT_SIGNAL_NT ("received Paths::debug_test");
    return {};
  case Paths::unknown:
    U3_ASSERT_SIGNAL_NT ("received Paths::unknown");
    return {};
  }

  U3_XLOG_ERROR ("get path for " + to_string (type));
  return {};
}
}   // namespace libs::iproperties::appl_paths
