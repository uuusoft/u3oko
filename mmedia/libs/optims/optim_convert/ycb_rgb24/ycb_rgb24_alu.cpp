/**
\file       ycb_rgb24_alu.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       30.07.2018
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"
#include "ycb_rgb24.hpp"
#include "ycb_rgb24_int.hpp"

namespace libs::optim::convert::ycb_rgb24
{
void
alu (::libs::optim::io::MCallInfo& info)
{
  YCB2RGB24_PREFIX;
#ifdef U3_FAKE_DISABLE
  const int           size_block = height * width;
  const std::uint8_t* y          = yuy2_buf;
  const std::uint8_t* rc         = y + size_block;
  const std::uint8_t* rb         = rc + size_block;

  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += 2)
    {
      std::int16_t y1        = y[0];   // U3_CAST_INT16 (y[0]) - 16;
      std::int16_t y2        = y[1];   // U3_CAST_INT16 (y[1]) - 16;
      auto         u         = U3_CAST_INT16 (rc[0]) - 128;
      auto         v         = U3_CAST_INT16 (rb[0]) - 128;
      const int    y1_premul = y1 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y1_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y1_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y1_premul, u, v));

      rgb24_buf[0] = y1;   // debug
      rgb24_buf[1] = y1;   // debug
      rgb24_buf[2] = y1;   // debug

      // rgb24_buf[0] = rand () % 256;      // debug
      // rgb24_buf[1] = rand () % 256;      // debug
      // rgb24_buf[2] = rand () % 256;      // debug

      rgb24_buf += 3;

      const int y2_premul = y2 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y2_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y2_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y2_premul, u, v));

      rgb24_buf[0] = y2;   // debug
      rgb24_buf[1] = y2;   // debug
      rgb24_buf[2] = y2;   // debug

      // rgb24_buf[0] = rand () % 256;      // debug
      // rgb24_buf[1] = rand () % 256;      // debug
      // rgb24_buf[2] = rand () % 256;      // debug

      y += 4;
      ++rc;
      ++rb;
      rgb24_buf += 3;
    }

    // yuy2_buf += leak_yuy2;
    rgb24_buf += leak_rgb24;
  }
#elif 1

  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += 2)
    {
      std::int16_t y1 = yuy2_buf[0];   // U3_CAST_INT16 (yuy2_buf[0]) - 16;
      std::int16_t y2 = yuy2_buf[1];   // U3_CAST_INT16 (yuy2_buf[2]) - 16;
      // std::int16_t     u         = U3_CAST_INT16 (yuy2_buf[2]) - 128;
      // std::int16_t     v         = U3_CAST_INT16 (yuy2_buf[1]) - 128;
      // const int y1_premul = y1 * 4769;

      // rgb24_buf[0] = gen::short2char (gen::yuv2red (y1_premul, u, v));
      // rgb24_buf[1] = gen::short2char (gen::yuv2green (y1_premul, u, v));
      // rgb24_buf[2] = gen::short2char (gen::yuv2blue (y1_premul, u, v));

      rgb24_buf[0] = y1;   // debug
      rgb24_buf[1] = y1;   // debug
      rgb24_buf[2] = y1;   // debug
      rgb24_buf += 3;

      rgb24_buf[0] = y2;   // debug
      rgb24_buf[1] = y2;   // debug
      rgb24_buf[2] = y2;   // debug
      rgb24_buf += 3;

      // rgb24_buf[0] = rand () % 256;      // debug
      // rgb24_buf[1] = rand () % 256;      // debug
      // rgb24_buf[2] = rand () % 256;      // debug

      yuy2_buf += 2;
    }

    yuy2_buf += leak_yuy2;
    rgb24_buf += leak_rgb24;
  }

#else
  for (std::size_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (std::size_t indx_x = 0; indx_x < width; indx_x += 2)
    {
      auto      y1        = U3_CAST_INT16 (yuy2_buf[0]) - 16;
      auto      y2        = U3_CAST_INT16 (yuy2_buf[2]) - 16;
      auto      u         = U3_CAST_INT16 (yuy2_buf[3]) - 128;
      auto      v         = U3_CAST_INT16 (yuy2_buf[1]) - 128;
      const int y1_premul = y1 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y1_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y1_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y1_premul, u, v));

      rgb24_buf[0] = rand () % 256;   // debug
      rgb24_buf[1] = rand () % 256;   // debug
      rgb24_buf[2] = rand () % 256;   // debug

      rgb24_buf += 3;

      const int y2_premul = y2 * 4769;

      rgb24_buf[0] = gen::short2char (gen::yuv2red (y2_premul, u, v));
      rgb24_buf[1] = gen::short2char (gen::yuv2green (y2_premul, u, v));
      rgb24_buf[2] = gen::short2char (gen::yuv2blue (y2_premul, u, v));

      // rgb24_buf[0] = rand () % 256;      // debug
      // rgb24_buf[1] = rand () % 256;      // debug
      // rgb24_buf[2] = rand () % 256;      // debug

      yuy2_buf += 4;
      rgb24_buf += 3;
    }

    yuy2_buf += leak_yuy2;
    rgb24_buf += leak_rgb24;
  }
#endif
}
}   // namespace libs::optim::convert::ycb_rgb24
