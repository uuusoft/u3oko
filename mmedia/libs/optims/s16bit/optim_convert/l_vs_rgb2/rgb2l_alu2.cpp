/**
\file
\author    Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\create    31.07.2016
\project    u3_optim_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"

#include "l_vs_rgb2.hpp"
#include "rgb_to_l_int2.hpp"

namespace libs::optim::s16bit::convert::l_vs_rgb2
{
void
rgb24_to_l_alu (::libs::optim::io::MCallInfo& info)
{
  RGB2L_PREFIX (1);
  U3_MARK_UNUSED_HERE (leak_hsl);

  const std::uint32_t stride_hsl = info.dsts_[0].stride_;
  const auto*         rgb24str   = ::libs::helpers::casts::reinterpret_cast_helper< const std::uint8_t* > (rgb24);

  for (std::uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::uint32_t indx_x = 0; indx_x < width; ++indx_x)
    {
      l[indx_x] = ::libs::optim::convert::gen::rgb2y (rgb24str[0], rgb24str[1], rgb24str[2]);

      rgb24str += 3;
    }

    rgb24str = ::libs::helpers::mem::move_cptr (rgb24str, leak_rgb);
    l        = ::libs::helpers::mem::move_ptr (l, stride_hsl);
  }
}
}   // namespace libs::optim::s16bit::convert::l_vs_rgb2
