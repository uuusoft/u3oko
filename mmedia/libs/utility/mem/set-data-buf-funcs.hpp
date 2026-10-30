#pragma once
/**
\file       set-data-buf-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/

namespace libs::utility::mem
{
template< typename TType >
auto
set_buf (TType* src, TType val, std::size_t count) -> void
{
  ::libs::utility::checks::throw_ifn (src);
  ::libs::utility::checks::throw_ifn (count > 0);
  std::fill (src, src + count, val);
}
}   // namespace libs::utility::mem
