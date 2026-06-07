#pragma once
/**
\file       rgb_to_l_int.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_convert
*/

#if !defined(RGB2L_PREFIX)
#  define RGB2L_PREFIX(size)                                                                                                              \
    U3_CHECK (check_rgb2l (info), "check rgb2l info");                                                                                    \
    const std::uint32_t ppc            = size;                                                                                            \
    std::int16_t*       l              = info.dsts_[0].buf ();                                                                            \
    const auto*         rgb24          = ::libs::helpers::casts::reinterpret_cast_helper< const std::uint32_t* > (info.srcs_[0].ubuf ()); \
    const std::uint32_t width          = info.srcs_[0].width_;                                                                            \
    const std::uint32_t height         = info.srcs_[0].height_;                                                                           \
    const std::uint32_t raw_cycle      = width / ppc;                                                                                     \
    const std::uint32_t cycle          = (raw_cycle * ppc < width) ? raw_cycle + 1 : raw_cycle;                                           \
    const std::uint32_t leak_rgb       = info.srcs_[0].stride_ - cycle * ppc * sizeof (std::uint8_t) * 3;                                 \
    const std::uint32_t req_stride_hsl = cycle * sizeof (std::uint16_t) * ppc;                                                            \
    const std::uint32_t leak_hsl       = info.dsts_[0].stride_ - req_stride_hsl;

#endif
