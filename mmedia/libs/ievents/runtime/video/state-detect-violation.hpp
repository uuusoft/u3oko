#pragma once
/**
\file       state-detect-violation.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       08.06.2022
\project    u3_ievents_lib
*/

namespace libs::ievents::runtime::video
{
enum class DetectViolations : std::uint32_t
{
  start   = 0x00,   //<
  stop    = 0x01,   //<
  next    = 0x02,   //<
  unknown = 0xFF    //<
};
}   // namespace libs::ievents::runtime::video
