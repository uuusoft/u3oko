#pragma once
/**
\file       sync-objs-time.hpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::events_base::runtime::control
{
enum class SyncTimes : std::uint32_t
{
  realtime = 0x00,   //<
  selected = 0x01,   //<
  unknown  = 0xFF    //< для общности
};

// EAI-REFACT
std::string to_string (const SyncTimes&);

inline constexpr SyncTimes
sync_objs_time_from_raw_val (std::uint32_t val)
{
  return ::libs::utility::casts::static_cast_helper< SyncTimes > (val);
}
}   // namespace libs::events_base::runtime::control
