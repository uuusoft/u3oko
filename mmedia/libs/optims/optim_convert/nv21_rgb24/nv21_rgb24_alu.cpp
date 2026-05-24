/**
\file       nv21_rgb24_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.11.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"
#include "nv21_rgb24.hpp"
#include "nv21_rgb24_int.hpp"

namespace libs::optim::convert::nv21_rgb24
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  NV212RGB24 (2);

  for (std::uint32_t indx_y = 0; indx_y < yuy2->height_; ++indx_y)
  {
    const std::uint8_t* prev_uv_buf = uv_buf;
    for (std::uint32_t indx_x = 0; indx_x < yuy2->width_; indx_x += ppc)
    {
      std::int16_t y1 = U3_CAST_INT16 (y_buf[0]) - 16;
      std::int16_t y2 = U3_CAST_INT16 (y_buf[1]) - 16;
      std::int16_t u  = U3_CAST_INT16 (uv_buf[0]) - 128;
      std::int16_t v  = U3_CAST_INT16 (uv_buf[1]) - 128;

      const std::int32_t y1_premul = y1 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y1_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y1_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y1_premul, u, v));

      rgb24_buf += 3;

      const std::int32_t y2_premul = y2 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y2_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y2_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y2_premul, u, v));

      y_buf += 2;
      uv_buf += 2;
      rgb24_buf += 3;
    }

    y_buf += leak_yuy2;
    uv_buf += leak_yuy2;

    if (odd_line)
    {
      uv_buf = prev_uv_buf;
    }

    rgb24_buf += leak_rgb24;
    odd_line = !odd_line;
  }
}
}   // namespace libs::optim::convert::nv21_rgb24
