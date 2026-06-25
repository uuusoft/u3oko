#pragma once
/**
\file       camera-focus-type.hpp
\date       16.05.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::driver
{
enum class Focus : std::uint32_t
{
  auto_generic     = 0x00,   //<
  auto_near        = 0x01,   //<
  auto_macro       = 0x02,   //<
  caf              = 0x03,   //<
  caf_near         = 0x04,   //<
  fixed_infinity   = 0x05,   //<
  fixed_hyperfocal = 0x06,   //<
  fixed_near       = 0x07,   //<
  fixed_macro      = 0x08,   //<
  fixed_cirrent    = 0x09,   //<
  fixed_max        = 0x0A,   //<
  edof             = 0x0B,   //<
  caf_macro        = 0x0C,   //<
  caf_fast         = 0x0D,   //<
  caf_near_fast    = 0x0E,   //<
  caf_macro_fast   = 0x0F,   //<
  unknown          = 0xFF    //<
};

Focus str2focus (const std::string& str);
Focus camera_focus_from_raw_value (std::uint32_t val);
}   // namespace libs::ievents::props::videos::generic::driver
