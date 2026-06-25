#pragma once
/**
\file       uyvy_rgb24_int.hpp
\author     Erashov Anton erashov2026@proton.me
\date       28.03.2026
\project    u3_optim_gen_convert
*/
namespace libs::optim::convert::uyvy_rgb24
{
void get_params (
  ::libs::optim::io::MCallInfo&       info,
  const ::libs::optim::io::ProxyBuf** yuy2,
  ::libs::optim::io::ProxyBuf**       rgb24);
}   // namespace libs::optim::convert::uyvy_rgb24

#if !defined(UYVY2RGB24_PREFIX)
#  define UYVY2RGB24_PREFIX                                                                     \
    const ::libs::optim::io::ProxyBuf* yuy2  = 0;                                               \
    ::libs::optim::io::ProxyBuf*       rgb24 = 0;                                               \
                                                                                                \
    get_params (info, &yuy2, &rgb24);                                                           \
                                                                                                \
    const std::uint8_t* yuy2_buf   = yuy2->ubuf ();                                             \
    std::uint8_t*       rgb24_buf  = rgb24->ubuf ();                                            \
    const std::uint32_t leak_yuy2  = yuy2->stride_ - yuy2->width_ * sizeof (std::uint8_t) * 2;  \
    const std::uint32_t leak_rgb24 = rgb24->stride_ - yuy2->width_ * sizeof (std::uint8_t) * 3; \
    const std::size_t   width      = yuy2->width_;                                              \
    const std::size_t   height     = yuy2->height_;

#endif
