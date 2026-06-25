/**
\file       enum-ops-status.cpp
\author     Erashov Anton erashov2026@proton.me
\date       10.03.2022
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "enum-ops-status.hpp"

namespace libs::ievents
{
// EAI-REFACT
const std::string&
to_string (const OpsStatus& val)
{
  static const std::unordered_map< OpsStatus, const std::string > vals = {
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


OpsStatus
tag_invoke (::boost::json::value_to_tag< OpsStatus >, const ::boost::json::value& jvs)
{
  return ::libs::helpers::casts::static_cast_helper< OpsStatus > (::libs::helpers::json::get_uint32 (jvs));
}
}   // namespace libs::ievents
