#pragma once
/**
\file       rand-sort-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_filter_space
*/

namespace dlls::noisez::space::impl::rang::vars
{
/// Реализация "зашумления" изображения путем случайного выбора элемента из окрестности пикселя (рзамером в ядро фильтрации)
class RandSortAlg final
{
  public:
  RandSortAlg ()  = default;
  ~RandSortAlg () = default;

  void
  process (
    const std::int16_t* start_spx,
    std::uint32_t       indxx,
    std::uint32_t       indxy,
    const std::int32_t  size_core,
    const std::int32_t  half_size_core,
    const std::int32_t  count_core_vals,
    const std::uint32_t beg_cond_core,
    std::uint32_t       sstride,
    const std::int32_t  rang,
    const std::int16_t* spx,
    std::int16_t*       ipx)
  {
    if (size_core)
    {
      const std::int32_t  randx   = rand () % size_core;
      const std::int32_t  randy   = rand () % size_core;
      const std::int16_t* beg_spx = spx;

      beg_spx = ::libs::utility::mem::move_cptr_back (beg_spx, beg_cond_core);
      beg_spx = ::libs::utility::mem::move_cptr (beg_spx, sstride * randy + randx * sizeof (std::int16_t));

      *ipx = *beg_spx;
    }
    else
    {
      *ipx = *spx;
    }
  }
};

/// Реализация "зашумления" изображения путем случайного выбора элемента из окрестности пикселя (ядро фильтрации)
using RandSortImpl = GenericImpl< RandSortAlg >;
}   // namespace dlls::noisez::space::impl::rang::vars
