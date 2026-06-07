#pragma once
/**
\file       type-mouse-button.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/

namespace libs::igui_events::events
{
enum struct TypeMouseButton : std::uint32_t
{
  left    = 0x00,   //<
  right   = 0x01,   //<
  middle  = 0x02,   //<
  unknown = 0xFF    //<
};
}   // namespace libs::igui_events::events
