/**
\file       uyvy_rgb24_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       28.03.2026
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"
#include "uyvy_rgb24.hpp"
#include "uyvy_rgb24_int.hpp"

namespace libs::optim::convert::uyvy_rgb24
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  UYVY2RGB24_PREFIX;
  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += 2)
    {
      auto y1 = U3_CAST_INT16 (yuy2_buf[1]) - 16;
      auto y2 = U3_CAST_INT16 (yuy2_buf[3]) - 16;
      auto u  = U3_CAST_INT16 (yuy2_buf[0]) - 128;
      auto v  = U3_CAST_INT16 (yuy2_buf[2]) - 128;

      const int y1_premul = y1 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y1_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y1_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y1_premul, u, v));

      rgb24_buf += 3;

      const int y2_premul = y2 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y2_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y2_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y2_premul, u, v));

      yuy2_buf += 4;
      rgb24_buf += 3;
    }

    yuy2_buf += leak_yuy2;
    rgb24_buf += leak_rgb24;
  }
}
}   // namespace libs::optim::convert::uyvy_rgb24
