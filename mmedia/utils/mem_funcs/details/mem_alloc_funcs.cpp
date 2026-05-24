/**
\file       mem_funcs.cpp
\brief      функции работы с памятью
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_mem_funcs
\brief      Файл реализации низкоуровных функций для работы с памятью
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../mem-funcs-includes_int.hpp"

namespace utils::mem_funcs::details::consts
{
constexpr std::uint32_t count_add_blocks = 3;    //< Расширение памяти на утроенный размер указателя платформы, чтобы гарантировать увеличение на размер указателя (реальный размер) + 1 байт на смещение настоящего указателя
constexpr std::uint32_t size_align       = 64;   //< Требуемое выравнивание, должно быть больше или равно размеру указателя платформы
}   // namespace utils::mem_funcs::details::consts


namespace utils::mem_funcs::details
{
void
afree (void** pptr)
{
  U3_ASSERT_NT (pptr, PTR_TOLOG (pptr));
  if (nullptr == pptr || nullptr == *pptr)
  {
    return;
  }

  const std::size_t _int_ptr = U3_CAST_REINTERPRET< std::size_t > (*pptr);
  const std::size_t offset   = *U3_CAST_REINTERPRET< std::uint8_t* > (_int_ptr - 1);

  if ((0 == offset) || (offset > consts::count_add_blocks * consts::size_align))
  {
    U3_XLOG_ERROR ("FAILED GET BLOCK MEMORY FOR CORRECT FREE " + VTOLOG (offset) + VTOLOG (consts::count_add_blocks * consts::size_align));
    free (*pptr);
  }
  else
  {
    U3_ASSERT_NT (_int_ptr > offset, VTOLOG (_int_ptr) + VTOLOG (offset));
    void* _real_ptr = U3_CAST_REINTERPRET< void* > (_int_ptr - offset);
    free (_real_ptr);
  }

  *pptr = nullptr;
}


void
aalloc (void** pptr, const std::size_t size)
{
  U3_ASSERT_NT (pptr, PTR_TOLOG (pptr));
  U3_ASSERT_NT (size > 0, VTOLOG (size));

  if (0 == size || nullptr == pptr)
  {
    return;
  }

  U3_ASSERT_NT (nullptr == *pptr, PTR_TOLOG (*pptr));
  *pptr = nullptr;

  const std::size_t _real_size   = size + consts::count_add_blocks * consts::size_align;
  std::uint8_t      offset       = 0;
  void*             _raw_ptr     = malloc (_real_size);
  const std::size_t _int_raw_ptr = U3_CAST_REINTERPRET< std::size_t > (_raw_ptr);

  if (nullptr == _raw_ptr)
  {
    U3_ASSERT_SIGNAL_NT ("FAILED ALLOC MEMORY" + VTOLOG (_real_size) + VTOLOG (size));
    return;
  }

  *pptr  = U3_CAST_REINTERPRET< void* > ((_int_raw_ptr + 2 * consts::size_align) & ::libs::helpers::mem::consts::align_ptr64);
  offset = U3_CAST_UINT8 (U3_CAST_REINTERPRET< std::size_t > (*pptr) - _int_raw_ptr);

  if (offset < 1)
  {
    U3_ASSERT_SIGNAL_NT ("FAILED OFFSET ALLOCATED MEMORY" + VTOLOG (offset) + VTOLOG (_real_size));
    free (_raw_ptr);
    _raw_ptr = nullptr;
    *pptr    = nullptr;
  }
  else
  {
    *U3_CAST_REINTERPRET< std::uint8_t* > ((U3_CAST_REINTERPRET< std::size_t > (*pptr)) - 1) = offset;
    *U3_CAST_REINTERPRET< std::size_t* > (_raw_ptr)                                          = size;
  }
}


void
arealloc (void** pptr, const std::size_t size)
{
  U3_ASSERT_NT (pptr, PTR_TOLOG (pptr));
  U3_ASSERT_NT (size > 0, VTOLOG (size));

  if (nullptr == pptr)
  {
    return;
  }

  if (nullptr == *pptr)
  {
    aalloc (pptr, size);
    return;
  }

  if (size <= 0)
  {
    afree (pptr);
    return;
  }

  void*       _new_ptr  = nullptr;
  std::size_t size_copy = 0;

  aalloc (&_new_ptr, size);

  if (!_new_ptr)
  {
    U3_ASSERT_SIGNAL_NT ("FAILED AALLOC FUNCT" + VTOLOG (size));
    afree (pptr);
    return;
  }

  const std::size_t _int_ptr  = U3_CAST_REINTERPRET< std::size_t > (*pptr);
  std::uint8_t      offset    = *U3_CAST_REINTERPRET< std::uint8_t* > (_int_ptr - 1);
  void*             _real_ptr = U3_CAST_REINTERPRET< void* > (_int_ptr - offset);
  const std::size_t _old_size = *U3_CAST_REINTERPRET< std::size_t* > (_real_ptr);

  size_copy = _old_size - offset;
  size_copy = size_copy > size ? size : size_copy;

  memcpy (_new_ptr, *pptr, size_copy);

  afree (pptr);
  *pptr = _new_ptr;
}
}   // namespace utils::mem_funcs::details
