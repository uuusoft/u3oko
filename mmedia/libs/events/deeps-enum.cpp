/**
\file       deeps-enum.cpp
\date       18.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    uuu_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "deeps-enum.hpp"

namespace libs::events
{
const std::string&
to_string (const Deeps& val)
{
  static const std::unordered_map< Deeps, const std::string > valmap = {
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
