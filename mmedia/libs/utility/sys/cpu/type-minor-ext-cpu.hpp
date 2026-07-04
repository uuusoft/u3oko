#pragma once
/**
\file       type-minor-ext-cpu.hpp
\author     Erashov Anton erashov2026@proton.me
\date       02.06.2022
\project    u3_helpers_lib
*/

namespace libs::utility::sys::cpu
{
enum class CpuMinorExts : std::uint32_t
{
  empty   = 0x00,   //<
  fma     = 0x01,   //< FMA
  f16c    = 0x02,   //< F16C
  rdrand  = 0x03,   //< RDRAND
  unknown = 0xFF    //<
};
}   // namespace libs::utility::sys::cpu
