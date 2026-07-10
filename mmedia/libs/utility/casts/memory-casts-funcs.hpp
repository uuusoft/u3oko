#pragma once
/**
\file       memory-casts-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2026
\project    u3_helpers_lib
\brief      Функции преобразований, чтобы контролировать применение reinterpret_cast etc
*/

namespace libs::utility::casts
{
template< typename To, typename From >
inline constexpr decltype (auto)
static_cast_helper (From&& val) noexcept (noexcept (static_cast< To > (std::forward< From > (val))))
{
  return static_cast< To > (std::forward< From > (val));
}

template< typename T >
inline constexpr std::remove_const_t< T >*
const_cast_helper (T* val) noexcept
{
  return const_cast< std::remove_const_t< T >* > (val);
}

template< typename T >
inline constexpr std::remove_const_t< T >&
const_cast_helper (T& val) noexcept
{
  return const_cast< std::remove_const_t< T >& > (val);
}

template< typename T, typename U >
inline constexpr T
reinterpret_cast_helper (U* val)
{
  // NOLINTNEXTLINE
  return reinterpret_cast< T > (val);
}

template< typename T, typename U >
inline constexpr T
reinterpret_cast_helper (U val)
{
  // NOLINTNEXTLINE
  return reinterpret_cast< T > (val);
}
}   // namespace libs::utility::casts
