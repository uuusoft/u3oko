/**
\file       utility-lib-u3copy-func.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
\brief      Реализация функции копирования блока памяти для всей системы
*/
#include "../utility-lib-includes_int.hpp"
#include "u3copy-func.hpp"

namespace libs::utility::mem
{
void
u3copy (const void* src, void* dst, std::size_t size)
{
  memcpy (dst, src, size);
}
}   // namespace libs::utility::mem
