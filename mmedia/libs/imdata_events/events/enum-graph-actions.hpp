#pragma once
/**
\file       enum-graph-actions.hpp
\date       14.09.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/

namespace libs::imdata_events::events
{
enum class GraphActions : std::uint32_t
{
  get     = 0x00,   //<
  add     = 0x01,   //<
  disable = 0x02,   //<
  enable  = 0x03,   //<
  remove  = 0x1F,   //<
  unknown = 0xFF    //<
};

const std::string& to_string (const GraphActions& val);

inline constexpr GraphActions
change_graph_action_from_raw_val (std::uint32_t val)
{
  return ::libs::helpers::casts::static_cast_helper< GraphActions > (val);
}
}   // namespace libs::imdata_events::events
