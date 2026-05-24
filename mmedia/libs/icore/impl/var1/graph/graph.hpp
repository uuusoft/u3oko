#pragma once
/**
\file       graph.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       22.12.2016
\project    u3_icore_lib
\brief      Объявление реализации графа обработки данных в локальном режиме
*/

namespace libs::icore::impl::var1::graph
{
/// Реализация граф обработки данных в локальном режиме
class Graph final : public core::graph::IGraph
{
  public:
  Graph ();
  virtual ~Graph ();

  // U3-REFACT
  void thread_func_impl (std::uint32_t indx_thread);
  void thread_postfunc_impl (std::uint32_t indx_thread);

  private:
  //  internal typess
  using graph_obj_type          = ::libs::icore::impl::var1::obj::IGraphNodeExt;
  using obj_ids_type            = ::libs::core::graph::IGraph::obj_ids_type;
  using array_interf_type       = std::array< graph_obj_type::ptr, graph::consts::max_count_objs >;
  using arrays_interf_type      = std::array< array_interf_type, graph::consts::max_helper_objs >;
  using array_iinterf_type      = std::array< std::int32_t, graph::consts::max_helper_objs >;
  using sync_type               = std::mutex;
  using lock_type               = std::lock_guard< sync_type >;
  using id2data_graph_objs_type = std::unordered_map< syn::NodeID, graph_obj_type::ptr >;
  using live_ext_requests_type  = std::atomic< std::int32_t >;

  //  IGraph overrides
  virtual void                load_int (const std::string& folder) override;
  virtual const obj_ids_type& get_objs_int () override;
  virtual void                send_event2obj_int (const syn::NodeID& id_obj, events::IEvent::ptr& evnt) override;
  virtual void                set_logger_int (::libs::link::ILink::weak_ptr ptr) override;

  void load_impl (const ::pugi::xml_named_node_iterator& root);
  void connect_impl (const ::pugi::xml_named_node_iterator& pt);
  void clear_impl ();
  void deb_load_objs_impl ();

  /// Функция обработки буферов /захват, передача по цепочки фильтров, возврат
  /// \return true, если при ее вызове был обработан хотя бы один буфер, иначе false
  bool data_graph_process_impl ();
  void change_objs_state_impl (const obj::FilterRuns& state);
  void data_graph_work_func_impl (var1::obj::ObjGraph*, ::libs::bufs::Bufs::ptr&, const std::uint32_t, obj::dll::TransformInfo::tevents_type*);

  /// Функция обработки особо важных событий для графа
  /// \param[in]  evnt событие
  /// \param[in]  funct  функция-решения, предоставленная клиентом
  void recive_special_event_impl (const events::IEvent::ptr& evnt);

  /// Функция возращает по идентификатору объект графа
  /// \param[in]  obj_id событие
  /// \return     объект или empty
  graph_obj_type::weak_ptr get_obj_impl (const syn::NodeID& obj_id);

  /// Функция синхронизации идентификаторов объектов после загрузки из xml
  void refresh_id_objs_impl () const;

  obj::FilterRuns                state_;                  //< Состояние графа с точки зрения запуска
  std::unique_ptr< std::thread > data_thread_;            //< Рабочий поток графа
  id2data_graph_objs_type        id2data_graph_objs_;     //< Словарь для поиска объекта по его идентификатору
  mutable obj_ids_type           data_graph_obj_ids_;     //< Идентификаторы объектов в графе
  bool                           req_terminate_thread_;   //< Разделяемый флаг с рабочим потоком, требование завершить работу
  mutable sync_type              ctrl_graph_mtx_;         //< Поле для синрохнизации доступа к объекту графа
  live_ext_requests_type         live_ext_requests_;      //< Счетчик количества требований на обработку внешнего запроса, для разгрузки рабочего потока графа
  ::libs::bufs::Bufs::ptr        work_bufs_;              //< Рабочий буфер для захвата кадров
  arrays_interf_type             interf_objs_;            //<
  array_iinterf_type             source_interf_objs_;     //<
  ::libs::link::ILink::weak_ptr  logger_;                 //< Логгер пути, устанавливается извне
  std::uint64_t                  count_process_frames_;   //< Количество обработанных кадров во время всей работы сеанса графа
  syn::ExpandedTimes             expand_objs_time_;       //< Вспомогательное поле для оценки времени работы конкретных объектов в графе
  syn::ExpandedTimes             exptimes_;               //< Вспомогательное поле для оценки времени работы алгоритмов в объектах графа
  std::string                    data_graph_folder_;      //< Директория с данными графа (xml настройки + события настройки)
};
}   // namespace libs::icore::impl::var1::graph
