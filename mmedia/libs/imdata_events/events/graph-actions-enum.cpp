/**
\file       graph-actions-enum.cpp
\date       22.02.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-data-event.hpp"
#include "graph-actions-enum.hpp"

namespace libs::imdata_events::events
{
std::string
to_string (const GraphActions& val)
{
  switch (val)
  {
  case GraphActions::add:
    return "add";
  case GraphActions::disable:
    return "disable";
  case GraphActions::enable:
    return "enable";
  case GraphActions::get:
    return "get";
  case GraphActions::remove:
    return "remove";
  case GraphActions::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown GraphActions" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown GraphActions";
  }
}
}   // namespace libs::imdata_events::events
