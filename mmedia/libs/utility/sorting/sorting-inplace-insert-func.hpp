#pragma once
/**
\file       sorting-inplace-insert-func.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/

namespace libs::utility::sorting
{
/// Сортировка вставкой последовательности [beg, end), полезна для малых последовательностей
/// \tparam         TTIt  тип итератор произвольного доступа
/// \param[in, out] beg  начало сортируемой последовательности
/// \param[in, out] end  элемент за окончанием последовательности
template< typename TTIt >
void
sorting_inplace_insert (TTIt beg, TTIt end)
{
  for (TTIt eit = std::next (beg); eit != end; ++eit)
  {
    for (TTIt iit = eit; iit != beg && (*iit < *(std::prev (iit))); --iit)
    {
      std::swap (*iit, *std::prev (iit));
    }
  }
  U3_ASSERT (std::is_sorted (beg, end));
}
}   // namespace libs::utility::sorting
