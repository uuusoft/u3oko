/**
\file       events-vals-enum.cpp
\date       14.09.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../includes_int.hpp"
#include "events-vals-enum.hpp"

namespace libs::ievents::props::modules::events
{
const std::string&
val2str (const EventsVals& val)
{
  static std::unordered_map< EventsVals, const std::string > val2str = {
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

EventsVals
str2val (const std::string& str)
{
  static const std::unordered_map< std::string, EventsVals > str2val = {
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
}   // namespace libs::ievents::props::modules::events
