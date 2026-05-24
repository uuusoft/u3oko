#pragma once
/**
\file       sync-objs-time.hpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::control
{
enum class SyncTimes : std::uint32_t
{
  realtime = 0x00,   //<
  selected = 0x01,   //<
  unknown  = 0xFF    //< для общности
};

std::string to_string (const SyncTimes& val);

inline constexpr SyncTimes
sync_objs_time_from_raw_val (std::uint32_t val)
{
  return U3_CAST_STATIC< SyncTimes > (val);
}
}   // namespace libs::ievents::runtime::control
