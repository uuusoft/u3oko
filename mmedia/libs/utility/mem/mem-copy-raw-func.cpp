/**
\file       mem-copy-raw-func.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\brief      Реализация функции копирования блока памяти для всей системы
*/
#include "../utility-lib-includes_int.hpp"
#include "mem-copy-raw-func.hpp"

namespace libs::utility::mem
{
void
mem_copy_raw (const void* src, void* dst, std::size_t size)
{
  ::libs::utility::checks::throw_ifn (src);
  ::libs::utility::checks::throw_ifn (dst);
  if (size)
  {
    memcpy (dst, src, size);
  }
}
}   // namespace libs::utility::mem
