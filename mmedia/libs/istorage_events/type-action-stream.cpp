/**
\file       type-action-stream.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.06.2022
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "istorage-events-includes_int.hpp"
#include "type-action-stream.hpp"

namespace libs::istorage_events
{
std::string
to_string (const StreamActions& val)
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
}   // namespace libs::istorage_events
