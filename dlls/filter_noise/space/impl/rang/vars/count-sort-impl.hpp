//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       count-sort-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang { namespace vars {
/**
\brief  Реализация фильтрации используя сортировку подсчетом с кешем результата в строке.
        На данный момент это самая быстрая реализация на CPU.
*/
class CountSortAlg
{
  public:
  //  ext types
  using nfinder_type = FinderNthElementByCount<short>;

  CountSortAlg ()
  {}

  ~CountSortAlg ()
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
    FAST_MOVE_CPTR_BACK (_start_spx, _beg_cond_core);

    *_ipx = _nfinder.get (
      _start_spx,
      _indxx,
      _indxy,
      _size_core,
      _sstride,
      _rang);

    if (0 == _size_core)
      {
        *_ipx = *_spx;
      }
    return;
  }


  private:
  nfinder_type _nfinder;      //< Поле для поиска n-элемента в области пикселя.
};

/// Реализация фильтрации используя сортировку подсчетом с кешем результата в строке. На данный момент это самая быстрая реализация на CPU.
using CountSortImpl = GenericImpl<CountSortAlg>;

}}}}}}      // namespace dlls::filter_noise::space::impl::rang::vars
