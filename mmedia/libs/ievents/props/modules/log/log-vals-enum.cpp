/**
\file       log-vals-enum.cpp
\date       01.03.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../includes_int.hpp"
#include "property-log-module-event.hpp"

namespace libs::ievents::props::modules::log
{
std::atomic< LogLevels > g_log_level = LogLevels::info;

const std::string&
val2str (const LogVals& val)
{
  static const std::unordered_map< LogVals, const std::string > val2str = {
    { LogVals::max_cache_events, consts::max_cache_events },
    { LogVals::ms_max_period_flush_events, consts::ms_max_period_flush_events },
    { LogVals::max_size_one_log_file_byte, consts::max_size_one_log_file_byte },
    { LogVals::enable_store_call_place, consts::enable_store_call_place },
    { LogVals::enable_log_events, consts::enable_log_events },
    { LogVals::log_level, consts::log_level },
    { LogVals::enable_suppress_duplicate_msg, consts::enable_suppress_duplicate_msg },
    { LogVals::no_val, consts::no_val }
  };

  auto finger = val2str.find (val);
  if (val2str.end () == finger)
  {
    U3_XLOG_WARN ("convert LogVals to string" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    finger = val2str.find (LogVals::no_val);
  }
  return finger->second;
}


LogVals
str2val (const std::string& str)
{
  static const std::unordered_map< std::string, const LogVals > str2val = {
    { consts::max_cache_events, LogVals::max_cache_events },
    { consts::ms_max_period_flush_events, LogVals::ms_max_period_flush_events },
    { consts::max_size_one_log_file_byte, LogVals::max_size_one_log_file_byte },
    { consts::enable_store_call_place, LogVals::enable_store_call_place },
    { consts::enable_log_events, LogVals::enable_log_events },
    { consts::log_level, LogVals::log_level },
    { consts::enable_suppress_duplicate_msg, LogVals::enable_suppress_duplicate_msg }
  };

  auto find = str2val.find (str);
  if (str2val.end () == find)
  {
    U3_XLOG_WARN ("convert string to LogVals " + str);
    return LogVals::no_val;
  }
  return find->second;
}
}   // namespace libs::ievents::props::modules::log
