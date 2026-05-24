/**
\file       storage-module.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_module_storage
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-storage-includes_int.hpp"
#include "storage-module.hpp"

namespace modules::uuu_storage::appl
{
StorageModule::StorageModule ()
{
  text_id_module_ = ::libs::ilink::consts::id_storage;
}


StorageModule::~StorageModule ()
{
}


void
StorageModule::process_read_data (syn::ReadData::raw_ptr props)
{
  const auto&                           stream_id  = props->get_stream_id ();
  const impl::IStorageImpl::seance_type sstream_id = ::libs::helpers::utils::to_string (stream_id);
  auto                                  int_msg    = props->get_msg ();

  U3_ASSERT (int_msg);
  if (!check_acesss_rights (stream_id, ::libs::istorage_events::StreamActions::read))
  {
    U3_XLOG_WARN ("invalide access rights for read operation " + sstream_id);
    return;
  }

#if 0
  impl::IStorageImpl::id_chunk_type id_bin;
  auto                              buf_props = ::libs::iproperties::helpers::cast_event< ::libs::ievents::runtime::mem::BuffEvent > (int_msg);
  std::int64_t                      size_data  = (*buf_props->get_buf ())[::utils::dbufs::MemVars::size_data];

  storage_impl_->load (sstream_id, buf_props->get_buf ()->getraw_buf ().get ());

  if (props->is_failed ())
  {
    ++streams_runtime_infos_[stream_id].count_errors_;
  }
  else
  {
    U3_ASSERT (size_data > 0);
    streams_runtime_infos_[stream_id].count_read_bytes_ += size_data;
  }
#endif
}


void
StorageModule::process_write_data (syn::WriteData::raw_ptr props)
{
  const auto&                           stream_id  = props->get_stream_id ();
  const impl::IStorageImpl::seance_type sstream_id = ::libs::helpers::utils::to_string (stream_id);
  auto                                  int_msg    = props->get_msg ();

  U3_ASSERT (int_msg);
  if (!check_acesss_rights (stream_id, ::libs::istorage_events::StreamActions::write))
  {
    U3_LOG_STORAGE_WRN ("invalid access rights for write operation " + sstream_id);
    return;
  }

  std::int64_t                      size_data = 0;
  impl::IStorageImpl::id_chunk_type id_bin;

  if (auto buf_gen_props = ::libs::iproperties::helpers::cast_event< ::libs::ievents::runtime::mem::BuffEvent > (int_msg))
  {
    id_bin    = storage_impl_->save (sstream_id, buf_gen_props->get_buf ().get ());
    size_data = (*buf_gen_props->get_buf ())[::utils::dbufs::MemVars::size_data];
  }
  else if (auto buf_zip_props = ::libs::iproperties::helpers::cast_event< ::libs::ievents::runtime::mem::ZipDataEvent > (int_msg))
  {
    id_bin    = storage_impl_->save (sstream_id, &buf_zip_props->get_zip ()[0], buf_zip_props->get_size ());
    size_data = buf_zip_props->get_size ();
  }
  else
  {
    U3_ASSERT_SIGNAL ("unknown type write data" + TOLOG (int_msg->get_mid ()));
    return;
  }

  if (props->is_failed ())
  {
    ++streams_runtime_infos_[stream_id].count_errors_;
  }
  else
  {
    U3_ASSERT (size_data > 0);
    streams_runtime_infos_[stream_id].count_write_bytes_ += size_data;
  }
}


void
StorageModule::process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr props)
{
  stop_module_ = props->is_start () ? false : true;
  sync_status_impls ();
  streams_runtime_infos_.clear ();
  streams_rights_.clear ();

  if (props->is_start ())
  {
    load_binary_statistic ();
  }
}


void
StorageModule::process_update_stream (syn::UpdateStream::raw_ptr props)
{
  switch (props->action_)
  {
  case ::libs::istorage_events::StreamUpdates::open:
    U3_ASSERT (props->stream_id_.empty ());
    break;
  case ::libs::istorage_events::StreamUpdates::close:
    U3_ASSERT (!props->stream_id_.empty ());
    streams_rights_.erase (props->stream_id_);
    break;
  case ::libs::istorage_events::StreamUpdates::change:
  case ::libs::istorage_events::StreamUpdates::check_and_get_info:
    U3_ASSERT (!props->stream_id_.empty ());
    break;
  default:
    U3_XLOG_ERROR ("find action stream " + to_string (props->action_));
    break;
  }

  indexer_impl_->update_stream (props);

  switch (props->action_)
  {
  case ::libs::istorage_events::StreamUpdates::open:
    U3_ASSERT (streams_rights_.end () == streams_rights_.find (props->stream_id_));
    U3_ASSERT (!props->stream_id_.empty ());
    streams_rights_[props->stream_id_] = props->operation_;

    break;
  case ::libs::istorage_events::StreamUpdates::close:
    break;
  case ::libs::istorage_events::StreamUpdates::change:
  case ::libs::istorage_events::StreamUpdates::check_and_get_info:
    U3_ASSERT (streams_rights_.end () != streams_rights_.find (props->stream_id_));
    break;
  default:
    U3_XLOG_ERROR ("find action stream " + to_string (props->action_));
    break;
  }
}


void
StorageModule::process_get_runtime_info (syn::GetRuntimeInfo::raw_ptr props)
{
  auto& res = props->stream_infos_;

  res.clear ();
  res.reserve (streams_runtime_infos_.size ());

  for (const auto& stream : streams_runtime_infos_)
  {
    res.push_back (stream.second);
  }
}


void
StorageModule::process_get_statistic_info (syn::GetStatisticInfo::raw_ptr props)
{
  auto& all_size = props->use_size_;

  all_size = 0;

  for (const auto& stream : streams_runtime_infos_)
  {
    all_size += stream.second.count_write_bytes_;
  }
  for (const auto& stream : streams_infos_)
  {
    all_size += stream.second.count_write_bytes_;
  }
}
void
StorageModule::sync_status_impls ()
{
  const auto status = stop_module_ ? appl::impl::ImplRuns::stop : appl::impl::ImplRuns::run;

  if (storage_impl_)
  {
    storage_impl_->change_state (status);
  }
  if (indexer_impl_)
  {
    indexer_impl_->change_state (status);
  }
}


void
StorageModule::create_impls (syn::PropertyStorageModuleEvent::raw_ptr props)
{
  storage_impl_ = storage_impl_ ? storage_impl_ : get_storage_impl ();
  indexer_impl_ = indexer_impl_ ? indexer_impl_ : get_indexer_impl ();

  indexer_impl_->set_info (props->get_paths ().empty () ? nullptr : &props->get_paths ().front ());
  storage_impl_->set_info (props->get_paths ().empty () ? nullptr : &props->get_paths ().front ());
}


bool
StorageModule::check_acesss_rights (
  const ::libs::istorage_events::stream_id_type& id,
  const ::libs::istorage_events::StreamActions&  op) const
{
  auto find = streams_rights_.find (id);
  if (streams_rights_.end () == find)
  {
    U3_XLOG_ERROR ("find stream for check access rights");
    return false;
  }
  return op == find->second;
}


void
StorageModule::load_binary_statistic ()
{
  if (!storage_impl_)
  {
    return;
  }

  impl::IStorageImpl::ids_chunk_type ids;
  U3_ASSERT_SIGNAL ("StorageModule::load_binary_statistic: umimplemented");

#if 0
  storage_impl_->get_all_ids (ids);
  auto lock = storage_impl_->lock_ids (ids);
  storage_impl_->get_info_ids (lock);
  storage_impl_->unlock_ids (lock);
#endif
}
}   // namespace modules::uuu_storage::appl
