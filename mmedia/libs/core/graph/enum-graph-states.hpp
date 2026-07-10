#pragma once
/**
\file       enum-graph-states.hpp
\author     Erashov Anton erashov2026@proton.me
\date       28.02.2022
\project    u3_core_lib
*/

namespace libs::core::graph
{
enum class GraphStates : std::uint32_t
{
  enable  = 0x00,   //<
  disable = 0x01,   //<
  unknown = 0xFF    //<
};
}   // namespace libs::core::graph
