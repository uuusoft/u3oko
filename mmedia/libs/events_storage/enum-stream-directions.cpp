/**
\file       enum-stream-directions.cpp
\author     Erashov Anton erashov2026@proton.me
\date       24.06.2022
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "events-storage-includes_int.hpp"
#include "enum-stream-directions.hpp"

namespace libs::events_storage
{
// EAI-REFACT
auto
to_string (const StreamDirections& val) -> std::string
{
  switch (val)
  {
  case StreamDirections::unknown:
    return "unknown";
  case StreamDirections::backward:
    return "backward";
  case StreamDirections::forward:
    return "forward";
  default:
    U3_XLOG_ERROR ("unknown StreamDirections" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown StreamDirections";
  }
}
}   // namespace libs::events_storage
