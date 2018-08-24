#pragma once
/**
\file       base-module.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace appl { namespace base {
/**
  \brief  Базовая реализация для всех типов модулей (корневых оконечных и т.п.) системы.
  */
class BaseModule : public ::libs::link::appl::IApplication
{
  public:
  //  ext types
  using links_type      = ::libs::properties::vers::links::LinksApplication<::libs::link::ILink::ptr>;
  using recv_links_type = std::list<ILink::ptr>;

  BaseModule ();

  virtual ~BaseModule ();


  protected:
  //  int types
  using catch_msg_funct_type      = std::function<IEvent::ptr (IEvent::ptr _msg, bool _forward)>;
  using list_catch_msg_funct_type = std::list<std::pair<catch_msg_funct_type, IEvent::ptr>>;
  using id_msg2funct_type         = std::unordered_map<IEvent::text_id_type, catch_msg_funct_type>;

  //  ::libs::link::appl::IApplication impl
  virtual void init_int (const ::libs::link::appl::InitApplication& _info) override;
  virtual void init_appl_folders_int () override;
  virtual void init_proxys_int () override;
  virtual void init_appl_data_int () override;
  virtual void init_done_int () override;
  virtual void update_catch_functs_int () override;
  /**
    \brief  Функция получения списка связей для входящих событий.
    \return список связей, по которым будут получаться сообщения в рабочем цикле.
    */
  virtual recv_links_type get_recv_link () = 0;

  void load_events_props ();

  void update_events_props ();

  links_type                      links_;               //< Локальная копия для одновременного доступа через shared_ptr к разделяемым между всей системой интерфейсам.
  IAppPaths::ptr                  paths_;               //< Пути к различными ресурсам.
  ISysInfo::raw_ptr               sys_info_;            //< Свойства програмного окружения.
  EventPropsForApplication        event_props_;         //< Стандартные свойства-события системы.
  std::string                     name_company_;        //< Имя компании приложения.
  std::string                     name_appl_;           //< Имя приложения.
  std::string                     txt_ver_;             //< ???
  CpuInfo                         cpu_informer_;        //< Поле для получения свойств CPU.
  BlockMemAllocatorProxy::raw_ptr all2mem_;             //< Указатель на интерфейс по работе с блоками памяти.
  BuffAllocatorProxy::raw_ptr     all2buff_;            //< Указатель на интерфейс по работе с буферами.
  IOptimProxy::raw_ptr            all2optim_;           //< Указатель на интерфейс-хранилище оптимизированных алгоритмов.
  IEventsProxy::raw_ptr           all2events_;          //< Указатель на интерфейс для создания различнх событий по текстовым идентификаторам.
  id_msg2funct_type               catch_functs_;        //< Функции-обработчики сообщений.
  StateProcessEventExt            current_seq_;         //< Текущий запрос в обработке.
  int                             ms_time_sleep_;       //< Время засыпания рабочего потока при отсутствии сообщений.
  consts::id_link_module_type     text_id_module_;      //< текстовый идентификатор модуля, например для использования в логировании.
  bool                            stop_module_;         //< Флаг завершения работы
  ::libs::link::ILink::ptr        logger_;              //< Логер текущего модуля, может быть null. Настраивается наследниками.
  //seq2process_type              seqs_;  //< Запросы в процессе обработки.
};
/**
  \brief  
  */
inline void
register_events_for_module ()
{
  ::libs::events::register_events_in_archives ();
  ::libs::ievents::register_events_in_archives ();
  ::libs::ilog_events::events::register_events_in_archives ();
  ::libs::ievents_events::events::register_events_in_archives ();
  ::libs::igui_events::events::register_events_in_archives ();
  ::libs::imdata_events::events::register_events_in_archives ();
  ::libs::ihttp_events::events::register_events_in_archives ();
  ::libs::istorage_events::events::register_events_in_archives ();
  return;
}

}}}}      // namespace libs::ilink::appl::base
