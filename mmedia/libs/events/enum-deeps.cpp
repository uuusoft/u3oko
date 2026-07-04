/**
\file       deeps-enum.cpp
\date       18.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "includes_int.hpp"
#include "enum-deeps.hpp"

namespace libs::events
{
auto
to_string (const Deeps& val) -> const std::string&
{
  static const boost::unordered_flat_map< Deeps, const std::string > valmap = {
    { Deeps::empty, "empty" },
    { Deeps::full, "full" },
    { Deeps::unknown, "unknown" }
  };

  auto finger = valmap.find (val);
  if (valmap.end () == finger)
  {
    U3_XLOG_WARN ("unknown type Deeps" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    finger = valmap.find (Deeps::unknown);
  }
  return finger->second;
}
}   // namespace libs::events
