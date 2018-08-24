#pragma once
/**
\file       log-module.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      empty brief
*/

namespace modules { namespace uuu_log { namespace appl {
/**
  \brief  Реализация модуля логирования системы.
  */
class LogModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  LogModule ();

  virtual ~LogModule ();


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule);

  //  BaseModule overrides
  virtual void init_int (const ::libs::link::appl::InitApplication& _info) override;
  virtual void init_links_int (const ::libs::link::appl::InitApplication& _info) override;
  virtual void init_proxys_int () override;
  virtual void init_done_int () override;
  virtual bool deinit_int () override;
  virtual void update_catch_functs_int () override;

  //  LeafModule overrides
  virtual recv_links_type get_recv_link () override;
  virtual bool            catch_event (IEvent::ptr _evnt) override;
  virtual bool            is_now_sleep_thread (bool _now_recv_evnt) override;

  void make_dir_for_logs ();

  void open_log_file ();

  void flush_events ();

  void flush_event (::libs::events::IEvent::ptr& _evnt);

  void delete_folders (const list_folders_type& _folders);

  void prepare_start ();

  std::size_t fill_tab (const std::size_t _len, const std::size_t _max_count_tabs, const std::size_t _size_tab);

  void check_process ();

  void add_msg_from_self (const std::string& _info);

  void process_info_log( InfoLogEvent::raw_ptr,IEvent::ptr _msg);

  void process_property_log_module( PropertyLogModuleEvent::raw_ptr);

  void proces_change_state_process( ChangStateProcessTypeEvent::raw_ptr);

  void process_list_logs( ProcessListLogsEvent::raw_ptr);

  void process_log( ProcessLogEvent::raw_ptr);

  events_list_type events_;                           //< Временно кешированные события для сброса в лог (по таймауту или по достижению предельного размера списка).
  std::string      path2sessions_;                    //< Директория с сеансами логирования.
  std::string      name_folder_current_session_;      //< Имя директрии с логами текущего сеанса работы системы.
  std::string      path2logs_;                        //< Директория с логами текущего сеанса работы системы.
  std::fstream     file_;                             //< Текущий файл с логом.
  std::size_t      indx_file_;                        //< Индекс текущего файла с логом.
};

}}}      // namespace modules::uuu_log::appl
