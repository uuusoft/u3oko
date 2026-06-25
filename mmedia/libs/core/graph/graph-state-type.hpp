#pragma once
/**
\file       graph-state-type.hpp
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

inline constexpr std::uint32_t
                 graph_state_type_to_raw (const GraphStates& val)
{
  return U3_CAST_UINT32_FORCE (val);
}
}   // namespace libs::core::graph
