#pragma once
/**
\file       priorities-enum.hpp
\author     Erashov Anton erashov2026@proton.me
\date       11.05.2022
*/

namespace libs::utility::thread
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

auto to_string (const Priorities&) -> std::string;
auto set_thread_priority (const std::thread::id&, const Priorities&) -> void;
}   // namespace libs::utility::thread
