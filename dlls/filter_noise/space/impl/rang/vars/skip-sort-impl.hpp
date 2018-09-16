//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       skip-sort-impl.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_filter_space
\brief      empty brief
*/

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang { namespace vars {
/**
\brief  Реализация фильтрации с пропуском сортировки. Для оценки холостого хода и теста.
*/
class SkipSortAlg final
{
  public:
  SkipSortAlg ()
  {}

  ~SkipSortAlg ()
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
        int          _off_core     = 0;
        const short* _temp_beg_spx = _spx;

        FAST_MOVE_CPTR_BACK (_temp_beg_spx, _beg_cond_core);

        for (int _indxyc = 0; _indxyc < _size_core; ++_indxyc)
          {
            std::copy (_temp_beg_spx, _temp_beg_spx + _size_core, sort_vals_ + _off_core);
            _off_core += _size_core;
            FAST_MOVE_CPTR (_temp_beg_spx, _sstride);
          }
      }

    *_ipx = *_spx;
    return;
  }


  private:
  short sort_vals_[::libs::ievents::props::videos::noises::space::ext::consts::max_size_core * ::libs::ievents::props::videos::noises::space::ext::consts::max_size_core];      //< Временный массив для сортированной последовательности.
};

/// Реализация фильтрации с пропуском сортировки. Для оценки холостого хода и теста.
using SkipSortImpl = GenericImpl<SkipSortAlg>;

}}}}}}      // namespace dlls::filter_noise::space::impl::rang::vars
