#pragma once
/**
\file       space-noise-filter-dll.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_filter_space
\brief      Файл интерфейса типа для фильтрации иозображения в пространственной области
*/

namespace dlls::noisez::space
{
/// Узел графа обработки данных для фильтрации изображения в простраственной области
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ()          = default;
  virtual ~Filter () = default;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo*, const ::pugi::xml_named_node_iterator&) override;
  virtual void transform_int (syn::TransformInfo&) override;
  virtual void call_int (syn::CallInterfInfo&) override;

  // internal
  void init_pts (syn::ConnectInfo*);
  auto itransform () -> void;

  /// Вспомогательная функция для обновления текущей реализации фильтрации
  /// Выбор делается на основе свойства, загруженного из xml
  void update_impl ();

  IFilterImpl::uniq_ptr impl_;   //< Поле реализация фильтрации, выбирается на основе параметра из xml файла конфигурации
};
}   // namespace dlls::noisez::space
