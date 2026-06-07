#pragma once
/**
\file       enum-graph-node-actions.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/

namespace libs::imdata_events::events
{
enum class GraphNodeActions : std::uint32_t
{
  get     = 0x00,   //<
  set     = 0x01,   //<
  unknown = 0xFF    //<
};

inline constexpr GraphNodeActions
change_node_graph_action_from_raw_value (std::uint32_t val)
{
  return ::libs::helpers::casts::static_cast_helper< GraphNodeActions > (val);
}
}   // namespace libs::imdata_events::events
