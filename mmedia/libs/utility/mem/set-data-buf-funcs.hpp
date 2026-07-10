#pragma once
/**
\file       set-data-buf-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::mem
{
template< typename TType >
auto
set_buf (TType* src, TType val, std::size_t count) -> void
{
  U3_ASSERT (src);
  U3_ASSERT (count > 0);
  std::fill (src, src + count, val);
}
}   // namespace libs::utility::mem
