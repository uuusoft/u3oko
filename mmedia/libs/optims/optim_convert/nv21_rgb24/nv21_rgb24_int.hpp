#pragma once
/**
\file       nv21_rgb24_int.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_optim_gen_convert
*/
namespace libs::optim::convert::nv21_rgb24
{
void get_params (::libs::optim::io::MCallInfo& info, const ::libs::optim::io::ProxyBuf** yuy2, ::libs::optim::io::ProxyBuf** rgb24);
}   // namespace libs::optim::convert::nv21_rgb24

#if !defined(NV212RGB24_PREFIX)
#  define NV212RGB24(px_per_cycle)                                                                             \
    const std::uint32_t                ppc   = px_per_cycle;                                                   \
    const ::libs::optim::io::ProxyBuf* yuy2  = 0;                                                              \
    ::libs::optim::io::ProxyBuf*       rgb24 = 0;                                                              \
                                                                                                               \
    get_params (info, &yuy2, &rgb24);                                                                          \
                                                                                                               \
    const std::uint32_t off_beg_uv = yuy2->width_ * yuy2->height_ * (info.count_threads_ - info.thread_indx_); \
    const std::uint32_t off_uv     = yuy2->width_ * (yuy2->height_ >> 1) * info.thread_indx_;                  \
    const std::uint8_t* y_buf      = yuy2->ubuf ();                                                            \
    const std::uint8_t* uv_buf     = yuy2->ubuf () + off_beg_uv + off_uv;                                      \
    std::uint8_t*       rgb24_buf  = rgb24->ubuf ();                                                           \
    const std::uint32_t leak_yuy2  = yuy2->stride_ - yuy2->width_ * sizeof (std::uint8_t) * 1;                 \
    const std::uint32_t leak_rgb24 = rgb24->stride_ - yuy2->width_ * sizeof (std::uint8_t) * 3;                \
    bool                odd_line   = true;

#endif
