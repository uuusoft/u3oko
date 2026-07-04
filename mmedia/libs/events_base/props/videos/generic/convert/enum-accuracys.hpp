#pragma once
/**
\file       enum-accuracys.hpp
\author     Erashov Anton erashov2026@proton.me
\date       29.07.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::convert
{
enum class Accuracys : std::uint32_t
{
  usual   = 0x00,   //<
  fast    = 0x01,   //<
  best    = 0x02,   //<
  unknown = 0xFF    //<
};
}   // namespace libs::events_base::props::videos::generic::convert
