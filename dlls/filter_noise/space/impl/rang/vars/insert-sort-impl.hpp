//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       insert-sort-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang { namespace vars {
/**
  \brief  Реализация фильтрации используя сортировку вставкой. Для оценки производительности относительно стандартной фильтрации.
  */
class InsertSortAlg
{
  public:
  InsertSortAlg ()
  {}

  ~InsertSortAlg ()
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
        //  копируем во временный буфер, чтобы отсортировать.
#if 0
        std::iota( _sort_vals, _sort_vals + COUNT_OF(_sort_vals), 0 );  //  debug
#else
        int          _off_core = 0;
        const short* _beg_spx  = _spx;

        FAST_MOVE_CPTR_BACK (_beg_spx, _beg_cond_core);

        for (int _indxyc = 0; _indxyc < _size_core; ++_indxyc)
          {
            std::copy (_beg_spx, _beg_spx + _size_core, sort_vals_ + _off_core);
            _off_core += _size_core;
            FAST_MOVE_CPTR (_beg_spx, _sstride);
          }

        //  сортируем временный буфер.
        ::libs::helpers::sorting::sorting_inplace_insert<short*> (sort_vals_ + 0, sort_vals_ + _count_core_vals);
#endif
        // сохраняем результат в входном/выходном буфере.
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

/// Реализация фильтрации используя сортировку вставкой.
using InsertSortImpl = GenericImpl<InsertSortAlg>;

}}}}}}      // namespace dlls::filter_noise::space::impl::rang::vars
