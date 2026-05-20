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
  virtual ~Filter ();

  void thread_func_impl (std::uint32_t indx_thread);
  void thread_postfunc_impl ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // ::libs::icore::impl::var1::obj::dll::IFilter overrides
  virtual void                          load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void                          transform_int (syn::TransformInfo& info) override;
  virtual void                          call_int (syn::CallInterfInfo& info) override;
  virtual void                          run_int () override;
  virtual void                          stop_int () override;
  virtual syn::IInterfGraphObj::raw_ptr query_int (const ::libs::helpers::utils::cuuid& inter) override;

  //  internal realization interface IDataSource
  void fill_buf (InfoFilter* finfo, syn::BufsEvent::raw_ptr buf);

  //  internal realization intreface ICtrlDriverDShow
  void update_source_driver (InfoFilter* finfo);
  void update_source_driver_exactly (InfoFilter* finfo, const std::string& name_impl);
  void init_pts (syn::ConnectInfo* info);

  ::libs::optim::io::hioptim scale_;               //< Реализация алгоритма для масштабирования изображения
  ::libs::optim::io::hioptim flip_y_;              //< Реализация алгоритма для отображения изображения по вертикали
  syn::IEmptyInterfObjGraph  support_interf_;      //< Поле используется как флаг поддержки ряда интерфейсов
  IDataSourceImpl            idata_source_impl_;   //< Реализация интерфейса libs::icore::impl::var1::obj::interfs::IDataSourceInterfObjGraph
  syn::tevents_type          events_from_impl_;    //< События, сгенерированные нижележайшем слоем. Передаются данным объектом в граф обработки данных

  static ::libs::helpers::dlls::ForeverLoadDlls frozen_dlls_;   //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы
};
}   // namespace dlls::sources::gen_vgen
