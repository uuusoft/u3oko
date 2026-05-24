/**
\file       rgb32-rgb24-alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       22.02.2026
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "rgb32-rgb24.hpp"

namespace libs::optim::convert::rgb32_rgb24
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  const auto&         rgb32      = info.srcs_.at (0);
  auto&               rgb24      = info.dsts_.at (0);
  const auto          rgb32_bpp  = ::libs::helpers::uids::helpers::get_count_bytes_from_format (::libs::helpers::uids::minor::id_val::rgb32);
  const auto          rgb24_bpp  = ::libs::helpers::uids::helpers::get_count_bytes_from_format (::libs::helpers::uids::minor::id_val::rgb24);
  const std::uint8_t* rgb32_buf  = rgb32.ubuf ();
  std::uint8_t*       rgb24_buf  = rgb24.ubuf ();
  const int32_t       rgb32_leak = rgb32.stride_ - rgb32.width_ * rgb32_bpp;
  const int32_t       rgb24_leak = rgb24.stride_ - rgb24.width_ * rgb24_bpp;
  const auto          width      = rgb32.width_;
  const auto          height     = rgb32.height_;

  U3_XLOG_DBG (VTOLOG (rgb32_leak) + VTOLOG (rgb32.stride_) + VTOLOG (rgb32.width_) + VTOLOG (rgb32_bpp));
  U3_ASSERT (rgb32_leak >= 0);
  U3_ASSERT (rgb24_leak >= 0);
  for (std::uint32_t iy = 0; iy < height; ++iy)
  {
    for (std::uint32_t ix = 0; ix < width; ++ix)
    {
      rgb24_buf[0] = rgb32_buf[0];
      rgb24_buf[1] = rgb32_buf[1];
      rgb24_buf[2] = rgb32_buf[2];

      rgb32_buf += rgb32_bpp;
      rgb24_buf += rgb24_bpp;
    }

    U3_FAST_MOVE_CPTR (rgb32_buf, rgb32_leak);
    U3_FAST_MOVE_PTR (rgb24_buf, rgb24_leak);
  }
}
}   // namespace libs::optim::convert::rgb32_rgb24
