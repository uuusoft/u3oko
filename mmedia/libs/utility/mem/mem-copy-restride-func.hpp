#pragma once
/**
\file       mem-copy-restride-func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::utility::mem
{
template< typename TTSrc, typename TTDst >
  requires (std::is_pointer_v< TTSrc > && std::is_pointer_v< TTDst >)
void
mem_copy_restride (
  TTSrc               src,
  const std::uint32_t sheight,
  const std::uint32_t sstride,
  TTDst               dst,
  const std::uint32_t dheight,
  const std::uint32_t dstride)
{
  U3_CHECK (src, "null src");
  U3_CHECK (dst, "null dst");
  const auto min_height = std::min< std::uint32_t > (sheight, dheight);
  const auto min_stride = std::min< std::uint32_t > (sstride, dstride);
  for (std::uint32_t indxy = 0; indxy < min_height; ++indxy)
  {
    mem_copy_raw (src, dst, min_stride);
    src = ::libs::utility::mem::move_cptr (src, sstride);
    dst = ::libs::utility::mem::move_ptr (dst, dstride);
  }
}
}   // namespace libs::utility::mem
