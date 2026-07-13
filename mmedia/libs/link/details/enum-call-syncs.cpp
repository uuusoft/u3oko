/**
\file       enum-call-syncs.cpp
\date       04.03.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
*/
#include "../_make/libs-link-includes_int.hpp"
#include "enum-call-syncs.hpp"

namespace libs::link::details
{
auto
to_string (const CallSyncs& val) -> const std::string&
{
  static const boost::unordered_flat_map< CallSyncs, const std::string > vals = {
    { CallSyncs::async, "async" },
    { CallSyncs::sync, "sync" },
    { CallSyncs::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    finger = vals.find (CallSyncs::unknown);
  }
  return finger->second;
}
}   // namespace libs::link::details
