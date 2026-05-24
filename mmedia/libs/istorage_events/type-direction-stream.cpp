/**
\file       type-direction-stream.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.06.2022
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "istorage-events-includes_int.hpp"
#include "type-direction-stream.hpp"

namespace libs::istorage_events
{
std::string
to_string (const StreamDirections& val)
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
}   // namespace libs::istorage_events
