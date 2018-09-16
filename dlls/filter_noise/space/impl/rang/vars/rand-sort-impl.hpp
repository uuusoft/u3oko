//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       rand-sort-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang { namespace vars {
/**
\brief  Реализация "зашумления" изображения путем случайного выбора элемента из окрестности пикселя (рзамером в ядро фильтрации).
*/
class RandSortAlg
{
  public:
  RandSortAlg ()
  {}

  ~RandSortAlg ()
  {}

  void
  process (
    const short* _start_spx,
    std::size_t  _indxx,
    std::size_t  _indxy,
    const int    _size_core,
    const int    _half_size_core,
    const int    _count_core_vals,
    const int    _beg_cond_core,
    std::size_t  _sstride,
    const int    _rang,
    const short* _spx,
    short*       _ipx)
  {
    if (_size_core)
      {
        const int    _randx   = rand () % _size_core;
        const int    _randy   = rand () % _size_core;
        const short* _beg_spx = _spx;

        FAST_MOVE_CPTR_BACK (_beg_spx, _beg_cond_core);
        FAST_MOVE_CPTR (_beg_spx, _sstride * _randy + _randx * sizeof (short));

        *_ipx = *_beg_spx;
      }
    else
      {
        *_ipx = *_spx;
      }
    return;
  }
};

/// Реализация "зашумления" изображения путем случайного выбора элемента из окрестности пикселя (ядро фильтрации).
using RandSortImpl = GenericImpl<RandSortAlg>;

}}}}}}      // namespace dlls::filter_noise::space::impl::rang::vars
