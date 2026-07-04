/**
\file       enum-ops-status.cpp
\author     Erashov Anton erashov2026@proton.me
\date       10.03.2022
\project    u3_events_base_lib
*/
#include "events-base-includes_int.hpp"
#include "enum-ops-status.hpp"

namespace libs::events_base
{
// EAI-REFACT
auto
to_string (const OpsStatus& val) -> const std::string&
{
  static const boost::unordered_flat_map< OpsStatus, const std::string > vals = {
    { OpsStatus::success, "success" },
    { OpsStatus::failed, "failed" },
    { OpsStatus::mixed, "mixed" },
    { OpsStatus::unset, "unset" },
    { OpsStatus::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    U3_XLOG_ERROR ("unknown OpsStatus" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    finger = vals.find (OpsStatus::unknown);
  }
  return finger->second;
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const OpsStatus& src)
{
  jvs = U3_CAST_UINT32_FORCE (src);
}


auto
tag_invoke (::boost::json::value_to_tag< OpsStatus >, const ::boost::json::value& jvs) -> OpsStatus
{
  return ::libs::utility::casts::static_cast_helper< OpsStatus > (::libs::utility::json::get_uint32 (jvs));
}
}   // namespace libs::events_base
