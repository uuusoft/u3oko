#pragma once
/**
\file       helpers-lib-move-mem-ptr-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::mem
{
template< typename T, typename U, std::enable_if_t< std::is_pointer_v< T >, bool > = true >
[[nodiscard]] inline constexpr T
move_ptr (T ptr, U off)
{
  auto* ret = casts::reinterpret_cast_helper< std::uint8_t* > (ptr);
  ret += off;
  return casts::reinterpret_cast_helper< T > (ret);
}


template< typename T, typename U, std::enable_if_t< std::is_pointer_v< T >, bool > = true >
[[nodiscard]] inline constexpr T
move_cptr (T ptr, U off)
{
  const auto* ret = casts::reinterpret_cast_helper< const std::uint8_t* > (ptr);
  ret += off;
  return casts::reinterpret_cast_helper< T > (ret);
}


template< typename T, typename U, std::enable_if_t< std::is_pointer_v< T >, bool > = true >
[[nodiscard]] inline constexpr T
move_ptr_back (T ptr, U off)
{
  auto* ret = casts::reinterpret_cast_helper< std::uint8_t* > (ptr);
  ret -= off;
  return casts::reinterpret_cast_helper< T > (ret);
}


template< typename T, typename U, std::enable_if_t< std::is_pointer_v< T >, bool > = true >
[[nodiscard]] inline constexpr T
move_cptr_back (T ptr, U off)
{
  const auto* ret = casts::reinterpret_cast_helper< const std::uint8_t* > (ptr);
  ret -= off;
  return casts::reinterpret_cast_helper< T > (ret);
}
}   // namespace libs::helpers::mem
