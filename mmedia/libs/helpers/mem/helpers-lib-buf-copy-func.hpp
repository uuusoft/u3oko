#pragma once
/**
\file       helpers-lib-buf-copy-func.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_helpers_lib
*/

namespace libs::helpers::mem
{
template< typename TTSrcElement, typename TTDstElement >
void
buf_copy (
  TTSrcElement       src,
  const std::int32_t sheight,
  const std::int32_t sstride,
  TTDstElement       dst,
  const std::int32_t dheight,
  const std::int32_t dstride)
{
  U3_CHECK (src, "null src for buf copy");
  U3_CHECK (dst, "null dst for buf copy");

  const std::int32_t min_height = std::min< std::int32_t > (sheight, dheight);
  const std::int32_t min_stride = std::min< std::int32_t > (sstride, dstride);

  for (std::int32_t indxy = 0; indxy < min_height; ++indxy)
  {
    u3copy (src, dst, U3_CAST_SIZE_T (min_stride));
    src = ::libs::helpers::mem::move_cptr (src, sstride);
    dst = ::libs::helpers::mem::move_ptr (dst, dstride);
  }
}
}   // namespace libs::helpers::mem
