/**
\file       optim_s16bit.cpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_16bit_generic
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"

namespace libs::optim::s16bit
{
void
calc_source_dims (
  picter_dim_type       stride_src,
  picter_dim_type       width,
  picter_dim_type       height,
  const picter_dim_type size_subpx,
  picter_dim_type&      count_subpx_x,
  picter_dim_type&      count_subpx_y,
  picter_dim_type&      leak_src)
{
  count_subpx_x = width / size_subpx;
  count_subpx_y = height;
  leak_src      = stride_src - sizeof (std::int16_t) * count_subpx_x * size_subpx;

  // 24.05.2016 если данный цикл не состоит даже из одного прохода, шаг все-равно требуется уменьшить
  if (count_subpx_x <= 0)
  {
    leak_src -= sizeof (std::int16_t) * size_subpx;
  }

  U3_ASSERT (0 < stride_src);
  U3_ASSERT (0 < width);
  U3_ASSERT (0 < count_subpx_y);
}


void
calc_dest_source_dims (
  picter_dim_type       stride_dst,
  picter_dim_type       stride_src,
  picter_dim_type       width,
  picter_dim_type       height,
  const picter_dim_type size_subpx,
  picter_dim_type&      count_subpx_x,
  picter_dim_type&      count_subpx_y,
  picter_dim_type&      leak_src,
  picter_dim_type&      leak_dst)
{
  count_subpx_x = 0;
  count_subpx_y = 0;
  leak_src      = 0;
  leak_dst      = 0;

  calc_source_dims (
    stride_src,
    width,
    height,
    size_subpx,
    count_subpx_x,
    count_subpx_y,
    leak_src);

  leak_dst = stride_dst - sizeof (std::int16_t) * count_subpx_x * size_subpx;

  // 24.05.2016 если данный цикл не состоит даже из одного прохода, шаг все-равно требуется уменьшить
  if (count_subpx_x <= 0)
  {
    leak_dst -= sizeof (std::int16_t) * size_subpx;
  }

  U3_ASSERT (0 < stride_dst);
  U3_ASSERT (0 < width);
  U3_ASSERT (0 < count_subpx_y);
}


void
calc_dest_dims (
  picter_dim_type&      stride_dst,
  picter_dim_type&      width,
  picter_dim_type&      leak,
  const picter_dim_type size_subpx)
{
  U3_ASSERT (0 < stride_dst);
  U3_ASSERT (0 < width);

  picter_dim_type loc__count_subpx_x = (width >> (4 == size_subpx ? 2 : 3));

  if (width & (4 == size_subpx ? 0x3 : 0x7))
  {
    loc__count_subpx_x++;
  }

  loc__count_subpx_x = (0 == loc__count_subpx_x) ? 1 : loc__count_subpx_x;
  leak               = (loc__count_subpx_x << (4 == size_subpx ? 3 : 4));
  stride_dst -= leak;
  width = width << 1;
}


void
calc_dest_dims_source (
  picter_dim_type&      stride_dst,
  picter_dim_type&      stride_src,
  picter_dim_type&      width,
  picter_dim_type&      leak,
  const picter_dim_type size_subpx)
{
  calc_dest_dims (stride_dst, width, leak, size_subpx);
  U3_ASSERT (0 < stride_src);
  stride_src -= leak;
}
}   // namespace libs::optim::s16bit
