#pragma once
/**
\file       skip-sort-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
*/

namespace dlls::noisez::space::impl::rang::vars
{
/// Реализация фильтрации с пропуском сортировки
/// Для оценки холостого хода и теста
class SkipSortAlg final
{
  public:
  SkipSortAlg ()  = default;
  ~SkipSortAlg () = default;

  void
  process (
    const std::int16_t* beg_spx,
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
    if (size_core)
    {
      int                 off_core     = 0;
      const std::int16_t* temp_beg_spx = spx;

      temp_beg_spx = ::libs::helpers::mem::move_cptr_back (temp_beg_spx, beg_cond_core);

      for (int indxyc = 0; indxyc < size_core; ++indxyc)
      {
        std::copy (temp_beg_spx, temp_beg_spx + size_core, sort_vals_ + off_core);
        off_core += size_core;
        temp_beg_spx = ::libs::helpers::mem::move_cptr (temp_beg_spx, sstride);
      }
    }

    *ipx = *spx;
  }

  private:
  std::int16_t sort_vals_[syn::space_consts::max_size_core * syn::space_consts::max_size_core];   //< Временный массив для сортированной последовательности
};

/// Реализация фильтрации с пропуском сортировки
/// Для оценки холостого хода и теста
using SkipSortImpl = GenericImpl< SkipSortAlg >;
}   // namespace dlls::noisez::space::impl::rang::vars
