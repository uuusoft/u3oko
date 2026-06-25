/**
\file       helpers-lib-u3copy-func.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
\brief      Реализация функции копирования блока памяти для всей системы
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "helpers-lib-u3copy-func.hpp"

namespace libs::helpers::mem
{
void
u3copy (const void* src, void* dst, std::size_t size)
{
  memcpy (dst, src, size);
}
}   // namespace libs::helpers::mem
