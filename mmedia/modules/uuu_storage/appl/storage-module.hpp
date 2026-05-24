#pragma once
/**
\file       storage-module.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl
{
/// Реализация модуля системы хранения данных
/// Производит:
///   -выбор и загрузку реализаций хранения бинарных данных, индексирования, шифрования, проверки целостности и прочего
///   -проверку пред и пост условий операций
class StorageModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  StorageModule ();
  virtual ~StorageModule ();

  private:
  //  internal typess
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule)
  using runtime_storage_type       = std::unordered_map< ::libs::istorage_events::stream_id_type, ::libs::istorage_events::events::RuntimeStreamInfo >;
  using access_rights_storage_type = std::unordered_map< ::libs::istorage_events::stream_id_type, ::libs::istorage_events::StreamActions >;

  //  IApplication overrides
  virtual void init_appl_data_int () override;

  //  BaseModule overrides
  virtual void appl_init_int (const ::libs::link::appl::InitApplication& info) override;
  virtual void init_links_int (const ::libs::link::appl::InitApplication& info) override;
  virtual void init_proxys_int () override;
  virtual void init_done_int () override;
  virtual bool appl_deinit_int () override;
  virtual void update_catch_funcs_int () override;

  //  LeafModule overrides
  virtual recv_links_type get_recv_link () override;
  virtual bool            catch_event (::libs::events::IEvent::ptr& evnt) override;
  virtual bool            is_now_thread_to_sleep (bool now_recv_evnt) override;

  // int functions
  void sync_status_impls ();
  void create_impls (syn::PropertyStorageModuleEvent::raw_ptr);
  bool check_acesss_rights (const ::libs::istorage_events::stream_id_type& id, const ::libs::istorage_events::StreamActions& op) const;
  void process_update_stream (syn::UpdateStream::raw_ptr props);
  void process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr props);
  void process_write_data (syn::WriteData::raw_ptr props);
  void process_read_data (syn::ReadData::raw_ptr props);
  void process_get_runtime_info (syn::GetRuntimeInfo::raw_ptr props);
  void process_get_statistic_info (syn::GetStatisticInfo::raw_ptr props);
  void load_binary_statistic ();

  impl::IStorageImpl::ptr    storage_impl_;            //< Выбранная реализация хранения бинарных данных
  impl::IIndexerImpl::ptr    indexer_impl_;            //< Выбранная реализация индексирования данных
  runtime_storage_type       streams_runtime_infos_;   //< Поле сбора статистики использования потоков после старта, т.е. в текущем сеансе
  access_rights_storage_type streams_rights_;          //< Поле прав доступа к данным потоков
  runtime_storage_type       streams_infos_;           //< Поле отражает статистику использования данных на момент старта
};
}   // namespace modules::uuu_storage::appl
