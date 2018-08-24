#pragma once
/**
\file       path.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       22.12.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Объявление реализации графа обработки данных в локальном режиме.
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace path {
/**
  \brief  Реализация граф обработки данных в локальном режиме.
  */
class Path : public core::path::IPath
{
  public:
  Path ();

  virtual ~Path ();

  void thread_funct_impl (std::size_t _indx_thread);

  void thread_postfunct_impl ();


  private:
  //  int types
  using path_obj_type      = ::libs::icore::impl::var1::obj::IPathObjExt;
  using array_id_objs_type = core::path::IPath::array_id_objs_type;
  using array_interf_type  = std::array<path_obj_type::ptr, path::consts::max_count_objs>;
  using arrays_interf_type = std::array<array_interf_type, path::consts::max_helper_objs>;
  using array_iinterf_type = std::array<int, path::consts::max_helper_objs>;
  using sync_type          = std::mutex;
  using guard_type         = std::lock_guard<sync_type>;
  using id2obj_type        = std::map<PathObjID, path_obj_type::ptr>;
  using events_type        = obj::dll::TransformInfo::events_type;

  //  IPath impl
  virtual void                      load_int (const std::string& xml_file) override;
  virtual const array_id_objs_type& get_objs_int () const override;
  virtual void                      send_event2obj_int (const PathObjID& _id_obj, events::IEvent::ptr& _evnt) override;
  virtual void                      set_logger_int (::libs::link::ILink::weak_ptr _ptr) override;

  void load_impl (const base_functs::xml::itn& root);

  void connect_impl (const base_functs::xml::itn& _pt);

  void clear_impl ();

  void deb_load_objs_impl ();
  /**
    \brief  Функция обработки буферов /захват, передача по цепочки фильтров, возврат/.
    \return true, если при ее вызове был обработан хотя бы один буфер, иначе false.
    */
  bool process_impl ();

  void change_objs_state_impl (const obj::RunStateFilter& _state);

  void work_funct_impl (
    var1::obj::ObjPath*        _pfilter,
    ::libs::buffs::Buffs::ptr& _pbuffs,
    const unsigned int         _iindx,
    events_type*               _frame_events);
  /**
    \brief      Функция обработки особо важных событий для графа.
    \param[in]  _evnt событие
    \param[in]  _funct  функция-решения, предоставленная клиентом.
    \return     true, если обработка сообщения завершена.
    */
  bool recv_special_event_impl (const events::IEvent::ptr& _evnt);
  /**
    \brief      Функция возращает по идентификатору объект графа.
    \param[in]  _obj_id событие
    \return     объект или empty.
    */
  path_obj_type::weak_ptr get_obj_impl (const PathObjID& _obj_id);
  /**
    \brief    Функция синхронизации идентификаторов объектов после загрузки из xml.
    */
  void refresh_id_objs_impl () const;

  obj::RunStateFilter           state_;                     //< Состояние графа с точки зрения запуска.
  std::unique_ptr<std::thread>  data_thread_;               //< Рабочий поток графа.
  id2obj_type                   id2obj_;                    //< Словарь для поиска объекта по его идентификатору.
  mutable array_id_objs_type    id_objs_;                   //< Идентификаторы объектов в графе.
  bool                          req_terminate_thread_;      //< Разделяемый флаг с рабочим потоком, требование завершить работу.
  mutable sync_type             ctrl_mtx_;                  //< Поле для синрохнизации доступа к объекту графа.
  long long                     count_process_frames_;      //< Количество обработанных кадров во время всей работы сеанса графа.
  ExpandedTimeStatistic         expand_objs_time_;          //< Вспомогательное поле для оценки времени работы конкретных объектов в графе.
  ::libs::buffs::Buffs::ptr     work_buffs_;                //< Рабочий буфер для захвата кадров.
  arrays_interf_type            interf_objs_;               //< ???
  array_iinterf_type            source_interf_objs_;        //< ???
  pugi::xml_document            xml_path_;                  //< XML который использовался для построения графа в последний раз.
  ::libs::link::ILink::weak_ptr logger_;                    //< Логгер пути, устанавливается извне.
};

}}}}}      // namespace libs::icore::impl::var1::path
