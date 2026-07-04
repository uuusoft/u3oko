/**
\file       camera-focus-type.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "camera-focus-type.hpp"

namespace libs::events_base::props::videos::generic::driver
{
auto
str2focus (const std::string& str) -> Focus
{
  const boost::unordered_flat_map< std::string, Focus > vals = {
    { "auto_generic", Focus::auto_generic },
    { "auto_near", Focus::auto_near },
    { "auto_macro", Focus::auto_macro },
    { "caf", Focus::caf },
    { "caf_near", Focus::caf_near },
    { "fixed_infinity", Focus::fixed_infinity },
    { "fixed_hyperfocal", Focus::fixed_hyperfocal },
    { "fixed_near", Focus::fixed_near },
    { "fixed_macro", Focus::fixed_macro },
    { "fixed_cirrent", Focus::fixed_cirrent },
    { "fixed_max", Focus::fixed_max },
    { "edof", Focus::edof },
    { "caf_macro", Focus::caf_macro },
    { "caf_fast", Focus::caf_fast },
    { "caf_near_fast", Focus::caf_near_fast },
    { "caf_macro_fast", Focus::caf_macro_fast }
  };

  auto pval = vals.find (str);
  if (vals.end () == pval)
  {
    U3_XLOG_WARN ("unknown FocusType str " + str);
    return Focus::auto_generic;
  }
  return pval->second;
}


auto
camera_focus_from_raw_value (uint32_t val) -> Focus
{
  return ::libs::utility::casts::static_cast_helper< Focus > (val);
}
}   // namespace libs::events_base::props::videos::generic::driver
