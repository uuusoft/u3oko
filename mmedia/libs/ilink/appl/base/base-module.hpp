#pragma once
/**
\file       base-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilink
*/

namespace libs::ilink::appl::base
{
/// Базовая реализация для всех типов модулей (корневых оконечных etc) системы
class BaseModule : public ::libs::link::appl::IApplication
{
  public:
  //  ext types
  using links_type      = ::libs::properties::vers::links::LinksApplication< ::libs::link::ILink::ptr >;
  using recv_links_type = std::list< ::libs::link::ILink::ptr >;

  BaseModule ();
  virtual ~BaseModule () = default;

  protected:
  //  internal typess
  using catch_msg_func_type      = std::function< ::libs::events::IEvent::ptr (::libs::events::IEvent::ptr&, bool, const ::libs::ilink::appl::StateProcessEventExt&) >;
  using list_catch_msg_func_type = std::list< std::pair< catch_msg_func_type, ::libs::events::IEvent::ptr > >;
  using id_msg2func_type         = std::unordered_map< ::libs::events::IEvent::hid_type, catch_msg_func_type >;

  //  ::libs::link::appl::IApplication overrides
  virtual void appl_init_int (const ::libs::link::appl::InitApplication&) override;
  virtual void init_appl_folders_int () override;
  virtual void init_proxys_int () override;
  virtual void init_appl_data_int () override;
  virtual void init_done_int () override;
  virtual void update_catch_funcs_int () override;
  virtual void appl_force_stop_int () override;

  // BaseModule
  /// Функция получения списка связей для входящих событий
  /// \return список связей, по которым будут получаться сообщения в рабочем цикле
  virtual recv_links_type get_recv_link () = 0;

  void load_events_props ();
  void update_events_props ();

  links_type                                                links_;                                                           //< Локальная копия для одновременного доступа через shared_ptr к разделяемым между всей системой интерфейсам
  ::libs::iproperties::appl_paths::IAppPaths::ptr           paths_;                                                           //< Пути к различными ресурсам
  ::libs::optim::mcalls::IMCaller::ptr                      mthreads_;                                                        //<
  ::libs::ilink::appl::EventPropsForApplication             appl_event_props_;                                                //< Стандартные свойства-события системы
  ::libs::helpers::sys::cpu::CpuInfo                        cpu_informer_;                                                    //< Поле для получения свойств CPU
  ::libs::link::ILink::ptr                                  logger_;                                                          //< Логер текущего модуля, может быть null. Настраивается наследниками
  id_msg2func_type                                          catch_funcs_;                                                     //< Функции-обработчики сообщений
  ::libs::ilink::appl::StateProcessEventExt                 current_seq_;                                                     //< Текущий запрос события в обработке, хранит всю runtime информацию события
  ::libs::helpers::sys::ISysInfo::raw_ptr                   sys_info_       = nullptr;                                        //< Свойства програмного окружения
  ::utils::mem_funcs::impl::BlockMemAllocatorProxy::raw_ptr all2mem_        = nullptr;                                        //< Указатель на интерфейс по работе с блоками памяти
  ::utils::dbufs::allocator::BufAllocatorProxy::raw_ptr     all2buf_        = nullptr;                                        //< Указатель на интерфейс по работе с буферами
  ::libs::proxy::IOptimProxy*                               all2optim_      = nullptr;                                        //< Указатель на интерфейс-хранилище оптимизированных алгоритмов
  ::libs::proxy::IEventsProxy*                              all2events_     = nullptr;                                        //< Указатель на интерфейс для создания различнх событий по текстовым идентификаторам
  ::libs::ievents::props::base_id::id_link_type             text_id_module_ = "u3_unkmodule";                                 //< текстовый идентификатор модуля, например для использования в логировании
  bool                                                      stop_module_    = false;                                          //< Флаг завершения работы
  std::int32_t                                              ms_time_sleep_  = ::libs::link::consts::ms_wait_delay_recv_msg;   //< Время засыпания рабочего потока при отсутствии сообщений
};

void register_events_for_module ();
}   // namespace libs::ilink::appl::base
