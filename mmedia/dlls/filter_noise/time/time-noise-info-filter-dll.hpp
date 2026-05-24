#pragma once
/**
\file       info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_time_filter_noise
*/

namespace dlls::filter_noise::time
{
/// Тип для хранения свойств, связанных с фильтром изображения во временной области
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter ();

  syn::VideoTimeNoiseRemoverProp::raw_ptr rprops_;             //< Настроенный указатель на свойства (для удобства)
  syn::ExpandedTimes                      expand_time_algs_;   //< Поле для логирования времени работы
  std::int64_t                            counter_frame_;      //< Количество обработанных кадров
  IFilterImpl::uniq_ptr                   impl_;               //< Поле реализация фильтрации, выбирается на основе параметра из xml файла конфигурации
  bool                                    synced_;             //< Флаг требования синхронизации

  private:
  // overrides ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
  virtual void sync_int (bool force) override;
};
}   // namespace dlls::filter_noise::time
