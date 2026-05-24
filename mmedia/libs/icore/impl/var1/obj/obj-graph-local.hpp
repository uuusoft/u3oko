#pragma once
/**
\file       obj-graph-local.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru, erashov2026@proton.me erashov2004@yandex.ru
\date       22.12.2016
\project    u3_icore_lib
\brief      Объявление реализации объекта локальной версии графа
*/
namespace libs::icore::impl::var1::graph
{
//  forward
class Graph;
}   // namespace libs::icore::impl::var1::graph

namespace libs::icore::impl::var1::obj
{
/// Реализация объекта в локальной версии графа обработки данных
class ObjGraph final : public IGraphNodeExt
{
  friend class ::libs::icore::impl::var1::graph::Graph;

  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ObjGraph)

  explicit ObjGraph (
    const ::libs::core::graph::IGraph*         pparent,
    const ::libs::core::graph::NodeID&         id_obj,
    ::libs::link::ILink::weak_ptr              logger,
    ::libs::helpers::statistic::ExpandedTimes& expand_objs_algoritm_time);

  virtual ~ObjGraph ();

  ObjGraph (const ObjGraph& src)            = delete;
  ObjGraph& operator= (const ObjGraph& src) = delete;

  private:
  //  internal typess
  using forever_dlls_types = ::libs::helpers::dlls::ForeverLoadDlls;
  using create_func_type   = ::boost::function< libs::icore::impl::var1::obj::dll::create_impl_func_type >;

  //  IGraphNode impl
  virtual core::graph::IInterfGraphObj::raw_ptr query_int (const ::libs::helpers::utils::cuuid& id_intef) override;

  //  IGraphNodeExt impl
  virtual void load_int (const ::pugi::xml_named_node_iterator& root) override;
  virtual void connect_int (int idpt1, IGraphNodeExt::ptr& filter, int idpt2) override;
  virtual void send_event2me_int (::libs::events::IEvent::ptr& evnt) override;
  virtual void stop_int () override;
  virtual void run_int () override;

  /// Функция загружает и иниицализирует объект из загружаемого кода (dll/so)
  /// \param[in]  name_lib имя файла кода
  /// \param[in]  node     узел xml для инициализации свойств объекта
  void load_lib (const std::string& name_lib, const ::pugi::xml_named_node_iterator& node);

  /// Функция освобождает объект из загружаемого кода (dll/so)
  void free_lib ();

  /// Функция устанавливает соединение между двумя объектами
  void set_src_connect (int indx_src, ObjGraph* filter, int indx_dst);

  /// Функция устанавливает соединение между двумя объектами
  void set_dst_connect (int indx_src, ObjGraph* filter, int indx_dst);

  /// Функция возвращает общую информацию о объекте графа обработки данных
  const obj::FilterInfo& get_info () const;

  /// Основная рабочая функция по обработке данных объектом графа
  /// \param[in, out] info параметры вызова
  void transform (obj::dll::TransformInfo& info);

  ::libs::helpers::dlls::dll_type                 lib_;           //< Собственно загруженная библиотека с реализацией
  const core::graph::IGraph*                      pparent_;       //< Указатель на граф, которому принадлежит данный объект
  libs::icore::impl::var1::obj::FilterInfo        info_;          //<
  libs::icore::impl::var1::obj::InterfsForFilter  iinfo_;         //<
  libs::icore::impl::var1::obj::dll::IFilter::ptr dfilter_;       //< Настоящая реализация полученная из dll/so
  libs::icore::impl::var1::obj::FilterRuns        state_;         //< Текущее состояние объекта с точки зрения запуска
  std::string                                     lib_name_;      //< Имя библиотеки, которая была использована для создания
  create_func_type                                pf_create_;     //< Функция в библиотеки, для создания настоящей реализации
  ::libs::link::ILink::weak_ptr                   logger_;        //< Логгер пути, устанавливается извне
  ::libs::helpers::statistic::ExpandedTimes&      exptimes_;      //<
  static forever_dlls_types                       frozen_dlls_;   //< Удерживаем в памяти все загруженные библиотеки, чтобы избегать сбоев при работе с событиями, которые были в них сгенерированы
};
}   // namespace libs::icore::impl::var1::obj
