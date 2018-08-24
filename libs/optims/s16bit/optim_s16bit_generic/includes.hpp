//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes.hpp
\date       26.07.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_ops
\brief    Внешний интерфейс включения модуля.
*/
#include "consts/vals.hpp"
#include "consts/def_buffs.hpp"
#include "consts/def_buffs_f32.hpp"

namespace libs { namespace optim { namespace s16bit {
/**
  \brief  empty brief?
  */
void calc_source_dims (
  std::size_t       _stride_src,
  std::size_t       _width,
  std::size_t       _height,
  const std::size_t _size_subpx,
  std::size_t&      _count_subpx_x,
  std::size_t&      _count_subpx_y,
  std::size_t&      _leak_src);
/**
  \brief  empty brief?
  */
void calc_dest_source_dims (
  std::size_t       _stride_dst,
  std::size_t       _stride_src,
  std::size_t       _width,
  std::size_t       _height,
  const std::size_t _size_subpx,
  std::size_t&      _count_subpx_x,
  std::size_t&      _count_subpx_y,
  std::size_t&      _leak_src,
  std::size_t&      _leak_dst);
/**
  \brief  empty brief?
  */
void calc_dest_dims (
  std::size_t&      _stride_dst,
  std::size_t&      _width,
  std::size_t&      _leak,
  const std::size_t _size_subpx);
/**
  \brief  empty brief?
  */
void calc_dest_dims_source (
  std::size_t&      _stride_dst,
  std::size_t&      _stride_src,
  std::size_t&      _width,
  std::size_t&      _leak,
  const std::size_t _size_subpx);

}}}      // namespace libs::optim::s16bit
