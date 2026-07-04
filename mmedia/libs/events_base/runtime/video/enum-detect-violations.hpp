#pragma once
/**
\file       enum-detect-violations.hpp
\author     Erashov Anton erashov2026@proton.me
\date       08.06.2022
\project    u3_events_base_lib
*/

namespace libs::events_base::runtime::video
{
enum class DetectViolations : std::uint32_t
{
  start   = 0x00,   //<
  stop    = 0x01,   //<
  next    = 0x02,   //<
  unknown = 0xFF    //<
};
}   // namespace libs::events_base::runtime::video
