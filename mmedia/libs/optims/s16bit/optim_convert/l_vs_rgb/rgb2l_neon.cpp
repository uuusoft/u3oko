/**
file       rgb2l_neon.cpp
author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
date       01.11.2016
project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb.hpp"
#include "rgb_to_l_int.hpp"

#if defined(U3_CPU_ARM)

namespace libs::optim::s16bit::convert::l_vs_rgb
{
void
rgb24_to_l_neon_float (::libs::optim::io::MCallInfo& info)
{
  RGB2L_PREFIX (1);
  U3_MARK_UNUSED_HERE (leak_hsl);

  const std::int32_t  stride_hsl = info.dsts_[0].stride_;
  const std::uint8_t* rgb24str   = U3_CAST_REINTERPRET< const std::uint8_t* > (rgb24);
  float               sl         = 0.0f;

  for (std::uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::uint32_t indx_x = 0; indx_x < width; ++indx_x)
    {
      const float min = std::min< float > (rgb24str[2], std::min< float > (rgb24str[1], rgb24str[0]));   // Min. value of RGB
      const float max = std::max< float > (rgb24str[2], std::max< float > (rgb24str[1], rgb24str[0]));   // Max. value of RGB

      sl = (max + min) * 0.5f;

      l[indx_x] = U3_CAST_UINT16 (sl);

      rgb24str += 3;
    }

    U3_FAST_MOVE_CPTR (rgb24str, leak_rgb);
    U3_FAST_MOVE_PTR (l, stride_hsl);
  }
}


void
rgb24_to_l_neon (::libs::optim::io::MCallInfo& info)
{
  RGB2L_PREFIX (1);
  U3_MARK_UNUSED_HERE (leak_hsl);

  const std::uint32_t stride_hsl = info.dsts_[0].stride_;
  const std::uint8_t* rgb24str   = U3_CAST_REINTERPRET< const std::uint8_t* > (rgb24);

  for (std::uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::uint32_t indx_x = 0; indx_x < width; ++indx_x)
    {
      const std::uint8_t min = std::min< std::uint8_t > (rgb24str[2], std::min< std::uint8_t > (rgb24str[1], rgb24str[0]));   // Min. value of RGB
      const std::uint8_t max = std::max< std::uint8_t > (rgb24str[2], std::max< std::uint8_t > (rgb24str[1], rgb24str[0]));   // Max. value of RGB

      l[indx_x] = (max + min) >> 1;
      rgb24str += 3;
    }

    U3_FAST_MOVE_CPTR (rgb24str, leak_rgb);
    U3_FAST_MOVE_PTR (l, stride_hsl);
  }
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb

#endif
