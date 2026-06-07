/**
\file       enum-stream-updates.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.06.2022
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "istorage-events-includes_int.hpp"
#include "enum-stream-updates.hpp"

namespace libs::istorage_events
{
const std::string&
to_string (const StreamUpdates& val)
{
  static const std::unordered_map< StreamUpdates, const std::string > vals = {
    { StreamUpdates::open, "open" },
    { StreamUpdates::close, "close" },
    { StreamUpdates::check_and_get_info, "check_and_get_info" },
    { StreamUpdates::change, "change" },
    { StreamUpdates::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    U3_ASSERT_SIGNAL_NT ("received StreamUpdates::unknown");
    finger = vals.find (StreamUpdates::unknown);
  }
  return finger->second;
}
}   // namespace libs::istorage_events
