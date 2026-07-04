#pragma once
/**
\file       enum-src2dsteqs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       29.07.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::convert
{
enum class Src2DstEqs : std::uint32_t
{
  src_int_dst  = 0x00,   //<
  src_int_dst2 = 0x01,   //<
  equal_dst    = 0x02,   //<
  additive     = 0x03,   //<
  unknown      = 0xFF    //<
};

inline constexpr Src2DstEqs
src2dst_from_raw_value (std::uint32_t val)
{
  return ::libs::utility::casts::static_cast_helper< Src2DstEqs > (val);
}
}   // namespace libs::events_base::props::videos::generic::convert
