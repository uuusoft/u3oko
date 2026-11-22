/**
\file       alloc-funcs.cpp
\brief      функции работы с памятью
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\brief      Файл реализации низкоуровных функций для работы с памятью
*/
#include "../mems-includes_int.hpp"

namespace utils::mems::details::consts
{
constexpr std::uint32_t count_add_blocks = 3;    //< Расширение памяти на утроенный размер указателя платформы, чтобы гарантировать увеличение на размер указателя (реальный размер) + 1 байт на смещение настоящего указателя
constexpr std::uint32_t size_align       = 64;   //< Требуемое выравнивание, должно быть больше или равно размеру указателя платформы
}   // namespace utils::mems::details::consts

namespace utils::mems::details
{
void
u3free (void** pptr)
{
  ::libs::utility::checks::assert_soft (pptr);
  if (nullptr == pptr || nullptr == *pptr)
  {
    return;
  }

  const auto vptr   = ::libs::utility::casts::reinterpret_cast_helper< std::size_t > (*pptr);
  const auto offset = *::libs::utility::casts::reinterpret_cast_helper< std::uint8_t* > (vptr - 1);

  if ((0 == offset) || (offset > consts::count_add_blocks * consts::size_align))
  {
    U3_XLOG_ERROR ("FAILED GET MEMORY BLOCK FOR FREE:{} {}", offset, consts::count_add_blocks * consts::size_align);
    free (*pptr);
  }
  else
  {
    ::libs::utility::checks::assert_soft (vptr > offset, U3_FORMAT ("{} {}", vptr, offset));
    auto* real_ptr = ::libs::utility::casts::reinterpret_cast_helper< void* > (vptr - offset);
    free (real_ptr);
  }

  *pptr = nullptr;
}


void
u3alloc (void** pptr, const std::size_t size)
{
  ::libs::utility::checks::assert_soft (pptr && size > 0, U3_FORMAT ("{} {}", U3_CAST_PTR2INT_FORCE (pptr), size));
  if (0 == size || nullptr == pptr)
  {
    return;
  }

  ::libs::utility::checks::assert_soft (nullptr == *pptr);
  *pptr = nullptr;

  const std::size_t real_size   = size + static_cast< std::size_t > (consts::count_add_blocks * consts::size_align);
  std::uint8_t      offset      = 0;
  void*             raw_ptr     = malloc (real_size);
  const auto        int_raw_ptr = ::libs::utility::casts::reinterpret_cast_helper< std::size_t > (raw_ptr);

  if (nullptr == raw_ptr)
  {
    ::libs::utility::checks::mark (U3_FORMAT ("failed alloc memory {} {}", real_size, size));
    return;
  }

  *pptr  = ::libs::utility::casts::reinterpret_cast_helper< void* > ((int_raw_ptr + static_cast< unsigned long > (2 * consts::size_align)) & ::libs::utility::mem::consts::align_ptr64);
  offset = U3_CAST_UINT8 (::libs::utility::casts::reinterpret_cast_helper< std::size_t > (*pptr) - int_raw_ptr);

  if (offset < 1)
  {
    ::libs::utility::checks::mark (U3_FORMAT ("FAILED OFFSET ALLOCATED MEMORY {} {}", offset, real_size));
    free (raw_ptr);
    raw_ptr = nullptr;
    *pptr   = nullptr;
  }
  else
  {
    // EAI-REFACT
    const auto step1 = ::libs::utility::casts::reinterpret_cast_helper< std::size_t > (*pptr);

    *::libs::utility::casts::reinterpret_cast_helper< std::uint8_t* > ((step1) -1) = offset;
    *::libs::utility::casts::reinterpret_cast_helper< std::size_t* > (raw_ptr)     = size;
  }
}


void
u3realloc (void** pptr, const std::size_t size)
{
  ::libs::utility::checks::assert_soft (pptr, U3_FORMAT ("{}", U3_CAST_PTR2INT_FORCE (pptr)));
  ::libs::utility::checks::assert_soft (size > 0, U3_FORMAT ("{}", size));
  if (nullptr == pptr)
  {
    return;
  }
  if (nullptr == *pptr)
  {
    u3alloc (pptr, size);
    return;
  }
  if (size <= 0)
  {
    u3free (pptr);
    return;
  }

  void*       new_ptr   = nullptr;
  std::size_t size_copy = 0;

  u3alloc (&new_ptr, size);

  if (!new_ptr)
  {
    ::libs::utility::checks::mark (U3_FORMAT ("FAILED u3alloc {}", size));
    u3free (pptr);
    return;
  }

  const auto vptr     = ::libs::utility::casts::reinterpret_cast_helper< std::size_t > (*pptr);
  auto       offset   = *::libs::utility::casts::reinterpret_cast_helper< std::uint8_t* > (vptr - 1);
  auto*      real_ptr = ::libs::utility::casts::reinterpret_cast_helper< void* > (vptr - offset);
  const auto old_size = *::libs::utility::casts::reinterpret_cast_helper< std::size_t* > (real_ptr);

  size_copy = old_size - offset;
  size_copy = size_copy > size ? size : size_copy;

  memcpy (new_ptr, *pptr, size_copy);

  u3free (pptr);
  *pptr = new_ptr;
}
}   // namespace utils::mems::details
