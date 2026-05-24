#pragma once
/**
\file       priorities-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       11.05.2022
\project    u3_helpers_lib
*/

namespace libs::helpers::thread
{
enum class Priorities : std::uint32_t
{
  freeze        = 0x00,   //<
  idle          = 0x01,   //<
  low           = 0x02,   //<
  below_normal  = 0x03,   //<
  normal        = 0x04,   //<
  above_normal  = 0x05,   //<
  high          = 0x06,   //<
  time_critical = 0x07,   //<
  unknown       = 0xFF    //<
};

std::string to_string (const Priorities& val);
void        set_thread_priority (const std::thread::id& thread, const Priorities& val);
}   // namespace libs::helpers::thread
