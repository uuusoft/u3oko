/**
\file       sync-objs-action.cpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "sync-objs-action.hpp"

namespace libs::events_base::runtime::control
{
auto
to_string (const SyncActions& val) -> std::string
{
  switch (val)
  {
  case SyncActions::info:
    return "info";
  case SyncActions::sync:
    return "sync";
  case SyncActions::uplink:
    return "uplink";
  case SyncActions::downlink:
    return "downlink";
  case SyncActions::start:
    return "start";
  case SyncActions::stop:
    return "stop";
  case SyncActions::empty:
    return "empty";
  case SyncActions::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown SyncActions" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown SyncActions";
  }
}
}   // namespace libs::events_base::runtime::control
