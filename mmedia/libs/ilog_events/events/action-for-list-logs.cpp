/**
\file       action-for-list-logs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.06.2022
\project    uuu_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "action-for-list-logs.hpp"

namespace libs::ilog_events::events
{
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
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const LogActions& src)
{
  jv = U3_CAST_UINT32_FORCE (src);
}


LogActions
tag_invoke (::boost::json::value_to_tag< LogActions >, const ::boost::json::value& jv)
{
  return U3_CAST_STATIC< LogActions > (::libs::helpers::json::get_uint32 (jv));
}
}   // namespace libs::ilog_events::events
