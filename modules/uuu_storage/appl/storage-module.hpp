#pragma once
/**
\file       storage-module.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       23.07.2018
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/

namespace modules { namespace uuu_storage { namespace appl {
/**
\brief  Реализация модуля системы хранения данных.
        Производит:
        -выбор и загрузку реализаций хранения бинарных данных, индексирования, шифрования, проверки целостности и прочего
        -проверку пред и пост условий операций
*/
class StorageModule final : public ::libs::ilink::appl::leaf::LeafModule
{
  public:
  StorageModule ();

  virtual ~StorageModule ();


  private:
  //  int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::ilink::appl::leaf::LeafModule);
  using runtime_storage_type       = std::unordered_map<stream_id_type, RuntimeStreamInfo>;
  using access_rights_storage_type = std::unordered_map<stream_id_type, TypeActionStream>;

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

  void sync_status_impls ();

  void create_impls (mevents::storage::PropertyStorageModuleEvent::raw_ptr);

  bool check_acesss_rights (const stream_id_type& _id, const TypeActionStream& _op) const;

  void process_update_stream (UpdateStream::raw_ptr _props);

  void process_change_state_process (::libs::ievents::runtime::state::ChangStateProcessTypeEvent::raw_ptr _props);

  void process_write_data (WriteData::raw_ptr _props);

  void process_read_data (ReadData::raw_ptr _props);

  void process_get_runtime_info (GetRuntimeInfo::raw_ptr _props);

  void process_get_statistic_info (GetStatisticInfo::raw_ptr _props);

  void load_binary_statistic();

  impl::IStorageImpl::ptr    storage_impl_;               //< Выбранная реализация хранения бинарных данных.
  impl::IIndexerImpl::ptr    indexer_impl_;               //< Выбранная реализация индексирования данных.
  runtime_storage_type       streams_runtime_infos_;      //< Поле сбора статистики использования потоков после старта, т.е. в текущем сеансе.
  access_rights_storage_type streams_rights_;             //< Поле прав доступа к данным потоков.
  runtime_storage_type       streams_infos_;              //< Поле отражает статистику использования данных на момент старта.
};

}}}      // namespace modules::uuu_storage::appl
