#pragma once
/**
\file       x16_x8_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::x16_x8
{
void get_params (
  ::libs::optim::io::MCallInfo&       info,
  const ::libs::optim::io::ProxyBuf** x16,
  ::libs::optim::io::ProxyBuf**       x8);

}

#if !defined(X16_TO_X8_PREFIX)
#  define X16_TO_X8_PREFIX(px_per_cycle)                                                    \
    const std::uint32_t                ppc  = px_per_cycle;                                 \
    const std::uint32_t                dppc = ppc * 1;                                      \
    const ::libs::optim::io::ProxyBuf* x16  = nullptr;                                      \
    ::libs::optim::io::ProxyBuf*       x8   = nullptr;                                      \
                                                                                            \
    get_params (info, &x16, &x8);                                                           \
                                                                                            \
    const std::int16_t* x16_buf    = x16->buf ();                                           \
    std::uint8_t*       x8_buf     = x8->ubuf ();                                           \
    const std::uint32_t cycles     = x16->width_ / ppc;                                     \
    const std::uint32_t full_width = cycles * ppc;                                          \
    const std::uint32_t leak_x16   = x16->stride_ - full_width * sizeof (std::int16_t) * 1; \
    const std::uint32_t leak_x8    = x8->stride_ - full_width * sizeof (std::uint8_t) * 1;  \
    const std::uint32_t width      = x16->width_;                                           \
    const std::uint32_t height     = x16->height_;                                          \
                                                                                            \
    U3_ASSERT (leak_x16 >= 0);                                                              \
    U3_ASSERT (leak_x8 >= 0);

#endif
