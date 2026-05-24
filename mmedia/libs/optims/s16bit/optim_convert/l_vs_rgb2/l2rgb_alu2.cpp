/**
\file
\author    Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create    31.07.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb2.hpp"
#include "l_to_rgb_int2.hpp"

namespace libs::optim::s16bit::convert::l_vs_rgb2
{
void
l_to_rgb24_alu (::libs::optim::io::MCallInfo& info)
{
  L2RGB_PREFIX (1);

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      const std::uint8_t val = U3_CAST_STATIC< std::uint8_t > (l[0] & 0xFF);

      rgb24[0] = val;
      rgb24[1] = val;
      rgb24[2] = val;

      ++l;
      rgb24 += 3;
    }

    U3_FAST_MOVE_PTR (rgb24, leak_l);
    U3_FAST_MOVE_CPTR (l, leak_l);
  }
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb2
