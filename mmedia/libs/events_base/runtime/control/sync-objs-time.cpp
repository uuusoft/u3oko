/**
\file       sync-objs-time.cpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "sync-objs-time.hpp"

namespace libs::events_base::runtime::control
{
auto
to_string (const SyncTimes& val) -> std::string
{
  switch (val)
  {
  case SyncTimes::realtime:
    return "info";
  case SyncTimes::selected:
    return "selected";
  case SyncTimes::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown SyncTimes" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown SyncTimes";
  }
}
}   // namespace libs::events_base::runtime::control
