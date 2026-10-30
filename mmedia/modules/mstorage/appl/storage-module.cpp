/**
\file       storage-module.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../module-storage-includes_int.hpp"
#include "storage-module.hpp"

namespace modules::mstorage::appl
{
StorageModule::StorageModule ()
{
  text_id_module_ = ::libs::ilink::consts::id_storage;
}


void
StorageModule::process_read_data (syn::ReadData::raw_ptr props)
{
  const auto&                           stream_id  = props->get_stream_id ();
  const impl::IStorageImpl::seance_type sstream_id = ::libs::utility::utils::to_string (stream_id);
  auto                                  int_msg    = props->get_msg ();

  ::libs::utility::checks::throw_ifn ((bool) int_msg);
  if (!check_access_rights (stream_id, syn::StreamActions::read))
  {
    U3_XLOG_WARN ("invalide access rights for read operation " + sstream_id);
    return;
  }

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  impl::IStorageImpl::id_chunk_type id_bin;

  auto*        buf_props = ::libs::iproperties::helpers::cast_event< syn::BuffEvent > (int_msg);
  std::int64_t size_data = (*buf_props->get_buf ())[::utils::dbufs::MemVars::size_data];

  storage_impl_->load (sstream_id, buf_props->get_buf ()->get_block ().get ());

  if (props->is_failed ())
  {
    ++streams_runtime_infos_[stream_id].count_errors_;
  }
  else
  {
    ::libs::utility::checks::throw_ifn (size_data > 0);
    streams_runtime_infos_[stream_id].count_read_bytes_ += size_data;
  }
#endif
}


void
StorageModule::process_write_data (syn::WriteData::raw_ptr props)
{
  const auto&                           stream_id  = props->get_stream_id ();
  const impl::IStorageImpl::seance_type sstream_id = ::libs::utility::utils::to_string (stream_id);
  auto                                  int_msg    = props->get_msg ();

  ::libs::utility::checks::throw_ifn ((bool) int_msg);
  if (!check_access_rights (stream_id, syn::StreamActions::write))
  {
    U3_LOG_STORAGE_WRN ("invalid access rights for write operation " + sstream_id);
    return;
  }

  std::int64_t                      size_data = 0;
  impl::IStorageImpl::id_chunk_type id_bin;

  if (auto* buf_gen_props = ::libs::iproperties::helpers::cast_event< syn::BuffEvent > (int_msg))
  {
    id_bin    = storage_impl_->save (sstream_id, buf_gen_props->get_buf ().get ());
    size_data = (*buf_gen_props->get_buf ())[::utils::dbufs::MemVars::size_data];
  }
  else if (auto* buf_zip_props = ::libs::iproperties::helpers::cast_event< syn::ZipDataEvent > (int_msg))
  {
    id_bin    = storage_impl_->save (sstream_id, &buf_zip_props->get_zip ()[0], buf_zip_props->get_size ());
    size_data = buf_zip_props->get_size ();
  }
  else
  {
    ::libs::utility::checks::throw_exception ("unknown type write data" + STOLOG (int_msg->get_mid ()));
    return;
  }

  if (props->is_failed ())
  {
    ++streams_runtime_infos_[stream_id].count_errors_;
  }
  else
  {
    ::libs::utility::checks::throw_ifn (size_data > 0);
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
  case ::libs::events_storage::StreamUpdates::open:
    ::libs::utility::checks::throw_ifn (props->stream_id_.empty ());
    break;
  case ::libs::events_storage::StreamUpdates::close:
    ::libs::utility::checks::assert_soft (!props->stream_id_.empty (), "stream_id empty");
    streams_rights_.erase (props->stream_id_);
    break;
  case ::libs::events_storage::StreamUpdates::change:
  case ::libs::events_storage::StreamUpdates::check_and_get_info:
    ::libs::utility::checks::throw_ifn (!props->stream_id_.empty ());
    break;
  default:
    U3_XLOG_ERROR ("find action stream " + to_string (props->action_));
    break;
  }

  indexer_impl_->update_stream (props);

  switch (props->action_)
  {
  case ::libs::events_storage::StreamUpdates::open:
    ::libs::utility::checks::throw_ifn (streams_rights_.end () == streams_rights_.find (props->stream_id_));
    ::libs::utility::checks::throw_ifn (!props->stream_id_.empty ());
    streams_rights_[props->stream_id_] = props->operation_;
    break;
  case ::libs::events_storage::StreamUpdates::close:
    break;
  case ::libs::events_storage::StreamUpdates::change:
  case ::libs::events_storage::StreamUpdates::check_and_get_info:
    ::libs::utility::checks::throw_ifn (streams_rights_.end () != streams_rights_.find (props->stream_id_));
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


auto
StorageModule::check_access_rights (const syn::stream_id_type& id, const syn::StreamActions& op) const -> bool
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
  ::libs::utility::checks::throw_exception ("StorageModule::load_binary_statistic: umimplemented");

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  storage_impl_->get_all_ids (ids);
  auto lock = storage_impl_->lock_ids (ids);
  storage_impl_->get_info_ids (lock);
  storage_impl_->unlock_ids (lock);
#endif
}
}   // namespace modules::mstorage::appl
