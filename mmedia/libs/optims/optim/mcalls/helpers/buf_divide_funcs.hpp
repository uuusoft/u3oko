#pragma once
/**
\file       buf_divide_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_optim_lib
*/

namespace libs::optim::mcalls::helpers
{
inline void
split_height (
  const std::uint32_t max_block,
  const std::uint32_t align_block,
  std::uint32_t       height,
  std::uint32_t&      ret)
{
  U3_ASSERT (max_block > 0);
  U3_ASSERT (((height % align_block) == 0));

  const std::uint32_t aligned_height = ::libs::utility::mem::align_value (height, align_block, true);
  const std::uint32_t aligned_blocks = aligned_height / align_block;

  ret = max_block;
  while (ret > 1 && (aligned_blocks % ret))
  {
    --ret;
  }
}
}   // namespace libs::optim::mcalls::helpers
