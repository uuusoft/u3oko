#pragma once
/**
\file       type-events.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/

namespace libs::events_gui::events
{
enum class TypeEvents : std::uint32_t
{
  unknow         = 0x00,   //<
  base           = 0x01,   //<
  exit_appl      = 0x02,   //<
  load_xml2frame = 0x03,   //<
  mem_block      = 0x04,   //<
  video_buf      = 0x05,   //<
  update_draw    = 0x06,   //<
  size_changed   = 0x07,   //<
  command_code   = 0x08,   //<
  mbutton_down   = 0x09,   //<
  mbutton_up     = 0x0A,   //<
  unknown        = 0xFF    //<
};
}   // namespace libs::events_gui::events
