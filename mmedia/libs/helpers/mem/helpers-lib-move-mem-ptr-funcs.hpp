#pragma once
/**
\file       helpers-lib-move-mem-ptr-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::mem
{
template< typename T >
T
move_ptr (T ptr, std::size_t off)
{
  std::uint8_t* ret = U3_CAST_REINTERPRET< std::uint8_t* > (ptr);
  ret += off;
  return U3_CAST_REINTERPRET< T > (ret);
}


template< typename T >
T
move_cptr (T ptr, std::size_t off)
{
  const std::uint8_t* ret = U3_CAST_REINTERPRET< const std::uint8_t* > (ptr);
  ret += off;
  return U3_CAST_REINTERPRET< T > (ret);
}


template< typename T >
T
move_ptr_back (T ptr, std::size_t off)
{
  std::uint8_t* ret = U3_CAST_REINTERPRET< std::uint8_t* > (ptr);
  ret -= off;
  return U3_CAST_REINTERPRET< T > (ret);
}


template< typename T >
T
move_cptr_back (T ptr, std::size_t off)
{
  const std::uint8_t* ret = U3_CAST_REINTERPRET< const std::uint8_t* > (ptr);
  ret -= off;
  return U3_CAST_REINTERPRET< T > (ret);
}
}   // namespace libs::helpers::mem


#if !defined(U3_FAST_MOVE_PTR)
#  define U3_FAST_MOVE_PTR(ptr, off) ptr = U3_CAST_REINTERPRET< decltype (ptr) > (U3_CAST_REINTERPRET< std::uint8_t* > (ptr) + U3_CAST_SIZE_T (off));
#endif

#if !defined(U3_FAST_MOVE_CPTR)
#  define U3_FAST_MOVE_CPTR(ptr, off) ptr = U3_CAST_REINTERPRET< decltype (ptr) > (U3_CAST_REINTERPRET< const std::uint8_t* > (ptr) + U3_CAST_SIZE_T (off));
#endif

#if !defined(U3_FAST_MOVE_PTR_BACK)
#  define U3_FAST_MOVE_PTR_BACK(ptr, off) ptr = U3_CAST_REINTERPRET< decltype (ptr) > (U3_CAST_REINTERPRET< std::uint8_t* > (ptr) - U3_CAST_SIZE_T (off));
#endif

#if !defined(U3_FAST_MOVE_CPTR_BACK)
#  define U3_FAST_MOVE_CPTR_BACK(ptr, off) ptr = U3_CAST_REINTERPRET< decltype (ptr) > (U3_CAST_REINTERPRET< const std::uint8_t* > (ptr) - U3_CAST_SIZE_T (off));
#endif
