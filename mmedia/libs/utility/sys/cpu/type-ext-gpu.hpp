#pragma once
/**
\file       type-ext-gpu.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::sys::cpu
{
enum class TypeExtGpu : std::uint32_t
{
  usual   = 0x00,   //<
  max     = 0x01,   //<
  min     = 0x02,   //<
  unknown = 0xFF    //<
};
}   // namespace libs::utility::sys::cpu
