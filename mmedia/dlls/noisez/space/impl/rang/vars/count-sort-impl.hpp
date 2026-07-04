#pragma once
/**
\file       count-sort-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_filter_space
*/

namespace dlls::noisez::space::impl::rang::vars
{
/// Реализация фильтрации используя сортировку подсчетом с кешем результата в строке
/// На данный момент это самая быстрая реализация на CPU
class CountSortAlg final
{
  public:
  //  ext types
  using nfinder_type = FinderNthElementByCount< std::int16_t, std::uint8_t >;

  CountSortAlg ()  = default;
  ~CountSortAlg () = default;

  void
  process (
    const std::int16_t* start_spx,
    std::uint32_t       indxx,
    std::uint32_t       indxy,
    const std::int32_t  size_core,
    const std::int32_t  half_size_core,
    const std::int32_t  count_core_vals,
    const std::int32_t  beg_cond_core,
    std::uint32_t       sstride,
    const std::int32_t  rang,
    const std::int16_t* spx,
    std::int16_t*       ipx)
  {
    start_spx = ::libs::utility::mem::move_cptr_back (start_spx, beg_cond_core);

    *ipx = nfinder.get_nth_element (
      start_spx,
      indxx,
      indxy,
      size_core,
      sstride,
      rang);

    if (0 == size_core)
    {
      *ipx = *spx;
    }
  }

  private:
  nfinder_type nfinder;   //< Поле для поиска n-элемента в области пикселя
};

/// Реализация фильтрации используя сортировку подсчетом с кешем результата в строке
///  На данный момент это самая быстрая реализация на CPU
using CountSortImpl = GenericImpl< CountSortAlg >;
}   // namespace dlls::noisez::space::impl::rang::vars
