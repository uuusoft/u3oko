/**
\file       rgb_to_l_neon.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb2.hpp"
#include "rgb_to_l_int2.hpp"

#ifdef U3_CPU_ARM

namespace libs::optim::s16bit::convert::l_vs_rgb2
{
void
rgb24_to_l_neon (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  return rgb24_to_l_alu (info);
#  if 0
  RGB2L_PREFIX (1);

  const std::uint32_t stride_hsl = info.dsts_[0].stride_;
  const std::uint8_t* rgb24str   = ::libs::helpers::casts::reinterpret_cast_helper< const std::uint8_t* > (rgb24);

  for (std::uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::uint32_t indx_x = 0; indx_x < width; ++indx_x)
    {
      const std::uint8_t min = std::min< std::uint8_t > (rgb24str[2], std::min< std::uint8_t > (rgb24str[1], rgb24str[0]));   // Min. value of RGB
      const std::uint8_t max = std::max< std::uint8_t > (rgb24str[2], std::max< std::uint8_t > (rgb24str[1], rgb24str[0]));   // Max. value of RGB

      l[indx_x] = (max + min) >> 1;
      rgb24str += 3;
    }

    rgb24str = ::libs::helpers::mem::move_cptr (rgb24str, leak_rgb);
    l = ::libs::helpers::mem::move_ptr (l, stride_hsl);
  }
#  endif
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb2

#endif
