#pragma once
/**
\file       i420_rgb24_int.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       30.07.2018
\project    u3_optim_gen_convert
*/

namespace libs::optim::convert::i420_rgb24
{
void get_params (
  ::libs::optim::io::MCallInfo&       info,
  const ::libs::optim::io::ProxyBuf** y,
  ::libs::optim::io::ProxyBuf**       rgb24);
}

#if !defined(I4202RGB24_PREFIX)
#  define I4202RGB24_PREFIX                                                                                                          \
    const ::libs::optim::io::ProxyBuf* y     = nullptr;                                                                              \
    ::libs::optim::io::ProxyBuf*       rgb24 = nullptr;                                                                              \
                                                                                                                                     \
    get_params (info, &y, &rgb24);                                                                                                   \
                                                                                                                                     \
    const std::uint32_t                off_beg_u          = y->stride_ * y->height_ * (info.count_threads_ - info.indx_thread_);     \
    const std::uint32_t                off_beg_v          = off_beg_u + (y->stride_ * y->height_ * info.count_threads_ >> 1);        \
    const std::uint32_t                off_uv_thread_bufs = y->stride_ * y->height_ * info.indx_thread_ >> 1;                        \
    const ::libs::optim::io::ProxyBuf  temp_u (y->ubuf () + off_beg_u + off_uv_thread_bufs, y->stride_, y->width_, y->height_ >> 1); \
    const ::libs::optim::io::ProxyBuf  temp_v (y->ubuf () + off_beg_v + off_uv_thread_bufs, y->stride_, y->width_, y->height_ >> 1); \
    const ::libs::optim::io::ProxyBuf* u = &temp_u;                                                                                  \
    const ::libs::optim::io::ProxyBuf* v = &temp_v;                                                                                  \
                                                                                                                                     \
    const std::uint8_t* y_buf      = y->ubuf ();                                                                                     \
    const std::uint8_t* u_buf      = u->ubuf ();                                                                                     \
    const std::uint8_t* v_buf      = v->ubuf ();                                                                                     \
    std::uint8_t*       rgb24_buf  = rgb24->ubuf ();                                                                                 \
    const std::uint32_t width      = y->width_;                                                                                      \
    const std::uint32_t height     = y->height_;                                                                                     \
    const std::uint32_t leak_y     = y->stride_ - width * sizeof (std::uint8_t) * 1;                                                 \
    const std::uint32_t leak_uv    = y->stride_ - ((width * sizeof (std::uint8_t) * 1) >> 1);                                        \
    const std::uint32_t leak_rgb24 = rgb24->stride_ - width * sizeof (std::uint8_t) * 3;

#endif
