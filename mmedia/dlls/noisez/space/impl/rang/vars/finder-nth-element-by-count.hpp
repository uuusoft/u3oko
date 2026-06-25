#pragma once
/**
\file       finder-nth-element-by-count.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_space_filter
\brief      Объявление типа для быстрого поиска n-го элемента в массиве чисел на основе сортировки подсчетом
*/

//  Отладочное определение для отключения этапов поиска.
//  Используется для оценки соотношения затраченного времени между "холостым" ходом обхода и выбора пикселей и собственно фильтрации.
#ifndef SKIP_OPERATIONS_FOR_FINDER_NELEMENT
// #  define SKIP_OPERATIONS_FOR_FINDER_NELEMENT
#endif

#ifndef DEBUG_ALG_SORT_FUND_RANG_ELEMENT
// #define DEBUG_ALG_SORT_FUND_RANG_ELEMENT
#endif

namespace dlls::noisez::space::impl::rang::vars
{
/// Класс для быстрого поиска n-го элемента в распределенном не отсортированном массиве
/// \tparam[in] template_source_value_type    тип элемента в входном распределенном массиве
/// \tparam[in] template_int_value_type       тип внутреннго элемента
template< typename template_source_value_type, typename template_int_value_type >
class FinderNthElementByCount final
{
  public:
  //  ext types
  using source_value_type = template_source_value_type;   //< Тип входных значений (обычно short)
  using int_value_type    = template_int_value_type;      //< Тип для дипазона значений, который может обрабатываться данной реализацией. Он меньше, чем диапазон значений входного типа

  FinderNthElementByCount ()
  {
    static_assert (std::is_integral< source_value_type >::value, "integer required.");
    static_assert (std::is_signed< source_value_type >::value, "signed integer required.");
    static_assert (std::is_integral< int_value_type >::value, "integer required.");
    static_assert (std::is_unsigned< int_value_type >::value, "signed integer required.");
    freq_counters_.fill (0);
  }

  ~FinderNthElementByCount () = default;

  FinderNthElementByCount (const FinderNthElementByCount& src)            = delete;
  FinderNthElementByCount& operator= (const FinderNthElementByCount& src) = delete;

  /// Функция для получения n-элемента по распределенному массиву
  /// \param[in]  beg_core   начало области фильтрации
  /// \param[in]  indxx      индекс столбца в строке, которому принадлежит центральный элемент области фильтрации
  /// \param[in]  indxy      индекс строки в буфере, которой принадлежит центральный элемент области фильтрации
  /// \param[in]  size_core  размер области фильтрации
  /// \param[in]  sstride    шаг строки буфера
  /// \param[in]  rang       ранг элемента
  /// \return     значение n-го элемента
  source_value_type
  get_nth_element (
    const source_value_type* beg_core,
    std::uint32_t            indxx,
    std::uint32_t            indxy,
    const std::int32_t       size_core,
    std::uint32_t            sstride,
    const std::int32_t       rang)
  {
    //  Нулевое значение допустимо, как признак отсутствия фильтрации для данного пикселя.
    //  Например если он представляет собой точку перегиба изображения.
    if (0 == size_core)
    {
      last_size_core_ = size_core;
      return 0;
    }
    //  Ищем минимум и максимум в разреженном массиве.
    //  Для каждого первого пикселя в строке или первого пикселя с изменным размером ядра фильтрации ищем в полной окрестности.
    //  Для всех последующих производим только обновление вычисленных на предыдущем шаге значений.
    //  Изменение размера ядра фильтрации может быть связано с буфером условий (опционально, настраивается через параметры).
    if (0 == indxx || last_size_core_ != size_core)
    {
      update_min_max (beg_core, size_core, sstride);
      update_freqs (beg_core, size_core, sstride);
      last_size_core_ = size_core;
    }
    else
    {
      refresh_min_max (beg_core, size_core, sstride);
      //  если это не первый пиксель в строке, то массив частот уже обновлен в update_min_max, поэтому отключаем.
      // update_freqs ( beg_core, size_core, sstride );
    }
    return get_val_rang (rang);
  }

  /// Функция сброса объекта в начальное состояния, для использования его с новой строки данных (например)
  void
  reset ()
  {
    last_size_core_ = 0;
    min_            = std::numeric_limits< int_value_type >::max ();
    max_            = std::numeric_limits< int_value_type >::min ();

    freq_counters_.fill (0);
  }

  protected:
  /// Вспомогательная функция полного поиска min/max в области фильтрации
  /// \param[in]  beg_core   начало области фильтрации
  /// \param[in]  size_core  размер области фильтрации
  /// \param[in]  sstride    шаг строки буфера
  void
  update_min_max (
    const source_value_type* beg_core,
    const std::int32_t       size_core,
    std::uint32_t            sstride)
  {
#ifdef SKIP_OPERATIONS_FOR_FINDER_NELEMENT
    //  debug
    min_ = rand () % 20;
    max_ = min_ + rand () % 100;
    return;
#endif

    freq_counters_.fill (0);   // принудительно сбрасываем при полном обновлении весь массив

    min_ = std::numeric_limits< source_value_type >::max ();
    max_ = std::numeric_limits< source_value_type >::min ();

    auto minmaxbeg = beg_core;

    for (int indxy = 0; indxy < size_core; ++indxy)
    {
      const auto minmax = std::minmax_element (minmaxbeg, minmaxbeg + size_core);   // локальный min+max для строки ядра
      // глобальный min+max для всего ядра
      min_      = std::min< source_value_type > (*minmax.first, min_);
      max_      = std::max< source_value_type > (*minmax.second, max_);
      minmaxbeg = ::libs::helpers::mem::move_cptr (minmaxbeg, sstride);
    }
  }

  /// Вспомогательная функция обновления min/max в области фильтрации Обновление производится по удаляемому слева и добавляемому справа столбцам
  /// Также производится обновление массива частот
  /// \param[in]  beg_core   начало области фильтрации
  /// \param[in]  size_core  размер области фильтрации
  /// \param[in]  sstride    шаг строки буфера
  void
  refresh_min_max (
    const source_value_type* beg_core,
    const std::int32_t       size_core,
    std::uint32_t            sstride)
  {
#ifdef SKIP_OPERATIONS_FOR_FINDER_NELEMENT
    // debug
    min_ = rand () % 20;
    max_ = min_ + rand () % 100;
    return;
#endif

    //  уменьшаем частоты удаленного левого столбца.
    {
      const source_value_type* del_val = beg_core - 1;
      for (int indxy = 0; indxy < size_core; ++indxy)
      {
        auto val = del_val[0];
        U3_ASSERT_NT (get_counter (val) > 0, VTOLOG (val));
        --update_counter (val);
        del_val = ::libs::helpers::mem::move_cptr (del_val, sstride);
      }
    }

    //  добавляем новый правый столбец.
    source_value_type add_min = std::numeric_limits< source_value_type >::max ();
    source_value_type add_max = std::numeric_limits< source_value_type >::min ();

    {
      const source_value_type* add_val = beg_core + size_core - 1;

      for (int indxy = 0; indxy < size_core; ++indxy)
      {
        auto val = add_val[0];
        add_min  = std::min< source_value_type > (val, add_min);
        add_max  = std::max< source_value_type > (val, add_max);

        ++update_counter (val);
        add_val = ::libs::helpers::mem::move_cptr (add_val, sstride);
      }
    }

    //  обновляем минимальный элемент, с учетом удаленного столбца и добавленного
    {
      source_value_type find_min_beg = std::min< source_value_type > (add_min, min_);
      source_value_type find_min_end = std::max< source_value_type > (add_min, min_);

      for (source_value_type find_min = find_min_beg; find_min <= find_min_end; ++find_min)
      {
        if (get_counter (find_min))
        {
          min_ = find_min;
          break;
        }
      }
    }

    //  обновляем максимальный элемент, с учетом удаленного столбца и добавленного
    {
      source_value_type find_max_beg = std::min< source_value_type > (add_max, max_);
      source_value_type find_max_end = std::max< source_value_type > (add_max, max_);

      for (source_value_type find_max = find_max_end; find_max >= find_max_beg; --find_max)
      {
        if (get_counter (find_max))
        {
          max_ = find_max;
          break;
        }
      }
    }
  }

  /// Вспомогательная функция обновления массива частот
  /// \param[in]  beg_core   начало области фильтрации
  /// \param[in]  size_core  размер области фильтрации
  /// \param[in]  sstride    шаг строки буфера
  void
  update_freqs (
    const source_value_type* beg_core,
    const std::int32_t       size_core,
    std::uint32_t            sstride)
  {
#ifdef SKIP_OPERATIONS_FOR_FINDER_NELEMENT
    return;
#endif

    zero_counters ();   //  обновляем массив частот.

    const source_value_type* cur_val = beg_core;

    for (int indxy = 0; indxy < size_core; ++indxy)
    {
      for (int indxx = 0; indxx < size_core; ++indxx)
      {
        auto val = cur_val[indxx];
#ifdef DEBUG_ALG_SORT_FUND_RANG_ELEMENT
        if (val < min_ || val > max_)
        {
          U3_XLOG_ERROR ("(val < min_ || val > max_) val=" << val << " min=" << min_ << " max=" << max_);
          throw std::runtime_error ("");
        }
#endif
        ++update_counter (val);
      }

      cur_val = ::libs::helpers::mem::move_cptr (cur_val, sstride);
    }
  }

  /// Вспомогательная функция поиска n-го элемента по массиву частот
  /// \param[in]  rang ранг элемента (фактически его индекс в отсортированном массиве
  /// \return     n-ный элемент
  source_value_type
  get_val_rang (const std::int32_t rang)
  {
#ifdef SKIP_OPERATIONS_FOR_FINDER_NELEMENT
    // Ищем ранг.
    return rand () % 256;
#endif
    int        summ_vals  = 0;
    const auto counts_beg = &get_counter (min_);
    const auto counts_end = &get_counter (max_) + 1;

    for (auto pval = counts_beg; pval != counts_end; ++pval)
    {
      summ_vals += *pval;
      if (summ_vals >= rang)
      {
        return pval + min_ - counts_beg;
      }
    }

#ifdef DEBUG_ALG_SORT_FUND_RANG_ELEMENT
    U3_ASSERT_SIGNAL ("beg=" << *counts_beg << " end=" << *counts_end << " min=" << min_ << " max=" << max_ << " rang=" << rang << " summ_vals=" << summ_vals);
    throw std::runtime_error ("");
#endif
    return min_;
  }


  const source_value_type&
  get_counter (source_value_type indx) const
  {
    indx = std::max< source_value_type > (std::numeric_limits< int_value_type >::min (), indx);
    indx = std::min< source_value_type > (std::numeric_limits< int_value_type >::max (), indx);
    return freq_counters_[indx];
  }


  source_value_type&
  update_counter (source_value_type indx)
  {
    indx = std::max< source_value_type > (std::numeric_limits< int_value_type >::min (), indx);
    indx = std::min< source_value_type > (std::numeric_limits< int_value_type >::max (), indx);
    return freq_counters_[indx];
  }

  void
  zero_counters ()
  {
    auto counts_beg = &update_counter (min_);
    auto counts_end = &update_counter (max_) + 1;

    for (auto indx = counts_beg; indx != counts_end; ++indx)
    {
      *indx = 0;
    }
  }

  private:
  //  internal typess
  using counters_array_type = std::array< source_value_type, std::numeric_limits< int_value_type >::max () + 1 >;   //< Тип для хранения частот всех значений. На данный момент все значения должны умещаться в беззнаковый символ. +1 добавлен для удобства итерации по ним

  counters_array_type freq_counters_;                                                       //< Счетчик частот символов
  source_value_type   min_            = std::numeric_limits< source_value_type >::max ();   //< Минимальный индекс счетчика, с значением отличным от 0
  source_value_type   max_            = std::numeric_limits< source_value_type >::min ();   //< Максимальный индекс счетчика, с значением отличным от 0
  std::int32_t        last_size_core_ = 0;                                                  //< Последний использованный размер ядра фильтрации. Может меняться по условию
};
}   // namespace dlls::noisez::space::impl::rang::vars
