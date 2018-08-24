//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       optim_s16bit.cpp
\date       26.07.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_optim_16bit_generic
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"

namespace libs { namespace optim { namespace s16bit {

void
calc_source_dims (
  std::size_t       _stride_src,
  std::size_t       _width,
  std::size_t       _height,
  const std::size_t _size_subpx,
  std::size_t&      _count_subpx_x,
  std::size_t&      _count_subpx_y,
  std::size_t&      _leak_src)
{
  _count_subpx_x = _width / _size_subpx;
  _count_subpx_y = _height;
  _leak_src      = _stride_src - sizeof (short) * _count_subpx_x * _size_subpx;

  // 24.05.2016 если данный цикл не состоит даже из одного прохода, шаг все-равно требуется уменьшить
  if (_count_subpx_x <= 0)
    {
      _leak_src -= sizeof (short) * _size_subpx;
    }

  UASSERT (0 < _stride_src);
  UASSERT (0 < _width);
  UASSERT (0 < _count_subpx_y);
  return;
}


void
calc_dest_source_dims (
  std::size_t       _stride_dst,
  std::size_t       _stride_src,
  std::size_t       _width,
  std::size_t       _height,
  const std::size_t _size_subpx,
  std::size_t&      _count_subpx_x,
  std::size_t&      _count_subpx_y,
  std::size_t&      _leak_src,
  std::size_t&      _leak_dst)
{
  _count_subpx_x = 0;
  _count_subpx_y = 0;
  _leak_src      = 0;
  _leak_dst      = 0;

  calc_source_dims (
    _stride_src,
    _width,
    _height,
    _size_subpx,
    _count_subpx_x,
    _count_subpx_y,
    _leak_src);

  _leak_dst = _stride_dst - sizeof (short) * _count_subpx_x * _size_subpx;

  // 24.05.2016 если данный цикл не состоит даже из одного прохода, шаг все-равно требуется уменьшить
  if (_count_subpx_x <= 0)
    {
      _leak_dst -= sizeof (short) * _size_subpx;
    }

  UASSERT (0 < _stride_dst);
  UASSERT (0 < _width);
  UASSERT (0 < _count_subpx_y);
  return;
}


void
calc_dest_dims (
  std::size_t&      _stride_dst,
  std::size_t&      _width,
  std::size_t&      _leak,
  const std::size_t _size_subpx)
{
  UASSERT (0 < _stride_dst);
  UASSERT (0 < _width);

  std::size_t loc__count_subpx_x = (_width >> (4 == _size_subpx ? 2 : 3));

  if (_width & (4 == _size_subpx ? 0x3 : 0x7))
    {
      loc__count_subpx_x++;
    }

  loc__count_subpx_x = (0 == loc__count_subpx_x) ? 1 : loc__count_subpx_x;
  _leak              = (loc__count_subpx_x << (4 == _size_subpx ? 3 : 4));
  _stride_dst -= _leak;
  _width = _width << 1;
  return;
}


void
calc_dest_dims_source (
  std::size_t&      _stride_dst,
  std::size_t&      _stride_src,
  std::size_t&      _width,
  std::size_t&      _leak,
  const std::size_t _size_subpx)
{
  calc_dest_dims (_stride_dst, _width, _leak, _size_subpx);
  UASSERT (0 < _stride_src);
  _stride_src -= _leak;
  return;
}

}}}      // namespace libs::optim::s16bit
