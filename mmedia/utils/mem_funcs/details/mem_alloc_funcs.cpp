/**
\file       mem_alloc_funcs.cpp
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

  const auto vptr   = ::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (*pptr);
  const auto offset = *::libs::helpers::casts::reinterpret_cast_helper< std::uint8_t* > (vptr - 1);

  if ((0 == offset) || (offset > consts::count_add_blocks * consts::size_align))
  {
    U3_XLOG_ERROR ("failed get block memory for free" + VTOLOG (offset) + VTOLOG (consts::count_add_blocks * consts::size_align));
    free (*pptr);
  }
  else
  {
    U3_ASSERT_NT (vptr > offset, VTOLOG (vptr) + VTOLOG (offset));
    auto* real_ptr = ::libs::helpers::casts::reinterpret_cast_helper< void* > (vptr - offset);
    free (real_ptr);
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

  const std::size_t real_size   = size + consts::count_add_blocks * consts::size_align;
  std::uint8_t      offset      = 0;
  void*             raw_ptr     = malloc (real_size);
  const auto        int_raw_ptr = ::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (raw_ptr);

  if (nullptr == raw_ptr)
  {
    U3_ASSERT_SIGNAL_NT ("failed alloc memory" + VTOLOG (real_size) + VTOLOG (size));
    return;
  }

  *pptr  = ::libs::helpers::casts::reinterpret_cast_helper< void* > ((int_raw_ptr + 2 * consts::size_align) & ::libs::helpers::mem::consts::align_ptr64);
  offset = U3_CAST_UINT8 (::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (*pptr) - int_raw_ptr);

  if (offset < 1)
  {
    U3_ASSERT_SIGNAL_NT ("FAILED OFFSET ALLOCATED MEMORY" + VTOLOG (offset) + VTOLOG (real_size));
    free (raw_ptr);
    raw_ptr = nullptr;
    *pptr   = nullptr;
  }
  else
  {
    *::libs::helpers::casts::reinterpret_cast_helper< std::uint8_t* > ((::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (*pptr)) - 1) = offset;
    *::libs::helpers::casts::reinterpret_cast_helper< std::size_t* > (raw_ptr)                                                                       = size;
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

  void*       new_ptr   = nullptr;
  std::size_t size_copy = 0;

  aalloc (&new_ptr, size);

  if (!new_ptr)
  {
    U3_ASSERT_SIGNAL_NT ("FAILED AALLOC FUNCT" + VTOLOG (size));
    afree (pptr);
    return;
  }

  const auto vptr     = ::libs::helpers::casts::reinterpret_cast_helper< std::size_t > (*pptr);
  auto       offset   = *::libs::helpers::casts::reinterpret_cast_helper< std::uint8_t* > (vptr - 1);
  auto*      real_ptr = ::libs::helpers::casts::reinterpret_cast_helper< void* > (vptr - offset);
  const auto old_size = *::libs::helpers::casts::reinterpret_cast_helper< std::size_t* > (real_ptr);

  size_copy = old_size - offset;
  size_copy = size_copy > size ? size : size_copy;

  memcpy (new_ptr, *pptr, size_copy);

  afree (pptr);
  *pptr = new_ptr;
}
}   // namespace utils::mem_funcs::details
