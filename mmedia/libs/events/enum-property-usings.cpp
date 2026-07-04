/**
\file       enum-property-usings.cpp
\date       18.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "includes_int.hpp"
#include "enum-property-usings.hpp"

namespace libs::events
{
auto
to_string (const PropertyUsings& val) -> const std::string&
{
  static const boost::unordered_flat_map< PropertyUsings, const std::string > valmap = {
    { PropertyUsings::disabled, "disabled" },
    { PropertyUsings::enabled, "enabled" },
    { PropertyUsings::automatic, "automatic" },
    { PropertyUsings::unknown, "unknown" }
  };

  auto finger = valmap.find (val);
  if (valmap.end () == finger)
  {
    U3_XLOG_WARN ("unknown type PropertyUsings" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    finger = valmap.find (PropertyUsings::unknown);
  }
  return finger->second;
}
}   // namespace libs::events
