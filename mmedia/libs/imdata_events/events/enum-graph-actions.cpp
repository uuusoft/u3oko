/**
\file       enum-graph-actions.cpp
\date       22.02.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-data-event.hpp"
#include "enum-graph-actions.hpp"

namespace libs::imdata_events::events
{
const std::string&
to_string (const GraphActions& val)
{
  static const std::unordered_map< GraphActions, const std::string > vals = {
    { GraphActions::add, "add" },
    { GraphActions::disable, "disable" },
    { GraphActions::enable, "enable" },
    { GraphActions::get, "get" },
    { GraphActions::remove, "remove" },
    { GraphActions::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    finger = vals.find (GraphActions::unknown);
  }
  return finger->second;
}
}   // namespace libs::imdata_events::events
