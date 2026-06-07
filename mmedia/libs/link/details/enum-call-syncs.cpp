/**
\file       enum-call-syncs.cpp
\date       04.03.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_link
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../libs-link-includes_int.hpp"
#include "enum-call-syncs.hpp"

namespace libs::link::details
{
const std::string&
to_string (const CallSyncs& val)
{
  static const std::unordered_map< CallSyncs, const std::string > vals = {
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
