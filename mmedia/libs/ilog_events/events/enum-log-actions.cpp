/**
\file       enum-log-actions.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.06.2022
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "enum-log-actions.hpp"

namespace libs::ilog_events::events
{
// EAI-REFACT
std::string
to_string (const LogActions& act)
{
  switch (act)
  {
  case LogActions::get_sessions:
    return "get sessions";
  case LogActions::delete_sessions:
    return "delete sessions";
  case LogActions::unknown:
    return "unknown sessions";
  default:
    U3_ASSERT_SIGNAL ("unknown LogActions");
    break;
  }
  return "???";
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const LogActions& src)
{
  jvs = U3_CAST_UINT32_FORCE (src);
}


LogActions
tag_invoke (::boost::json::value_to_tag< LogActions >, const ::boost::json::value& jvs)
{
  return ::libs::helpers::casts::static_cast_helper< LogActions > (::libs::helpers::json::get_uint32 (jvs));
}
}   // namespace libs::ilog_events::events
