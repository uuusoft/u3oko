/**
\file       enum-log-actions.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.06.2022
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "enum-log-actions.hpp"

namespace libs::events_log::events
{
// EAI-REFACT
auto
to_string (const LogActions& act) -> std::string
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


auto
tag_invoke (::boost::json::value_to_tag< LogActions >, const ::boost::json::value& jvs) -> LogActions
{
  return ::libs::utility::casts::static_cast_helper< LogActions > (::libs::utility::json::get_uint32 (jvs));
}
}   // namespace libs::events_log::events
