#pragma once
/**
\file       buf_dimension_equal-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_dbufs
*/

namespace utils::dbufs::video::helpers
{
inline bool
buf_dimension_equal (const IVideoBuf& lplh, const IVideoBuf& rplh)
{
  return lplh.get_dim_var (Dims::width) == rplh.get_dim_var (Dims::width) &&
         lplh.get_dim_var (Dims::height) == rplh.get_dim_var (Dims::height) &&
         lplh.get_dim_var (Dims::stride) == rplh.get_dim_var (Dims::stride);
}
}   // namespace utils::dbufs::video::helpers
