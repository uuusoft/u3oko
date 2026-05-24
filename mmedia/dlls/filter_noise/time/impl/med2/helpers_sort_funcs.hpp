#pragma once
/**
\file       helpers_sort_funcs.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_unknown
*/

namespace dlls::filter_noise::time::impl::med2
{
/// Функция выбора наиболее подходящего алгоритма сортировки
/// Учитывается длина сортируемой последовательности и ранг числа
/// \param[in]      type     желаемый тип соритировки
/// \param[in]      length   длина последовательности
/// \param[in]      rang     ранг числа в последовательности, который важен
/// \param[in,out]  vals     последовательность для сортировки
inline void
sel_sort (
  ::libs::ievents::props::videos::noises::time::ext::Sortings type,
  const std::uint32_t                                         length,
  const std::uint32_t                                         rang,
  std::int16_t*                                               vals)
{
  U3_CHECK (rang < length, VTOLOG (rang) + VTOLOG (length));
  U3_ASSERT (vals);

  if (::libs::ievents::props::videos::noises::time::ext::Sortings::adaptive == type)
  {
    // Число 11 это в общем эвристика.
    type = (3 == length) ?
             ::libs::ievents::props::videos::noises::time::ext::Sortings::inplace_3_element :
             (length <= 11 ? ::libs::ievents::props::videos::noises::time::ext::Sortings::insert : ::libs::ievents::props::videos::noises::time::ext::Sortings::standart);
  }

  // самый часто используемый вариант сортировки, он же по умолчанию.
  if (::libs::ievents::props::videos::noises::time::ext::Sortings::insert == type || ::libs::ievents::props::videos::noises::time::ext::Sortings::usual == type)
  {
    ::libs::helpers::sorting::sorting_inplace_insert< std::int16_t* > (vals + 0, vals + length);
    return;
  }

  if (::libs::ievents::props::videos::noises::time::ext::Sortings::inplace_3_element == type)
  {
    U3_ASSERT (3 == length);
    ::libs::helpers::sorting::sorting_3_elements (vals);
    return;
  }

  if (::libs::ievents::props::videos::noises::time::ext::Sortings::standart == type)
  {
#if 0
    // На данный момент без разницы, т.к. практически все реализации stl сортируют последовательность короче 32 целиком. Т.к. скорость совпадает с std::sort
    // Но для полноты оставим пока так.
      std::sort ( vals, vals + length );
#else
    std::nth_element (vals, vals + rang, vals + length);
#endif
    return;
  }
  U3_THROW_EXCEPTION ("unknown sort type" + VTOLOG (U3_CAST_UINT32_FORCE (type)));
}
}   // namespace dlls::filter_noise::time::impl::med2
