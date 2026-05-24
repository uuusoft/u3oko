#pragma once
/**
\file       space-noise-filter-dll.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
\brief      Файл интерфейса типа для фильтрации иозображения в пространственной области
*/

namespace dlls::filter_noise::space
{
/// Узел графа обработки данных для фильтрации изображения в простраственной области
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info) override;
  virtual void call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info) override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);
  void itransform ();
  /// Вспомогательная функция для обновления текущей реализации фильтрации
  /// Выбор делается на основе свойства, загруженного из xml
  void update_impl ();

  IFilterImpl::uniq_ptr impl_;   //< Поле реализация фильтрации, выбирается на основе параметра из xml файла конфигурации
};
}   // namespace dlls::filter_noise::space
