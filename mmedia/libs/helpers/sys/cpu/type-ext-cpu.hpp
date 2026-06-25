#pragma once
/**
\file       type-ext-cpu.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::sys::cpu
{
enum class CpuExts : std::uint32_t
{
  usual   = 0x00,   //< Не определено, для общности
  max     = 0x01,   //< Максимально поддерживаемое расширение
  min     = 0x02,   //< Минмимально поддерживаемое расширение
  alu     = 0x03,   //< Признак ALU (часто по умолчанию)
  mmx     = 0x04,   //< Признак MMX (deprecate)
  sse1    = 0x05,   //< Признак SSE1 (deprecate)
  sse2    = 0x06,   //< Признак SSE2
  sse3    = 0x07,   //< Признак SSE3
  sse4_1  = 0x08,   //< Признак SSE4_1
  sse4_2  = 0x09,   //< Признак SSE4_2
  avx1    = 0x0A,   //< Признак AVX1
  avx2    = 0x0B,   //< Признак AVX2
  neon    = 0x0C,   //< Признак NEON
  unknown = 0xFF    //< Не определенно для общности
};
}   // namespace libs::helpers::sys::cpu
