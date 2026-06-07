#pragma once
/**
\file       type-ext-gpu.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::sys::cpu
{
enum class TypeExtGpu : std::uint32_t
{
  usual   = 0x00,   //<
  max     = 0x01,   //<
  min     = 0x02,   //<
  unknown = 0xFF    //<
};
}   // namespace libs::helpers::sys::cpu
