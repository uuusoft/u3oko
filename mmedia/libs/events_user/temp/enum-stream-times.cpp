#if 0
/**
\file       enum-stream-times.cpp
\author     Erashov Anton erashov2026@proton.me
\date       24.06.2022
\project    u3_events_storage
*/
#  include "mmedia/includes/control-defines-includes.hpp"
#  include "mmedia/includes/includes.hpp"
#  include "events-storage-includes_int.hpp"
#  include "enum-stream-times.hpp"

namespace libs::events_storage
{
// EAI-REFACT
std::string
to_string (const StreamTimes& val)
{
  switch (val)
  {
  case StreamTimes::exactly:
    return "exactly";
  case StreamTimes::oldest:
    return "oldest";
  case StreamTimes::youngest:
    return "youngest";
  case StreamTimes::unknown:
    U3_ASSERT_SIGNAL_NT ("received StreamTimes::unknown");
    return "unknown";
  }
  U3_XLOG_ERROR ("unknown type StreamTimes" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
  return "xxx";
}
}   // namespace libs::events_storage
#endif
