#pragma once
/**
\file       detect-move-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_detect_move
*/

namespace dlls::detectors::detect_move
{
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter ();

  syn::VideoDetectProp::raw_ptr          rprops_;       //< Настроенный указатель на свойства (для удобства)
  ::dlls::gens::vgen_diff::lib::DiffImpl diff_impl_;    //< Реализация вычисления разности между двумя кадрами
  syn::VideoDiffProp                     diff_props_;   //< Свойства вычисления разности
  ::dlls::gens::vgen_mops::lib::MopsImpl mops_impl_;    //< Реализация фильтрации (морфологической) разности
  syn::VideoMorphologyProp               mops_props_;   //< Свойства фильтрации (морфологической) разности
  bool                                   synced_;       //< Флаг требования синхронизации

  private:
  void init ();

  // overrides ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
  virtual void sync_int (bool force) override;
};
}   // namespace dlls::detectors::detect_move
