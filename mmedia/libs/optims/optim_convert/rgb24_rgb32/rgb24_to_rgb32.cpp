/**
\file       rgb24_to_rgb32.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_optim_gen_convert
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "rgb24_to_rgb32.hpp"

namespace libs::optim::convert::rgb24_rgb32
{
void
alu (
  const std::uint8_t* rgb24_buf,
  std::uint32_t       stride_rgb24,
  std::uint32_t       width,
  std::uint32_t       height,
  std::uint8_t*       rgb32_buf,
  std::uint32_t       stride_rgb32,
  std::uint32_t       max_size_buf_rgb32,
  std::uint8_t        fill_alpha)
{
  U3_ASSERT (rgb24_buf);
  U3_ASSERT (stride_rgb24);
  U3_ASSERT (width);
  U3_ASSERT (height);
  U3_ASSERT (rgb32_buf);
  U3_ASSERT (stride_rgb32);
  U3_ASSERT (max_size_buf_rgb32);
  U3_ASSERT (width * 3 <= stride_rgb24);
  U3_ASSERT (width * 4 <= stride_rgb32);
  U3_ASSERT (stride_rgb32 * height <= max_size_buf_rgb32);

  const std::uint32_t leak_rgb32 = stride_rgb32 - width * 4;
  const std::uint32_t leak_rgb24 = stride_rgb24 - width * 3;

  for (uint32_t indx_y = 0; indx_y < height; ++indx_y)
  {
    for (uint32_t indx_x = 0; indx_x < width; ++indx_x)
    {
      rgb32_buf[3] = fill_alpha;
      rgb32_buf[0] = rgb24_buf[0];
      rgb32_buf[1] = rgb24_buf[1];
      rgb32_buf[2] = rgb24_buf[2];

      rgb32_buf += 4;
      rgb24_buf += 3;
    }

    rgb24_buf += leak_rgb24;
    rgb32_buf += leak_rgb32;
  }
}
}   // namespace libs::optim::convert::rgb24_rgb32
