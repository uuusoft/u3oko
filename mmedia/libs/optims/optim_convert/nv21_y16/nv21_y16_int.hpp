#pragma once
/**
\file       nv21_y16_int.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_gen_convert
*/
namespace libs::optim::convert::nv21_y16
{
void get_params (::libs::optim::io::MCallInfo& info, const ::libs::optim::io::ProxyBuf** y8, ::libs::optim::io::ProxyBuf** y16);
}   // namespace libs::optim::convert::nv21_y16

#if !defined(NV212Y16_PREFIX)
#  define NV212Y16_PREFIX(px_per_cycle)                                                         \
    const std::uint32_t                ppc = px_per_cycle;                                      \
    const ::libs::optim::io::ProxyBuf* y8  = 0;                                                 \
    ::libs::optim::io::ProxyBuf*       y16 = 0;                                                 \
                                                                                                \
    get_params (info, &y8, &y16);                                                               \
                                                                                                \
    const std::uint8_t* y8_buf     = y8->ubuf ();                                               \
    std::int16_t*       y16_buf    = y16->buf ();                                               \
    const std::uint32_t stride_y8  = y8->stride_;                                               \
    const std::uint32_t stride_y16 = y16->stride_;                                              \
    const std::uint32_t leak_y8    = stride_y8 - y8->width_ * sizeof (std::uint8_t) * 1 * ppc;  \
    const std::uint32_t leak_y16   = stride_y16 - y8->width_ * sizeof (std::uint8_t) * 2 * ppc; \
    const std::uint32_t width      = y8->width_;                                                \
    const std::uint32_t height     = y8->height_;

#endif
