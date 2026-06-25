/**
\file       enum-log-process-actions.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.06.2022
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "enum-log-process-actions.hpp"

namespace libs::ilog_events::events
{
// EAI-REFACT
std::string
to_string (const LogProcessActions& val)
{
  switch (val)
  {
  case LogProcessActions::get_raw_log:
    return "get raw log";
  case LogProcessActions::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown LogProcessActions" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return std::string ("unknown LogProcessActions") + VTOLOG (U3_CAST_UINT32_FORCE (val));
  }
}

void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const LogProcessActions& src)
{
  jvs = U3_CAST_UINT32_FORCE (src);
}


LogProcessActions
tag_invoke (::boost::json::value_to_tag< LogProcessActions >, const ::boost::json::value& jvs)
{
  return ::libs::helpers::casts::static_cast_helper< LogProcessActions > (::libs::helpers::json::get_uint32 (jvs));
}
}   // namespace libs::ilog_events::events
