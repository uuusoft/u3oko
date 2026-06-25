/**
\file       camera-focus-type.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "camera-focus-type.hpp"

namespace libs::ievents::props::videos::generic::driver
{
Focus
str2focus (const std::string& str)
{
  const std::unordered_map< std::string, Focus > vals = {
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


Focus
camera_focus_from_raw_value (uint32_t val)
{
  return ::libs::helpers::casts::static_cast_helper< Focus > (val);
}
}   // namespace libs::ievents::props::videos::generic::driver
