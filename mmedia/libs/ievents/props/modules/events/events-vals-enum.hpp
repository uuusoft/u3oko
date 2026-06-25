#pragma once
/**
\file       events-vals-enum.hpp
\date       14.09.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::modules::events
{
enum class EventsVals : std::uint32_t
{
  max_count_events  = 0x00,   //<
  max_size_database = 0x01,   //<
  no_val            = 0x1E,   //<
  max_val           = 0x1F,   //<
  unknown           = 0xFF    //< Не определенно для общности
};

const std::string& val2str (const EventsVals& val);
EventsVals         str2val (const std::string& str);

inline constexpr std::uint32_t
                 enum_to_raw (const EventsVals& val)
{
  return U3_CAST_UINT32_FORCE (val);
}
}   // namespace libs::ievents::props::modules::events
