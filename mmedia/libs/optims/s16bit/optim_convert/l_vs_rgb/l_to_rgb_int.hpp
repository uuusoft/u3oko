#pragma once
/**
\file       l_to_rgb_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_convert
*/

#if !defined(L2RGB_PREFIX)
#  define L2RGB_PREFIX(size)                                                                     \
                                                                                                 \
    U3_CHECK (check_l2rgb (info), "check l2rgb");                                                \
                                                                                                 \
    const std::uint32_t ppc    = size;                                                           \
    const std::uint32_t width  = info.dsts_[0].width_;                                           \
    const std::uint32_t height = info.dsts_[0].height_;                                          \
    const std::int16_t* l      = info.srcs_[0].buf ();                                           \
    std::uint8_t*       rgb24  = info.dsts_[0].ubuf ();                                          \
    std::uint32_t       pcx    = width / 4;                                                      \
                                                                                                 \
    pcx = (pcx * 4 < width) ? pcx + 1 : pcx;                                                     \
                                                                                                 \
    const std::uint32_t leak_l       = info.srcs_[0].stride_ - pcx * 4 * sizeof (std::uint16_t); \
    const std::uint32_t stride_rgb24 = pcx * 4 * sizeof (std::uint8_t) * 3;                      \
    std::int32_t*       out_stride   = info.params_.pints_[0];                                   \
                                                                                                 \
    if (0 == *out_stride)                                                                        \
    {                                                                                            \
      *out_stride = stride_rgb24;                                                                \
    }                                                                                            \
                                                                                                 \
    const std::int32_t leak_rgb24 = *out_stride - stride_rgb24;                                  \
    U3_CHECK ((leak_rgb24 >= 0), "leak_rgb less 0");

#endif
