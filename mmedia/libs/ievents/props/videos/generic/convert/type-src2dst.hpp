#pragma once
/**
\file       type-src2dst.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       29.07.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::convert
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
  return U3_CAST_STATIC< Src2DstEqs > (val);
}
}   // namespace libs::ievents::props::videos::generic::convert
