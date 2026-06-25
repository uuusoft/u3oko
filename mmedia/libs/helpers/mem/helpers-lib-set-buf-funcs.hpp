#pragma once
/**
\file       helpers-lib-set-buf-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::mem
{
template< typename TTSource >
auto
set_buf (TTSource* src, TTSource val, std::size_t count) -> void
{
  U3_ASSERT (src);
  U3_ASSERT (count > 0);
  std::fill (src, src + count, val);
}
}   // namespace libs::helpers::mem
