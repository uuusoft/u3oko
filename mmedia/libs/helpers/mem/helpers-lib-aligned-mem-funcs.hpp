#pragma once
/**
\file       helpers-lib-aligned-mem-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/
namespace libs::helpers::mem::consts
{
constexpr std::size_t align_ptr2  = ~U3_CAST_SIZE_T_FORCE (0x1);
constexpr std::size_t align_ptr8  = ~U3_CAST_SIZE_T_FORCE (0x7);
constexpr std::size_t align_ptr16 = ~U3_CAST_SIZE_T_FORCE (0xF);
constexpr std::size_t align_ptr32 = ~U3_CAST_SIZE_T_FORCE (0x1F);
constexpr std::size_t align_ptr64 = ~U3_CAST_SIZE_T_FORCE (0x3F);
}   // namespace libs::helpers::mem::consts


namespace libs::helpers::mem
{
template< typename TTVal >
bool
check_align (const TTVal& val, const TTVal& align)
{
  TTVal aval = (val / align) * align;
  return aval == val ? true : false;
}


template< typename TTVal >
bool
check_align2 (TTVal val)
{
  return U3_CAST_SIZE_T (val) & 0x01 ? false : true;
}


template< typename TVal >
void
align2 (TVal& val, bool expand = true)
{
  U3_ASSERT (sizeof (TVal) <= sizeof (std::size_t));
  if (!check_align2 (val))
  {
    val = ::libs::helpers::casts::static_cast_helper< TVal > ((U3_CAST_SIZE_T (val) + (expand ? 7 : 0)) & consts::align_ptr2);
    U3_ASSERT (check_align2 (val));
  }
}


template< typename TTVal >
TTVal
get_align2 (const TTVal& val, bool expand = true)
{
  TTVal ret = val;
  align2< TTVal > (ret, expand);
  return ret;
}


template< typename TTVal >
bool
check_align8 (TTVal val)
{
  return U3_CAST_SIZE_T (val) & 0x07 ? false : true;
}


inline bool
check_align8_ptr (const void* buf)
{
  return ::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (buf) & 0x07 ? false : true;
}


template< typename TVal >
void
align8 (TVal& val, bool expand = true)
{
  U3_ASSERT (sizeof (TVal) <= sizeof (std::size_t));
  if (!check_align8 (val))
  {
    val = ::libs::helpers::casts::static_cast_helper< TVal > ((U3_CAST_SIZE_T (val) + (expand ? 7 : 0)) & consts::align_ptr8);
    U3_ASSERT (check_align8 (val));
  }
}


template< typename TTVal >
TTVal
get_align8 (const TTVal& val, bool expand = true)
{
  TTVal ret = val;
  align8< TTVal > (ret, expand);
  return ret;
}


template< typename TTVal >
bool
check_align16 (TTVal val)
{
  return U3_CAST_SIZE_T (val) & 0x0F ? false : true;
}


inline bool
check_align16_ptr (const void* buf)
{
  return ::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (buf) & 0x0F ? false : true;
}


template< typename TTVal >
void
align16 (TTVal& val, bool expand = true)
{
  U3_ASSERT (sizeof (TTVal) <= sizeof (std::size_t));
  if (!check_align16 (val))
  {
    val = ::libs::helpers::casts::static_cast_helper< TTVal > ((U3_CAST_SIZE_T (val) + (expand ? 15 : 0)) & consts::align_ptr16);
    U3_ASSERT (check_align16 (val));
  }
}


template< typename TTVal >
TTVal
get_align16 (const TTVal& val, bool expand = true)
{
  TTVal ret = val;
  align16< TTVal > (ret, expand);
  return ret;
}


template< typename TTVal >
bool
check_align32 (TTVal val)
{
  return U3_CAST_SIZE_T (val) & 0x1F ? false : true;
}


inline bool
check_align32_ptr (const void* buf)
{
  return ::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (buf) & 0x1F ? false : true;
}


template< typename TTVal >
void
align32 (TTVal& val, bool expand = true)
{
  U3_ASSERT (sizeof (TTVal) <= sizeof (std::size_t));
  if (!check_align32 (val))
  {
    val = ::libs::helpers::casts::static_cast_helper< TTVal > ((U3_CAST_SIZE_T (val) + (expand ? 31 : 0)) & consts::align_ptr32);
    U3_ASSERT (check_align32 (val));
  }
}


template< typename TTVal >
TTVal
get_align32 (const TTVal& val, bool expand = true)
{
  TTVal ret = val;
  align32< TTVal > (ret, expand);
  return ret;
}


template< typename TTVal >
bool
check_align64 (TTVal val)
{
  return U3_CAST_SIZE_T (val) & 0x3F ? false : true;
}


inline bool
check_align64_ptr (const void* buf)
{
  return ::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (buf) & 0x3F ? false : true;
}


template< typename TTVal >
void
align64 (TTVal& val, bool expand = true)
{
  U3_ASSERT (sizeof (TTVal) <= sizeof (std::size_t));
  if (!check_align64 (val))
  {
    val = ::libs::helpers::casts::static_cast_helper< TTVal > ((U3_CAST_SIZE_T (val) + (expand ? 63 : 0)) & consts::align_ptr64);
    U3_ASSERT (check_align64 (val));
  }
}


template< typename TTVal >
TTVal
get_align64 (const TTVal& val, bool expand = true)
{
  TTVal ret = val;
  align64< TTVal > (ret, expand);
  return ret;
}


template< typename TTVal >
TTVal
get_align (const TTVal& val, const TTVal& align, const bool expand = true)
{
  TTVal ret = val;
  switch (align)
  {
  case 1:
    break;
  case 2:
    align2< TTVal > (ret, expand);
    break;
  case 8:
    align8< TTVal > (ret, expand);
    break;
  case 16:
    align16< TTVal > (ret, expand);
    break;
  case 32:
    align32< TTVal > (ret, expand);
    break;
  case 64:
    align64< TTVal > (ret, expand);
    break;
  default:
    U3_ASSERT_SIGNAL ("invalid align" + VTOLOG (align));
    break;
  }
  return ret;
}
}   // namespace libs::helpers::mem
