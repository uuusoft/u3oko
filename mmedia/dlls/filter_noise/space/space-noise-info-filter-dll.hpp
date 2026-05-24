#pragma once
/**
\file       space-noise-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_filter_space
*/

namespace dlls::filter_noise::space
{
/// Структура для расширения постоянных свойств узла графа обработки данных для фильтрации изображения в пространственной области
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& src)            = delete;
  InfoFilter& operator= (const InfoFilter& src) = delete;

  syn::VideoSpaceNoiseRemoverProp::raw_ptr  rprops_;             //< Настроенный указатель на свойства (для удобства)
  ::libs::helpers::statistic::ExpandedTimes expand_time_algs_;   //< Поле для логирования времени работы
  std::int64_t                              counter_frame_;      //< Количество обработанных кадров
  syn::MedianSpaceFilterProp                median_props_;       //<
};
}   // namespace dlls::filter_noise::space
