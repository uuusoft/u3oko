#pragma once
/**
\file       gen-vgen-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_gen_vgen
*/

namespace dlls::sources::gen_vgen
{
/// Базовый фильтр захвата кадров из внешнего источника (http, ip, desktop, etc)
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter () = default;

  // EAI-REFACT
  auto thread_func_impl (std::uint32_t indx_thread) -> void;
  auto thread_postfunc_impl (std::uint32_t indx_thread) -> void;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // ::libs::icore::impl::var1::obj::dll::IFilter overrides
  virtual auto load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) -> void override;
  virtual auto transform_int (syn::TransformInfo& info) -> void override;
  virtual auto call_int (syn::CallInterfInfo& info) -> void override;
  virtual auto run_int () -> void override;
  virtual auto stop_int () -> void override;
  virtual auto query_int (const ::libs::helpers::utils::cuuid& inter) -> syn::IInterfGraphObj::raw_ptr override;

  //  internal realization interface IDataSource
  auto fill_buf (InfoFilter*, syn::BufsEvent::raw_ptr) -> void;

  //  internal realization intreface ICtrlDriverDShow
  auto update_source_driver (InfoFilter*) -> void;
  auto update_source_driver_exactly (InfoFilter*, const std::string&) -> void;
  auto init_pts (syn::ConnectInfo*) -> void;

  ::libs::optim::io::hioptim scale_;               //< Реализация алгоритма для масштабирования изображения
  ::libs::optim::io::hioptim flip_y_;              //< Реализация алгоритма для отображения изображения по вертикали
  syn::IEmptyInterfObjGraph  support_interf_;      //< Поле используется как флаг поддержки ряда интерфейсов
  IDataSourceImpl            idata_source_impl_;   //< Реализация интерфейса libs::icore::impl::var1::obj::interfs::IDataSourceInterfObjGraph
  syn::tevents_type          events_from_impl_;    //< События, сгенерированные нижележайшем слоем. Передаются данным объектом в граф обработки данных

  static ::libs::helpers::dlls::FreezerDlls frozen_dlls_;   //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы
};
}   // namespace dlls::sources::gen_vgen
