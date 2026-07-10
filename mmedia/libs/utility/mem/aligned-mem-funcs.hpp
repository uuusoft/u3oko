#pragma once
/**
\file       aligned-mem-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/
namespace libs::utility::mem::consts
{
inline constexpr std::size_t align_ptr2  = ~U3_CAST_SIZE_T_FORCE (0x1);
inline constexpr std::size_t align_ptr8  = ~U3_CAST_SIZE_T_FORCE (0x7);
inline constexpr std::size_t align_ptr16 = ~U3_CAST_SIZE_T_FORCE (0xF);
inline constexpr std::size_t align_ptr32 = ~U3_CAST_SIZE_T_FORCE (0x1F);
inline constexpr std::size_t align_ptr64 = ~U3_CAST_SIZE_T_FORCE (0x3F);
}   // namespace libs::utility::mem::consts

namespace libs::utility::mem
{
template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr bool
check_align (const TType& val, const TType& align)
{
  TType aval = (val / align) * align;
  return aval == val ? true : false;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr bool
check_align2 (TType val)
{
  return U3_CAST_SIZE_T (val) & 0x01 ? false : true;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr void
align2 (TType& val, bool expand = true)
{
  U3_ASSERT (sizeof (TType) <= sizeof (std::size_t));
  if (!check_align2 (val))
  {
    val = ::libs::utility::casts::static_cast_helper< TType > ((U3_CAST_SIZE_T (val) + (expand ? 7 : 0)) & consts::align_ptr2);
    U3_ASSERT (check_align2 (val));
  }
}


template< typename TType >
  requires (std::is_integral_v< TType >)
constexpr TType
get_align2 (const TType& val, bool expand = true)
{
  TType ret = val;
  align2< TType > (ret, expand);
  return ret;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr bool
check_align8 (TType val)
{
  return U3_CAST_SIZE_T (val) & 0x07 ? false : true;
}


inline constexpr bool
check_align8_ptr (const void* buf)
{
  return ::libs::utility::casts::reinterpret_cast_helper< std::size_t > (buf) & 0x07 ? false : true;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr void
align8 (TType& val, bool expand = true)
{
  U3_ASSERT (sizeof (TType) <= sizeof (std::size_t));
  if (!check_align8 (val))
  {
    val = ::libs::utility::casts::static_cast_helper< TType > ((U3_CAST_SIZE_T (val) + (expand ? 7 : 0)) & consts::align_ptr8);
    U3_ASSERT (check_align8 (val));
  }
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr TType
get_align8 (const TType& val, bool expand = true)
{
  TType ret = val;
  align8< TType > (ret, expand);
  return ret;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr bool
check_align16 (TType val)
{
  return U3_CAST_SIZE_T (val) & 0x0F ? false : true;
}


inline constexpr bool
check_align16_ptr (const void* buf)
{
  return ::libs::utility::casts::reinterpret_cast_helper< std::size_t > (buf) & 0x0F ? false : true;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr void
align16 (TType& val, bool expand = true)
{
  U3_ASSERT (sizeof (TType) <= sizeof (std::size_t));
  if (!check_align16 (val))
  {
    val = ::libs::utility::casts::static_cast_helper< TType > ((U3_CAST_SIZE_T (val) + (expand ? 15 : 0)) & consts::align_ptr16);
    U3_ASSERT (check_align16 (val));
  }
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr TType
get_align16 (const TType& val, bool expand = true)
{
  TType ret = val;
  align16< TType > (ret, expand);
  return ret;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr bool
check_align32 (TType val)
{
  return U3_CAST_SIZE_T (val) & 0x1F ? false : true;
}


inline constexpr bool
check_align32_ptr (const void* buf)
{
  return ::libs::utility::casts::reinterpret_cast_helper< std::size_t > (buf) & 0x1F ? false : true;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr void
align32 (TType& val, bool expand = true)
{
  U3_ASSERT (sizeof (TType) <= sizeof (std::size_t));
  if (!check_align32 (val))
  {
    val = ::libs::utility::casts::static_cast_helper< TType > ((U3_CAST_SIZE_T (val) + (expand ? 31 : 0)) & consts::align_ptr32);
    U3_ASSERT (check_align32 (val));
  }
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr TType
get_align32 (const TType& val, bool expand = true)
{
  TType ret = val;
  align32< TType > (ret, expand);
  return ret;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr bool
check_align64 (TType val)
{
  return U3_CAST_SIZE_T (val) & 0x3F ? false : true;
}


inline constexpr bool
check_align64_ptr (const void* buf)
{
  return ::libs::utility::casts::reinterpret_cast_helper< std::size_t > (buf) & 0x3F ? false : true;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr void
align64 (TType& val, bool expand = true)
{
  U3_ASSERT (sizeof (TType) <= sizeof (std::size_t));
  if (!check_align64 (val))
  {
    val = ::libs::utility::casts::static_cast_helper< TType > ((U3_CAST_SIZE_T (val) + (expand ? 63 : 0)) & consts::align_ptr64);
    U3_ASSERT (check_align64 (val));
  }
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr TType
get_align64 (const TType& val, bool expand = true)
{
  TType ret = val;
  align64< TType > (ret, expand);
  return ret;
}


template< typename TType >
  requires (std::is_integral_v< TType >)
inline constexpr TType
align_value (const TType& val, const TType& align, const bool expand = true)
{
  TType ret = val;
  switch (align)
  {
  case 1:
    break;
  case 2:
    align2< TType > (ret, expand);
    break;
  case 8:
    align8< TType > (ret, expand);
    break;
  case 16:
    align16< TType > (ret, expand);
    break;
  case 32:
    align32< TType > (ret, expand);
    break;
  case 64:
    align64< TType > (ret, expand);
    break;
  default:
    U3_ASSERT_SIGNAL ("invalid align" + VTOLOG (align));
    break;
  }
  return ret;
}
}   // namespace libs::utility::mem
