#pragma once
/**
\file       hsl_to_rgb_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_convert
*/

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
inline void
check_hsl2rgb (::libs::optim::io::MCallInfo& info)
{
  U3_CHECK (1 == info.dsts_.size (), "dst size not equal 1");
  U3_CHECK (3 == info.srcs_.size (), "src size not equal 1");
  U3_CHECK (1 == info.params_.pints_.size (), "pint not equal 1");

  const ::libs::optim::io::ProxyBuf& h   = info.srcs_[0];
  const ::libs::optim::io::ProxyBuf& s   = info.srcs_[1];
  const ::libs::optim::io::ProxyBuf& l   = info.srcs_[2];
  const ::libs::optim::io::ProxyBuf& rgb = info.dsts_[0];

  U3_CHECK (
    (h.width_ == s.width_) && (h.width_ == l.width_) && (h.width_ == rgb.width_),
    "widths not equal: " + VTOLOG (h.width_) + VTOLOG (s.width_) + VTOLOG (l.width_) + VTOLOG (rgb.width_));

  U3_CHECK (
    (h.height_ == s.height_) && (h.height_ == l.height_) && (h.height_ == rgb.height_),
    "heights not equal: " + VTOLOG (h.height_) + VTOLOG (s.height_) + VTOLOG (l.height_) + VTOLOG (rgb.height_));
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb


#if !defined(HSL2RGB_PREFIX)
#  define HSL2RGB_PREFIX(size)                                                                   \
                                                                                                 \
    check_hsl2rgb (info);                                                                        \
    const std::uint32_t ppc    = size;                                                           \
    const std::uint32_t width  = info.dsts_[0].width_;                                           \
    const std::uint32_t height = info.dsts_[0].height_;                                          \
    const std::int16_t* h      = info.srcs_[0].buf ();                                           \
    const std::int16_t* s      = info.srcs_[1].buf ();                                           \
    const std::int16_t* l      = info.srcs_[2].buf ();                                           \
    std::uint8_t*       rgb24  = info.dsts_[0].ubuf ();                                          \
    std::uint32_t       pcx    = width / 4;                                                      \
                                                                                                 \
    pcx = (pcx * 4 < width) ? pcx + 1 : pcx;                                                     \
                                                                                                 \
    const std::uint32_t leak_hsl     = info.srcs_[0].stride_ - pcx * 4 * sizeof (std::uint16_t); \
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
