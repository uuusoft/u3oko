/**
\file       helpers-lib-check-buf-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "helpers-lib-check-buf-funcs.hpp"

namespace libs::helpers::mem
{
bool
check_buf (void* sbuf, const std::uint32_t size)
{
  std::uint8_t*         buf     = ::libs::helpers::casts::reinterpret_cast_helper< std::uint8_t* > (sbuf);
  volatile bool         read_op = false;
  std::size_t           cindx   = 0;
  volatile std::uint8_t val     = 0;

  for (cindx = 0; cindx < size; ++cindx)
  {
    val     = buf[cindx];
    read_op = !read_op;

    buf[cindx] = val;
    read_op    = !read_op;
  }
  return true;
}


bool
check_read_buf (const void* sbuf, const std::uint32_t size)
{
  return check_buf (const_cast< void* > (sbuf), size);
}
}   // namespace libs::helpers::mem
