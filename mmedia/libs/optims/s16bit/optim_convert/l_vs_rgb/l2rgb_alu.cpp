/**
\file
\author    Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create    31.07.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb.hpp"
#include "l_to_rgb_int.hpp"

namespace libs::optim::s16bit::convert::l_vs_rgb
{
void
l_to_rgb24_alu (::libs::optim::io::MCallInfo& info)
{
  L2RGB_PREFIX (1);

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      const auto val = U3_CAST_UINT8 (l[0] & 0xFF);

      rgb24[0] = val;
      rgb24[1] = val;
      rgb24[2] = val;

      ++l;
      rgb24 += 3;
    }

    rgb24 = ::libs::helpers::mem::move_ptr (rgb24, leak_l);
    l     = ::libs::helpers::mem::move_cptr (l, leak_l);
  }
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb
