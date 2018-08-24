//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       finder-nth-element-by-count.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_space_filter
\brief      Объявление типа для быстрого поиска n-го элемента в массиве чисел на основе сортировки подсчетом.
*/

//  Отладочное определение для отключения этапов поиска.
//  Используется для оценки соотношения затраченного времени между "холостым" ходом обхода и выбора пикселей и собственно фильтрации.
#ifndef SKIP_OPERATIONS_FOR_FINDER_NELEMENT
//# define  SKIP_OPERATIONS_FOR_FINDER_NELEMENT
#endif

namespace dlls { namespace filter_noise { namespace space { namespace impl { namespace rang { namespace vars {
/**
  \brief      Класс для быстрого поиска n-го элемента в распределенном не отсортированном массиве.
  \tparam[in] TTVal   тип элемента в входном распределенном массиве.
  */
template <
  typename TTVal>
class FinderNthElementByCount
{
  public:
  //  ext types
  using value_type       = TTVal;              //< ???
  using bound_value_type = unsigned char;      //< Тип для дипазона значений, который может обрабатываться данной реализацией. Он меньше, чем диапазон значений входного типа.

  explicit FinderNthElementByCount () :
    last_size_core_ (0),
    min_ (std::numeric_limits<value_type>::max ()),
    max_ (std::numeric_limits<value_type>::min ())
  {
    static_assert (std::is_integral<value_type>::value, "integer required.");
    static_assert (std::is_signed<value_type>::value, "signed integer required.");
    counters_.fill (0);
    return;
  }

  ~FinderNthElementByCount ()
  {}

  FinderNthElementByCount (const FinderNthElementByCount& _src) = delete;
  FinderNthElementByCount& operator= (const FinderNthElementByCount& _src) = delete;
  /**
    \brief      Функция для получения n-элемента по распределенному массиву.
    \param[in]  _beg_core   начало области фильтрации.
    \param[in]  _indxx      индекс столбца в строке, которому принадлежит центральный элемент области фильтрации.
    \param[in]  _indxy      индекс строки в буфере, которой принадлежит центральный элемент области фильтрации.
    \param[in]  _size_core  размер области фильтрации.
    \param[in]  _sstride    шаг строки буфера.
    \param[in]  _rang       ранг элемента.
    \return     значение n-го элемента.
    */
  value_type
  get (
    const value_type* _beg_core,
    std::size_t       _indxx,
    std::size_t       _indxy,
    const int         _size_core,
    std::size_t       _sstride,
    const int         _rang)
  {
    //  Нулевое значение допустимо, как признак отсутствия фильтрации для данного пикселя.
    //  Например если он представляет собой точку перегиба изображения.
    if (0 == _size_core)
      {
        last_size_core_ = _size_core;
        return 0;
      }
    //  Ищем минимум и максимум в разреженном массиве.
    //  Для каждого первого пикселя в строке или первого пикселя с изменным размером ядра фильтрации ищем в полной окрестности.
    //  Для всех последующих производим только обновление вычисленных на предыдущем шаге значений.
    //  Изменение размера ядра фильтрации может быть связано с буфером условий (опционально, настраивается через параметры).
    if (0 == _indxx || last_size_core_ != _size_core)
      {
        update_min_max (_beg_core, _size_core, _sstride);
        update_freqs (_beg_core, _size_core, _sstride);
        last_size_core_ = _size_core;
      }
    else
      {
        refresh_min_max (_beg_core, _size_core, _sstride);
        //  если это не первый пиксель в строке, то массив частот уже обновлен в update_min_max, поэтому отключаем.
        //update_freqs ( _beg_core, _size_core, _sstride );
      }
    return get_val_rang (_rang);
  }
  /**
    \brief  Функция сброса объекта в начальное состояния, для использования его с новой строки данных (например).
    */
  void
  reset ()
  {
    last_size_core_ = 0;
    min_            = std::numeric_limits<value_type>::max ();
    max_            = std::numeric_limits<value_type>::min ();

    counters_.fill (0);
    return;
  }


  protected:
  /**
    \brief      Вспомогательная функция полного поиска min/max в области фильтрации.
    \param[in]  _beg_core   начало области фильтрации.
    \param[in]  _size_core  размер области фильтрации.
    \param[in]  _sstride    шаг строки буфера.
    */
  void
  update_min_max (
    const value_type* _beg_core,
    const int         _size_core,
    std::size_t       _sstride)
  {
#if defined(SKIP_OPERATIONS_FOR_FINDER_NELEMENT) && 1
    //  debug
    min_ = rand () % 20;
    max_ = min_ + rand () % 100;
    return;
#endif
    counters_.fill (0);

    min_ = std::numeric_limits<value_type>::max ();
    max_ = std::numeric_limits<value_type>::min ();

    auto _minmaxbeg = _beg_core;

    for (int _indxy = 0; _indxy < _size_core; ++_indxy)
      {
        const auto _minmax = std::minmax_element (_minmaxbeg, _minmaxbeg + _size_core);

        min_ = std::min<value_type> (*_minmax.first, min_);
        max_ = std::max<value_type> (*_minmax.second, max_);
        FAST_MOVE_CPTR (_minmaxbeg, _sstride);
      }
    return;
  }
  /**
    \brief      Вспомогательная функция обновления min/max в области фильтрации. 
                Обновление производится по удаляемому слева и добавляемому справа столбцам.
                Также производится обновление массива частот.
    \param[in]  _beg_core   начало области фильтрации.
    \param[in]  _size_core  размер области фильтрации.
    \param[in]  _sstride    шаг строки буфера.
    */
  void
  refresh_min_max (
    const value_type* _beg_core,
    const int         _size_core,
    std::size_t       _sstride)
  {
#if defined(SKIP_OPERATIONS_FOR_FINDER_NELEMENT) && 1
    //debug
    min_ = rand () % 20;
    max_ = min_ + rand () % 100;
    return;
#endif

    //  уменьшаем частоты удаленного левого столбца.
    {
      const value_type* _del_val = _beg_core - 1;

      for (int _indxy = 0; _indxy < _size_core; ++_indxy)
        {
          auto _val = _del_val[0];
          UASSERT (counters_[_val] > 0);
          --counters_[_val];
          FAST_MOVE_CPTR (_del_val, _sstride);
        }
    }

    //  добавляем новый правый столбец.
    value_type _add_min = std::numeric_limits<value_type>::max ();
    value_type _add_max = std::numeric_limits<value_type>::min ();

    {
      const value_type* _add_val = _beg_core + _size_core - 1;

      for (int _indxy = 0; _indxy < _size_core; ++_indxy)
        {
          auto _val = _add_val[0];
          _add_min  = std::min<value_type> (_val, _add_min);
          _add_max  = std::max<value_type> (_val, _add_max);
          ++counters_[_val];
          FAST_MOVE_CPTR (_add_val, _sstride);
        }
    }

    //  обновляем минимальный элемент, с учетом удаленного столбца и добавленного
    {
      value_type _find_min_beg = std::min<value_type> (_add_min, min_);
      value_type _find_min_end = std::max<value_type> (_add_min, min_);

      for (value_type _find_min = _find_min_beg; _find_min <= _find_min_end; ++_find_min)
        {
          if (counters_[_find_min])
            {
              min_ = _find_min;
              break;
            }
        }
    }

    //  обновляем максимальный элемент, с учетом удаленного столбца и добавленного
    {
      value_type _find_max_beg = std::min<value_type> (_add_max, max_);
      value_type _find_max_end = std::max<value_type> (_add_max, max_);

      for (value_type _find_max = _find_max_end; _find_max >= _find_max_beg; --_find_max)
        {
          if (counters_[_find_max])
            {
              max_ = _find_max;
              break;
            }
        }
    }
    return;
  }
  /**
    \brief      Вспомогательная функция обновления массива частот. 
    \param[in]  _beg_core   начало области фильтрации.
    \param[in]  _size_core  размер области фильтрации.
    \param[in]  _sstride    шаг строки буфера.
    */
  void
  update_freqs (
    const value_type* _beg_core,
    const int         _size_core,
    std::size_t       _sstride)
  {
#if defined(SKIP_OPERATIONS_FOR_FINDER_NELEMENT) && 1
    return;
#endif
    //  обновляем массив частот.
    auto _counts_beg = &counters_[min_];

    std::fill_n (_counts_beg, max_ - min_ + 1, static_cast<short> (0));

    const value_type* _cur_val = _beg_core;

    for (int _indxy = 0; _indxy < _size_core; ++_indxy)
      {
        for (int _indxx = 0; _indxx < _size_core; ++_indxx)
          {
            auto _val = _cur_val[_indxx];
            ++counters_[_val];
          }

        FAST_MOVE_CPTR (_cur_val, _sstride);
      }
    return;
  }
  /**
    \brief      Вспомогательная функция поиска n-го элемента по массиву частот.
    \param[in]  _rang ранг элемента (фактически его индекс в отсортированном массиве.
    \return     n-ный элемент.
    */
  value_type
  get_val_rang (const int _rang)
  {
#if defined(SKIP_OPERATIONS_FOR_FINDER_NELEMENT) && 1
    //Ищем ранг.
    return rand () % 256;
#endif
    int        _summ_vals  = 0;
    const auto _counts_beg = &counters_[min_];
    const auto _counts_end = &counters_[max_ + 1];

    for (auto _pval = _counts_beg; _pval != _counts_end; ++_pval)
      {
        _summ_vals += *_pval;

        if (_summ_vals >= _rang)
          {
            return _pval + min_ - _counts_beg;
          }
      }

    UASSERT_SIGNAL ("failed");
    return 0;
  }


  private:
  //  int types
  using counters_type = std::array<short, 256 + 1>;      //< Тип для хранения частот всех значений. На данный момент все значения должны умещаться в беззнаковый символ. +1 добавлен для удобства итерации по ним.

  counters_type counters_;            //< Счетчик частот символов.
  value_type    min_;                 //< Минимальный индекс счетчика, с значением отличным от 0.
  value_type    max_;                 //< Максимальный индекс счетчика, с значением отличным от 0.
  int           last_size_core_;      //< Последний использованный размер ядра фильтрации. Может меняться по условию.
};

}}}}}}      // namespace dlls::filter_noise::space::impl::rang::vars
