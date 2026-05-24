/**
\file       type-time-stream.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.06.2022
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "istorage-events-includes_int.hpp"
#include "type-time-stream.hpp"

namespace libs::istorage_events
{
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
}   // namespace libs::istorage_events
