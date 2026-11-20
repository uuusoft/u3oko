#pragma once
/**
\file       storage-module.hpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
*/

namespace modules::mstorage::appl
{
/// Реализация модуля системы хранения данных
/// Производит:
///   -выбор и загрузку реализаций хранения бинарных данных, индексирования, шифрования, проверки целостности и прочего
///   -проверку пред и пост условий операций
class StorageModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  StorageModule ();
  virtual ~StorageModule () = default;

  private:
  //  internal typess
  U3_ADD_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)
  using runtime_storage_type       = boost::unordered_flat_map< syn::stream_id_type, syn::RuntimeStreamInfo >;
  using access_rights_storage_type = boost::unordered_flat_map< syn::stream_id_type, syn::StreamActions >;

  //  IApplication overrides
  virtual auto init_appl_data_int () -> void override;

  //  BaseModule overrides
  virtual auto appl_init_int (const ::libs::link::appl::InitApplication&) -> void override;
  virtual auto init_links_int (const ::libs::link::appl::InitApplication&) -> void override;
  virtual auto init_proxys_int () -> void override;
  virtual auto init_done_int () -> void override;
  virtual auto appl_deinit_int () -> bool override;
  virtual auto update_catch_funcs_int () -> void override;
  virtual auto get_recv_link_int () -> recv_links_type override;

  //  LeafModule overrides
  virtual auto catch_event_int (::libs::events::IEvent::ptr& evnt) -> bool override;
  virtual auto is_now_thread_to_sleep_int (bool) -> bool override;

  // int functions
  auto create_impls (syn::PropertyStorageModuleEvent::raw_ptr) -> void;
  auto delete_impls () -> void;
  auto sync_status_impls () -> void;
  auto check_access_rights (const syn::stream_id_type&, const syn::StreamActions&) const -> bool;
  auto process_update_stream (syn::UpdateStream::raw_ptr) -> void;
  auto process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr) -> void;
  auto process_write_data (syn::WriteData::raw_ptr) -> void;
  auto process_read_data (syn::ReadData::raw_ptr) -> void;
  auto process_get_runtime_info (syn::GetRuntimeInfo::raw_ptr) -> void;
  auto process_get_statistic_info (syn::GetStatisticInfo::raw_ptr) -> void;
  auto load_binary_statistic () -> void;

  impl::IStorageImpl::ptr    storage_impl_;            //< выбранная реализация хранения бинарных данных
  impl::IIndexerImpl::ptr    indexer_impl_;            //< выбранная реализация индексирования данных
  runtime_storage_type       streams_runtime_infos_;   //< поле сбора статистики использования потоков после старта, т.е. в текущем сеансе
  access_rights_storage_type streams_rights_;          //< поле прав доступа к данным потоков
  runtime_storage_type       streams_infos_;           //< поле отражает статистику использования данных на момент старта
};
}   // namespace modules::mstorage::appl
