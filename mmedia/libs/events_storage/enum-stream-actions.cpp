/**
\file       enum-stream-actions.cpp
\author     Erashov Anton erashov2026@proton.me
\date       24.06.2022
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "events-storage-includes_int.hpp"
#include "enum-stream-actions.hpp"

namespace libs::events_storage
{
// EAI-REFACT
auto
to_string (const StreamActions& val) -> std::string
{
  switch (val)
  {
  case StreamActions::read:
    return "read";
  case StreamActions::write:
    return "write";
  case StreamActions::modification:
    return "modification";
  case StreamActions::unknown:
    return "unknown";
  }
  U3_XLOG_WARN ("unknown StreamActions" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
  return "xxx";
}
}   // namespace libs::events_storage
