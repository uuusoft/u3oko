#pragma once
/**
\file       /type-ext-dsp.hpp
\author     Erashov Anton erashov2026@proton.me
\date       02.06.2022
\project    u3_helpers_lib
*/

namespace libs::utility::sys::cpu
{
enum class DspExts : std::uint32_t
{
  usual    = 0x00,   //<
  hexagon4 = 0x01,   //< Hexagon4
  hexagon5 = 0x02,   //< Hexagon5
  hexagon6 = 0x03,   //< Hexagon6
  unknown  = 0xFF    //<
};
}   // namespace libs::utility::sys::cpu
