/**
\file       yuy2_rgb24_alu.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"
#include "yuy2_rgb24.hpp"
#include "yuy2_rgb24_int.hpp"

namespace libs::optim::convert::yuy2_rgb24
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  YUY22RGB24_PREFIX;

  for (std::size_t iy = 0; iy < height; ++iy)
  {
    for (std::size_t ix = 0; ix < width; ix += 2)
    {
      std::int16_t       y1        = U3_CAST_INT16 (yuy2_buf[0]) - 16;
      std::int16_t       y2        = U3_CAST_INT16 (yuy2_buf[2]) - 16;
      std::int16_t       u         = U3_CAST_INT16 (yuy2_buf[1]) - 128;
      std::int16_t       v         = U3_CAST_INT16 (yuy2_buf[3]) - 128;
      const std::int32_t y1_premul = y1 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y1_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y1_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y1_premul, u, v));

      rgb24_buf += 3;
      const std::int32_t y2_premul = y2 * 4769;

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
}   // namespace libs::optim::convert::yuy2_rgb24
