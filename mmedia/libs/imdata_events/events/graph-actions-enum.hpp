#pragma once
/**
\file       graph-actions-enum.hpp
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

std::string to_string (const GraphActions& val);

inline constexpr GraphActions
change_graph_action_from_raw_val (std::uint32_t val)
{
  return U3_CAST_STATIC< GraphActions > (val);
}
}   // namespace libs::imdata_events::events
