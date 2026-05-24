#pragma once
/**
\file       is_equal_dim.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_dbufs
*/

namespace utils::dbufs::video::helpers
{
inline bool
is_equal_dim (const IVideoBuf& isrc2, const IVideoBuf& isrc1)
{
  const auto width_equal  = isrc2.get_dim_var (Dims::width) == isrc1.get_dim_var (Dims::width);
  const auto height_equal = isrc2.get_dim_var (Dims::height) == isrc1.get_dim_var (Dims::height);
  const auto stride_equal = isrc2.get_dim_var (Dims::stride) == isrc1.get_dim_var (Dims::stride);
  return width_equal && height_equal && stride_equal;
}
}   // namespace utils::dbufs::video::helpers
