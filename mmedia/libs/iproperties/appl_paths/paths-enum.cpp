/**
\file       paths-enum.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       17.02.2012
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../libs-iproperties-includes_int.hpp"
#include "libs-iproperties-appl-paths-includes.hpp"

namespace libs::iproperties::appl_paths
{
const std::string&
to_string (const Paths& val)
{
  static const std::unordered_map< Paths, const std::string > tts2ss = {
    { Paths::generic_appl, "generic_appl" },
    { Paths::main_appl, "main_appl" },
    { Paths::bins, "bins" },
    { Paths::emulate_bins, "emulate_bins" },
    { Paths::logs, "logs" },
    { Paths::templates_event_module, "templates_event_module" },
    { Paths::templates_storage_module, "templates_storage_module" },
    { Paths::templates_data_module, "templates_data_module" },
    { Paths::templates_gui_module, "templates_gui_module" },
    { Paths::templates_appl_module, "templates_appl_module" },
    { Paths::active_appl_module, "active_appl_module" },
    { Paths::templates_http_module, "templates_http_module" },
    { Paths::temp, "temp" },
    { Paths::active_event_module, "active_event_module" },
    { Paths::active_storage_module, "active_storage_module" },
    { Paths::active_data_module, "active_data_module" },
    { Paths::active_configs, "configs" },
    { Paths::templates, "templates" },
    { Paths::debug_test, "" },
    { Paths::unknown, "" }
  };

  auto finger = tts2ss.find (val);
  if (tts2ss.end () == finger)
  {
    U3_XLOG_ERROR ("unknown val Paths" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    finger = tts2ss.find (Paths::unknown);
  }
  return finger->second;
}
}   // namespace libs::iproperties::appl_paths
