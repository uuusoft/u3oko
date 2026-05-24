#pragma once
/**
\file       includes.hpp
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_ops
*/
#include "consts/lib-optim-s16bit-gen-const-vals.hpp"
#include "consts/lib-optim-s16bit-def-bufs.hpp"
#include "consts/lib-optim-s16bit-def-bufs-f32.hpp"

namespace libs::optim::s16bit
{
using picter_dim_type = std::uint32_t;

void calc_source_dims (
  picter_dim_type       stride_src,
  picter_dim_type       width,
  picter_dim_type       height,
  const picter_dim_type size_subpx,
  picter_dim_type&      count_subpx_x,
  picter_dim_type&      count_subpx_y,
  picter_dim_type&      leak_src);


void calc_dest_source_dims (
  picter_dim_type       stride_dst,
  picter_dim_type       stride_src,
  picter_dim_type       width,
  picter_dim_type       height,
  const picter_dim_type size_subpx,
  picter_dim_type&      count_subpx_x,
  picter_dim_type&      count_subpx_y,
  picter_dim_type&      leak_src,
  picter_dim_type&      leak_dst);


void calc_dest_dims (
  picter_dim_type&      stride_dst,
  picter_dim_type&      width,
  picter_dim_type&      leak,
  const picter_dim_type size_subpx);


void calc_dest_dims_source (
  picter_dim_type&      stride_dst,
  picter_dim_type&      stride_src,
  picter_dim_type&      width,
  picter_dim_type&      leak,
  const picter_dim_type size_subpx);
}   // namespace libs::optim::s16bit
