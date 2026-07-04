#if 0
/**
\file       enum-stream-updates.cpp
\author     Erashov Anton erashov2026@proton.me
\date       24.06.2022
\project    u3_events_storage
*/
#  include "mmedia/includes/control-defines-includes.hpp"
#  include "mmedia/includes/includes.hpp"
#  include "events-storage-includes_int.hpp"
#  include "enum-stream-updates.hpp"

namespace libs::events_storage
{
const std::string&
to_string (const StreamUpdates& val)
{
  static const boost::unordered_flat_map< StreamUpdates, const std::string > vals = {
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
}   // namespace libs::events_storage
#endif
