#pragma once
/**
\file       x8_x16_int.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::x8_x16
{
void get_params (
  ::libs::optim::io::MCallInfo&       info,
  const ::libs::optim::io::ProxyBuf** x16,
  ::libs::optim::io::ProxyBuf**       x8);
}


#if !defined(X8_TO_X16_PREFIX)
#  define X8_TO_X16_PREFIX(px_per_cycle)                                                    \
    const std::uint32_t                ppc  = px_per_cycle;                                 \
    const std::uint32_t                dppc = ppc * 1;                                      \
    const ::libs::optim::io::ProxyBuf* x8   = nullptr;                                      \
    ::libs::optim::io::ProxyBuf*       x16  = nullptr;                                      \
                                                                                            \
    get_params (info, &x8, &x16);                                                           \
                                                                                            \
    const std::uint8_t* x8_buf     = x8->ubuf ();                                           \
    std::int16_t*       x16_buf    = x16->buf ();                                           \
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
