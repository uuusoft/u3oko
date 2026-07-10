#pragma once
/**
\file       uyvy_y16_int.hpp
\author     Erashov Anton erashov2026@proton.me
\date       28.03.2016
\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::uyvy_y16
{
void get_params (
  ::libs::optim::io::MCallInfo&       info,
  const ::libs::optim::io::ProxyBuf** yuy2,
  ::libs::optim::io::ProxyBuf**       y16);
}   // namespace libs::optim::convert::uyvy_y16

#if !defined(UYVY2Y16_PREFIX)
#  define UYVY2Y16_PREFIX(px_per_cycle)                                                      \
    const std::uint32_t                ppc  = px_per_cycle;                                  \
    const std::uint32_t                dppc = ppc * 2;                                       \
    const ::libs::optim::io::ProxyBuf* yuy2 = 0;                                             \
    ::libs::optim::io::ProxyBuf*       y16  = 0;                                             \
                                                                                             \
    get_params (info, &yuy2, &y16);                                                          \
                                                                                             \
    const std::uint8_t* yuy2_buf   = yuy2->ubuf ();                                          \
    std::int16_t*       y16_buf    = y16->buf ();                                            \
    const std::uint32_t cycles     = yuy2->width_ / ppc;                                     \
    const std::uint32_t full_width = cycles * ppc;                                           \
    const std::uint32_t leak_yuy2  = yuy2->stride_ - full_width * sizeof (std::uint8_t) * 2; \
    const std::uint32_t leak_y16   = y16->stride_ - full_width * sizeof (std::uint16_t);     \
    const std::uint32_t width      = yuy2->width_;                                           \
    const std::uint32_t height     = yuy2->height_;                                          \
                                                                                             \
    U3_ASSERT (leak_yuy2 >= 0);                                                              \
    U3_ASSERT (leak_y16 >= 0);

#endif
