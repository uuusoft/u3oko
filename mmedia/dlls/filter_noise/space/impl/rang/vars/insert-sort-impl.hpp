#pragma once
/**
\file       insert-sort-impl.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
*/

namespace dlls::filter_noise::space::impl::rang::vars
{
/// Реализация фильтрации используя сортировку вставкой
/// Для оценки производительности относительно стандартной фильтрации
class InsertSortAlg
{
  public:
  InsertSortAlg ()
  {
  }

  ~InsertSortAlg ()
  {
  }

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
    if (size_core)
    {
#if 0
      //debug
      std::iota (sort_vals, sort_vals + std::size (sort_vals), 0);
#else
      //  копируем во временный буфер, чтобы отсортировать.
      int                 off_core = 0;
      const std::int16_t* beg_spx  = spx;

      U3_FAST_MOVE_CPTR_BACK (beg_spx, beg_cond_core);

      for (int indxyc = 0; indxyc < size_core; ++indxyc)
      {
        std::copy (beg_spx, beg_spx + size_core, sort_vals_ + off_core);
        off_core += size_core;
        U3_FAST_MOVE_CPTR (beg_spx, sstride);
      }

      //  сортируем временный буфер.
      ::libs::helpers::sorting::sorting_inplace_insert< std::int16_t* > (sort_vals_ + 0, sort_vals_ + count_core_vals);
#endif
      // сохраняем результат в входном/выходном буфере.
      *ipx = sort_vals_[rang];
    }
    else
    {
      *ipx = *spx;
    }
  }

  private:
  std::int16_t sort_vals_[::libs::ievents::props::videos::noises::space::ext::consts::max_size_core * ::libs::ievents::props::videos::noises::space::ext::consts::max_size_core];   //< Временный массив для сортированной последовательности
};

/// Реализация фильтрации используя сортировку вставкой
using InsertSortImpl = GenericImpl< InsertSortAlg >;
}   // namespace dlls::filter_noise::space::impl::rang::vars
