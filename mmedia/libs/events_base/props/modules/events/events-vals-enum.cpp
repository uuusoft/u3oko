/**
\file       events-vals-enum.cpp
\date       14.09.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../events-base-includes_int.hpp"
#include "events-vals-enum.hpp"

namespace libs::events_base::props::modules::events
{
auto
val2str (const EventsVals& val) -> const std::string&
{
  static boost::unordered_flat_map< EventsVals, const std::string > val2str = {
    { EventsVals::max_count_events, consts::max_count_events },
    { EventsVals::max_size_database, consts::max_size_database },
    { EventsVals::unknown, "unknown" },
  };

  auto finger = val2str.find (val);
  if (finger == val2str.end ())
  {
    U3_XLOG_WARN ("convert EventsVals to string" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    finger = val2str.find (EventsVals::unknown);
  }
  return finger->second;
}

auto
str2val (const std::string& str) -> EventsVals
{
  static const boost::unordered_flat_map< std::string, EventsVals > str2val = {
    { consts::max_count_events, EventsVals::max_count_events },
    { consts::max_size_database, EventsVals::max_size_database }
  };

  auto find = str2val.find (str);
  if (str2val.end () == find)
  {
    U3_XLOG_WARN ("convert string to EventsVals " + TOLOG (str));
    return EventsVals::no_val;
  }
  return find->second;
}
}   // namespace libs::events_base::props::modules::events
