#pragma once
/**
\file       enum-mem-vars.hpp
\author     Erashov Anton erashov2026@proton.me
\date       12.08.2018
\project    u3_dbufs
*/

namespace utils::dbufs
{
enum class MemVars : std::uint32_t
{
  size_data   = 0x00,   //<
  offset_data = 0x01,   //<
  size_buf    = 0x02,   //<
  max_bound   = 0x04,   //<
  unknown     = 0xFF    //<
};

inline constexpr std::uint32_t
                 enum_to_raw (const MemVars& _val)
{
  return U3_CAST_UINT32_FORCE (_val);
}
}   // namespace utils::dbufs
