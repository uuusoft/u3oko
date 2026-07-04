/**
\file       log-levels-enum.cpp
\author     Erashov Anton erashov2026@proton.me
\date       02.03.2022
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "log-levels-enum.hpp"

namespace libs::events_base::props::modules::log
{
auto
from_raw_val (std::uint32_t val) -> LogLevels
{
  return ::libs::utility::casts::static_cast_helper< LogLevels > (val);
}

auto
to_string (const LogLevels& val) -> const std::string&
{
  static const boost::unordered_flat_map< LogLevels, const std::string > val2str = {
    { LogLevels::disable, "disable" },
    { LogLevels::debug, "debug" },
    { LogLevels::develop, "develop" },
    { LogLevels::exception, "exception" },
    { LogLevels::invalid_state, "invalid_state" },
    { LogLevels::error, "error" },
    { LogLevels::warning, "warning" },
    { LogLevels::mark, "mark" },
    { LogLevels::info, "info" },
    { LogLevels::timing, "timing" },
    { LogLevels::data, "data" },
    { LogLevels::unknown, "unknown" }
  };

  auto finger = val2str.find (val);
  if (val2str.end () == finger)
  {
    U3_XLOG_WARN ("convert LogLevels to string" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    finger = val2str.find (LogLevels::unknown);
  }
  return finger->second;
}
}   // namespace libs::events_base::props::modules::log
