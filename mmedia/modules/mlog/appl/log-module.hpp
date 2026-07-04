#pragma once
/**
\file       log-module.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mlog
*/

namespace modules::mlog::appl
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
  U3_ADD_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)

  //  IApplication overrides
  virtual auto init_appl_data_int () -> void override;

  //  BaseModule overrides
  virtual auto appl_init_int (const ::libs::link::appl::InitApplication& info) -> void override;
  virtual auto init_links_int (const ::libs::link::appl::InitApplication&) -> void override;
  virtual auto init_proxys_int () -> void override;
  virtual auto init_done_int () -> void override;
  virtual auto appl_deinit_int () -> bool override;
  virtual auto update_catch_funcs_int () -> void override;
  virtual auto get_recv_link_int () -> recv_links_type override;

  //  LeafModule overrides
  virtual auto catch_event_int (syn::IEvent::ptr& evnt) -> bool override;
  virtual auto is_now_thread_to_sleep_int (bool now_recv_evnt) -> bool override;

  auto make_dir_for_logs () -> void;
  auto open_log_file () -> void;
  auto flush_events () -> void;
  auto flush_event (syn::IEvent::ptr&) -> void;
  auto delete_folders (const syn::list_folders_type&) -> void;
  auto prepare_start () -> void;
  auto check_process () -> void;
  auto add_msg_from_self (const std::string&) -> void;
  auto process_info_log (syn::InfoLogEvent::raw_ptr, const syn::IEvent::ptr&) -> void;
  auto process_property_log_module (syn::PropertyLogModuleEvent::raw_ptr) -> void;
  auto process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr) -> void;
  auto process_list_logs (syn::ProcessListLogsEvent::raw_ptr) -> void;
  auto process_log (syn::ProcessLogEvent::raw_ptr) -> void;
  auto fill_tab (const std::uint64_t len, const std::uint64_t max_count_tabs, const std::uint64_t size_tab) -> std::uint64_t;

  syn::events_list_type                events_for_save_;         //< Временно кешированные события для сброса в лог (по таймауту или по достижению предельного размера списка)
  std::string                          path2sessions_;           //< Директория с всеми существующими сеансами
  syn::InfoLogSession::id_session_type active_session_folder_;   //< Имя директории с логами текущего сеанса работы системы
  std::string                          path2logs_;               //< Директория с логами текущего сеанса работы системы
  std::fstream                         file_for_store_events_;   //< Текущий файл с логом
  std::uint64_t                        indx_file_ = 0;           //< Индекс текущего файла с логом
  syn::suppressor_type                 suppressor_;              //< Для подавляния повторных сообщений
};
}   // namespace modules::mlog::appl
