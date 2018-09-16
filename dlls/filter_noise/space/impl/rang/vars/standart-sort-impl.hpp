//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       standart-sort-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang { namespace vars {
/**
\brief  Реализация фильтрации используя сортировку из стандартной библиотеки.
*/
class StandartSortAlg final
{
  public:
  StandartSortAlg ()
  {}

  ~StandartSortAlg ()
  {}

  void
  process (
    const short* _beg_spx,
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
#if 0
        std::iota( sort_vals_, sort_vals_ + COUNT_OF(sort_vals_), 0 );  //  debug
#else
        //  копируем во временный буфер, чтобы отсортировать.
        int          _off_core     = 0;
        const short* _temp_beg_spx = _spx;

        FAST_MOVE_CPTR_BACK (_temp_beg_spx, _beg_cond_core);

        for (int _indxyc = 0; _indxyc < _size_core; ++_indxyc)
          {
            std::copy (_temp_beg_spx, _temp_beg_spx + _size_core, sort_vals_ + _off_core);
            _off_core += _size_core;
            FAST_MOVE_CPTR (_temp_beg_spx, _sstride);
          }
        //  сортируем временный буфер.
        //  На данный момент без разницы, т.к. практически все реализации stl сортируют последовательность короче 32 целиком. Т.к. скорость совпадает с std::sort
        //  Но для полноты оставим пока так.
        //  std::sort ( _sort_vals, _sort_vals + _applay_count_core_vals );
        std::nth_element (
          sort_vals_,
          sort_vals_ + _rang,
          sort_vals_ + _count_core_vals);
#endif
        //сохраняем результат в входном/выходном буфере.
        *_ipx = sort_vals_[_rang];
      }
    else
      {
        *_ipx = *_spx;
      }

    return;
  }


  private:
  short sort_vals_[::libs::ievents::props::videos::noises::space::ext::consts::max_size_core * ::libs::ievents::props::videos::noises::space::ext::consts::max_size_core];      //< Временный массив для сортированной последовательности.
};
/// Реализация фильтрации используя сортировку из стандартной библиотеки.
using StandartSortImpl = GenericImpl<StandartSortAlg>;

}}}}}}      // namespace dlls::filter_noise::space::impl::rang::vars
