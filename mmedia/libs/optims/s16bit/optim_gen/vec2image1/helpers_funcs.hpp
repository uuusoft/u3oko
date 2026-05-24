#pragma once
/**
\file       helpers_funcs.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/

namespace libs::optim::s16bit::gen::vec2image1
{
void
fill (
  std::int16_t* buf,
  std::size_t   stride,
  std::int16_t  color,
  std::size_t   dx,
  std::size_t   dy)
{
  for (std::size_t indxy = 0; indxy < dy; ++indxy)
  {
    for (std::size_t indxx = 0; indxx < dx; ++indxx)
    {
      buf[indxx] = color;
    }

    U3_FAST_MOVE_PTR (buf, stride);
  }
}


short*
get_px (std::int16_t* base, std::size_t stride, int x, int y)
{
  if (y < 0)
  {
    std::int16_t* ret = base;
    U3_FAST_MOVE_PTR_BACK (ret, U3_CAST_SIZE_T (-y) * stride);
    ret += x;
    return ret;
  }

  std::int16_t* ret = base;
  U3_FAST_MOVE_PTR (ret, U3_CAST_SIZE_T (y) * stride);
  ret += x;
  return ret;
}


void
line (std::int16_t* base, std::size_t stride, int x1, int y1, int x2, int y2)
{
  const std::int32_t dx     = x1 - x2;
  const std::int32_t dy     = y1 - y2;
  const std::int32_t adx    = std::abs (dx);
  const std::int32_t ady    = std::abs (dy);
  std::int16_t       color  = 64;
  const std::int16_t dcolor = 20;

  if (adx >= ady)
  {
    const std::int32_t addx = x1 > x2 ? -1 : 1;
    const float        addy = U3_CAST_FLOAT (dy) / U3_CAST_FLOAT (adx);
    float              ny   = U3_CAST_FLOAT (y1);

    for (int nx = x1; nx != x2; nx += addx)
    {
      std::int16_t* px = get_px (base, stride, nx, U3_CAST_STATIC< std::int32_t > (ny));

      *px = color;
      color += dcolor;

      ::libs::helpers::utils::check_bound< std::int16_t > (color, U3_CAST_INT16 (0), U3_CAST_INT16 (255));

      ny += addy;
    }
  }
  else
  {
    const std::int32_t addy = y1 > y2 ? -1 : 1;
    const float        addx = U3_CAST_FLOAT (dx) / U3_CAST_FLOAT (ady);
    float              nx   = U3_CAST_FLOAT (x1);

    for (int ny = y1; ny != y2; ny += addy)
    {
      std::int16_t* px = get_px (base, stride, U3_CAST_STATIC< std::int32_t > (nx), ny);

      *px = color;
      color += dcolor;

      ::libs::helpers::utils::check_bound< std::int16_t > (color, U3_CAST_INT16 (0), U3_CAST_INT16 (255));

      nx += addx;
    }
  }
}
}   // namespace libs::optim::s16bit::gen::vec2image1
