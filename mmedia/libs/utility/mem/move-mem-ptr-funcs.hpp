#pragma once
/**
\file       move-mem-ptr-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::mem
{
template< typename T, typename U >
  requires (std::is_pointer_v< T > && std::is_unsigned_v< U >)
[[nodiscard]] inline constexpr T
move_ptr (T ptr, U off)
{
  auto* ret = casts::reinterpret_cast_helper< std::uint8_t* > (ptr);
  U3_ASSERT (ret);
  ret += off;
  return casts::reinterpret_cast_helper< T > (ret);
}


template< typename T, typename U >
  requires (std::is_pointer_v< T > && std::is_unsigned_v< U >)
[[nodiscard]] inline constexpr T
move_cptr (T ptr, U off)
{
  const auto* ret = casts::reinterpret_cast_helper< const std::uint8_t* > (ptr);
  U3_ASSERT (ret);
  ret += off;
  return casts::reinterpret_cast_helper< T > (ret);
}


template< typename T, typename U >
  requires (std::is_pointer_v< T > && std::is_unsigned_v< U >)
[[nodiscard]] inline constexpr T
move_ptr_back (T ptr, U off)
{
  auto* ret = casts::reinterpret_cast_helper< std::uint8_t* > (ptr);
  U3_ASSERT (ret && casts::reinterpret_cast_helper< std::uint64_t > (ret) >= off);
  ret -= off;
  return casts::reinterpret_cast_helper< T > (ret);
}


template< typename T, typename U >
  requires (std::is_pointer_v< T > && std::is_unsigned_v< U >)
[[nodiscard]] inline constexpr T
move_cptr_back (T ptr, U off)
{
  const auto* ret = casts::reinterpret_cast_helper< const std::uint8_t* > (ptr);
  U3_ASSERT (ret && casts::reinterpret_cast_helper< std::uint64_t > (ret) >= off);
  ret -= off;
  return casts::reinterpret_cast_helper< T > (ret);
}
}   // namespace libs::utility::mem
