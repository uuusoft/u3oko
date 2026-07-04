/**
\file       enum-selector-impls.cpp
\author     Erashov Anton erashov2026@proton.me
\date       10.03.2022
\project    u3_events_base_lib
*/
#include "events-base-includes_int.hpp"
#include "enum-selector-impls.hpp"

namespace libs::events_base
{
// EAI-REFACT
auto
to_string (const SelectorImpls& val) -> std::string
{
  switch (val)
  {
  case SelectorImpls::automatic:
    return "automatic";
  case SelectorImpls::software:
    return "software";
  case SelectorImpls::hardware:
    return "hardware";
  case SelectorImpls::unknown:
    return "unknown";
  default:
    U3_XLOG_ERROR ("unknown SelectorImpls" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown SelectorImpls";
  }
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const SelectorImpls& src)
{
  jvs = U3_CAST_UINT32_FORCE (src);
}


auto
tag_invoke (::boost::json::value_to_tag< SelectorImpls >, const ::boost::json::value& jvs) -> SelectorImpls
{
  return ::libs::utility::casts::static_cast_helper< SelectorImpls > (::libs::utility::json::get_uint32 (jvs));
}
}   // namespace libs::events_base
