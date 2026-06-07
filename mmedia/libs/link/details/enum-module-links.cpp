/**
\file       enum-module-links.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       04.03.2022
\project    u3_link
*/
#include "../libs-link-includes_int.hpp"
#include "enum-module-links.hpp"

namespace libs::link::details
{
const std::string&
to_string (const ModuleLinks& val)
{
  static const std::unordered_map< ModuleLinks, const std::string > vals = {
    { ModuleLinks::appl, "appl" },
    { ModuleLinks::gui, "gui" },
    { ModuleLinks::http, "http" },
    { ModuleLinks::mdata, "mdata" },
    { ModuleLinks::log, "log" },
    { ModuleLinks::storage, "storage" },
    { ModuleLinks::rtp, "rtp" },
    { ModuleLinks::integration, "integration" },
    { ModuleLinks::events, "events" },
    { ModuleLinks::users, "users" },
    { ModuleLinks::network, "network" },
    { ModuleLinks::assistent, "assistent" },
    { ModuleLinks::ai, "ai" },
    { ModuleLinks::test, "test" },
    { ModuleLinks::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    finger = vals.find (ModuleLinks::unknown);
  }
  return finger->second;
}
}   // namespace libs::link::details
