#pragma once
/**
\file       sorting-3-elements-helpers-funcs.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/

namespace libs::helpers::sorting
{
/// Вспомогательная функция обмена по условию "больше"
/// \tparam         TTVal тип обмениваемого значения
/// \param[in, out] val1
/// \param[in, out] val2
/// \return         пусто
template< typename TTVal >
void
swap_if_large (TTVal& val1, TTVal& val2)
{
  if (val1 > val2)
  {
    std::swap (val1, val2);
  }
}

/// Сортировка 3 элементов
/// \tparam         TTVal тип обмениваемого значения
/// \param[in, out] val1
/// \param[in, out] val2
/// \return         пусто
template< typename TTVal >
void
sorting_3_elements (TTVal* vals)
{
  swap_if_large (vals[0], vals[1]);
  swap_if_large (vals[1], vals[2]);
  swap_if_large (vals[0], vals[1]);
}
}   // namespace libs::helpers::sorting
