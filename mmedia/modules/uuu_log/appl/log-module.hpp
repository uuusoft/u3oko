#pragma once
/**
\file       log-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_log
*/

namespace modules::uuu_log::appl
{
std::string make_suppressor_key (const syn::IEvent::ptr&);
/// Реализация модуля логирования системы
class LogModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  LogModule ();
  virtual ~LogModule () = default;

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)

  //  IApplication overrides
  virtual void init_appl_data_int () override;

  //  BaseModule overrides
  virtual void appl_init_int (const ::libs::link::appl::InitApplication& info) override;
  virtual void init_links_int (const ::libs::link::appl::InitApplication&) override;
  virtual void init_proxys_int () override;
  virtual void init_done_int () override;
  virtual bool appl_deinit_int () override;
  virtual void update_catch_funcs_int () override;

  //  LeafModule overrides
  virtual recv_links_type get_recv_link () override;
  virtual bool            catch_event (syn::IEvent::ptr& evnt) override;
  virtual bool            is_now_thread_to_sleep (bool now_recv_evnt) override;

  void          make_dir_for_logs ();
  void          open_log_file ();
  void          flush_events ();
  void          flush_event (syn::IEvent::ptr&);
  void          delete_folders (const syn::list_folders_type&);
  void          prepare_start ();
  void          check_process ();
  void          add_msg_from_self (const std::string&);
  void          process_info_log (syn::InfoLogEvent::raw_ptr, syn::IEvent::ptr);
  void          process_property_log_module (syn::PropertyLogModuleEvent::raw_ptr);
  void          process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr);
  void          process_list_logs (syn::ProcessListLogsEvent::raw_ptr);
  void          process_log (syn::ProcessLogEvent::raw_ptr);
  std::uint64_t fill_tab (const std::uint64_t len, const std::uint64_t max_count_tabs, const std::uint64_t size_tab);

  syn::events_list_type                events_for_save_;         //< Временно кешированные события для сброса в лог (по таймауту или по достижению предельного размера списка)
  std::string                          path2sessions_;           //< Директория с всеми существующими сеансами
  syn::InfoLogSession::id_session_type active_session_folder_;   //< Имя директории с логами текущего сеанса работы системы
  std::string                          path2logs_;               //< Директория с логами текущего сеанса работы системы
  std::fstream                         file_for_store_events_;   //< Текущий файл с логом
  std::uint64_t                        indx_file_ = 0;           //< Индекс текущего файла с логом
  syn::suppressor_type                 suppressor_;              //< Для подавляния повторных сообщений
};
}   // namespace modules::uuu_log::appl
