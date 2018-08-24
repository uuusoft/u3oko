//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       storage-module-catch-msg-functs.cpp
\date       23.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "storage-module.hpp"

namespace modules { namespace uuu_storage { namespace appl {

void
StorageModule::update_catch_functs_int ()
{
  super::update_catch_functs_int ();

  catch_functs_[PropertyStorageModuleEvent::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("received PropertyStorageModuleEvent");
        auto _props = ::libs::iproperties::helpers::cast_event<mevents::storage::PropertyStorageModuleEvent> (_msg);
        event_props_.storage_module_->copy (_props);
        create_impls (_props);
        sync_status_impls ();
        load_binary_statistic ();
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[MemResourceStorageEvent::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("received MemResourceStorageEvent");
        UASSERT_SIGNAL ("unimplemented");
        auto _props = ::libs::iproperties::helpers::cast_event<MemResourceStorageEvent> (_msg);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[GetRuntimeInfo::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("received GetRuntimeInfo");
        auto _props = ::libs::iproperties::helpers::cast_event<GetRuntimeInfo> (_msg);
        UASSERT (_props);
        process_get_runtime_info (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[GetObjects::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("received GetObjects");
        auto _props = ::libs::iproperties::helpers::cast_event<GetObjects> (_msg);
        UASSERT (_props);
        indexer_impl_->get_objects (_props->objs_);
        //path_id_type id_path_;      //< Идентификатор пути.
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[GetStatisticInfo::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("received GetStatisticInfo");
        UASSERT_SIGNAL ("unimplemented");
        auto _props = ::libs::iproperties::helpers::cast_event<GetStatisticInfo> (_msg);
        UASSERT (_props);
        process_get_statistic_info (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[ReadData::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("received ReadData");
        auto _props = ::libs::iproperties::helpers::cast_event<ReadData> (_msg);
        process_read_data (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[WriteData::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<WriteData> (_msg);
        UASSERT (_props);
        process_write_data (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[UpdateStream::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TEST ("received UpdateStream");
        auto _props = ::libs::iproperties::helpers::cast_event<UpdateStream> (_msg);
        UASSERT (_props);
        process_update_stream (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[::libs::ievents::runtime::state::ChangStateProcessTypeEvent::gen_get_type_text_id ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("received ChangStateProcessTypeEvent");
        auto _props = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_msg);
        UASSERT (_props);
        process_change_state_process (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  return;
}


void
StorageModule::process_read_data (ReadData::raw_ptr _props)
{
  const auto&                                   _stream_id  = _props->get_stream_id ();
  const impl::IStorageImpl::info_about_mem_type _sstream_id = _stream_id.name ();
  auto                                          _int_msg    = _props->get_msg ();
  XULOG_TEST ("received ReadData event, stream_id=" << _sstream_id);
  UASSERT (_int_msg);

  if (!check_acesss_rights (_stream_id, TypeActionStream::read))
    {
      XULOG_WARNING ("invalide acess rights for read operation, " << _sstream_id);
      return;
    }

  impl::IStorageImpl::id_chunk_type _id_bin;
  auto                              _buff_props = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::mem::BuffEvent> (_int_msg);
  signed long long                  _size_data  = (*_buff_props->get_buff ())[::utils::dbuffs::TypeMemVar::size_data];

  storage_impl_->load (_sstream_id, _buff_props->get_buff ()->get_raw_buff ().get ());

  if (_props->is_failed ())
    {
      ++streams_runtime_infos_[_stream_id].count_errors_;
    }
  else
    {
      UASSERT (_size_data > 0);
      streams_runtime_infos_[_stream_id].count_read_bytes_ += _size_data;
    }
  return;
}


void
StorageModule::process_write_data (WriteData::raw_ptr _props)
{
  const auto&                                   _stream_id  = _props->get_stream_id ();
  const impl::IStorageImpl::info_about_mem_type _sstream_id = _stream_id.name ();
  auto                                          _int_msg    = _props->get_msg ();
  XULOG_TEST ("received WriteData event, stream_id=" << _sstream_id);
  UASSERT (_int_msg);

  if (!check_acesss_rights (_stream_id, TypeActionStream::write))
    {
      XULOG_WARNING ("invalide acess rights for write operation, " << _sstream_id);
      return;
    }

  signed long long                  _size_data = 0;
  impl::IStorageImpl::id_chunk_type _id_bin;

  if (auto _buff_props = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::mem::BuffEvent> (_int_msg))
    {
      _id_bin    = storage_impl_->save (_sstream_id, _buff_props->get_buff ().get ());
      _size_data = (*_buff_props->get_buff ())[::utils::dbuffs::TypeMemVar::size_data];
    }
  else if (auto _buff_props = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::mem::ZipDataEvent> (_int_msg))
    {
      _id_bin    = storage_impl_->save (_sstream_id, &_buff_props->get_zip ()[0], _buff_props->get_size ());
      _size_data = _buff_props->get_size ();
    }
  else
    {
      UASSERT_SIGNAL ("unknown type write data, " << _int_msg->get_mid ());
      return;
    }

  if (_props->is_failed ())
    {
      ++streams_runtime_infos_[_stream_id].count_errors_;
    }
  else
    {
      UASSERT (_size_data > 0);
      streams_runtime_infos_[_stream_id].count_write_bytes_ += _size_data;
    }
  return;
}


void
StorageModule::process_change_state_process (::libs::ievents::runtime::state::ChangStateProcessTypeEvent::raw_ptr _props)
{
  stop_module_ = _props->is_start () ? false : true;
  sync_status_impls ();
  streams_runtime_infos_.clear ();      // Статистику отчищаем.
  streams_rights_.clear ();

  if (_props->is_start ())
    {
      load_binary_statistic ();
    }
  return;
}


void
StorageModule::process_update_stream (UpdateStream::raw_ptr _props)
{
  switch (_props->action_)
    {
    case TypeUpdateStream::open:
      UASSERT (_props->stream_id_.empty ());
      break;
    case TypeUpdateStream::close:
      UASSERT (!_props->stream_id_.empty ());
      streams_rights_.erase (_props->stream_id_);
      break;
    case TypeUpdateStream::change:
    case TypeUpdateStream::check_and_get_info:
      UASSERT (!_props->stream_id_.empty ());
      break;
    default:
      XULOG_ERROR ("failed find action stream, " << to_str (_props->action_));
      break;
    }

  indexer_impl_->update_stream (_props);

  switch (_props->action_)
    {
    case TypeUpdateStream::open:
      UASSERT (streams_rights_.end () == streams_rights_.find (_props->stream_id_));
      UASSERT (!_props->stream_id_.empty ());
      streams_rights_[_props->stream_id_] = _props->operation_;
      XULOG_TEST ("set rights for " << _props->stream_id_.name () << "=" << to_str (_props->operation_));
      break;
    case TypeUpdateStream::close:
      break;
    case TypeUpdateStream::change:
    case TypeUpdateStream::check_and_get_info:
      UASSERT (streams_rights_.end () != streams_rights_.find (_props->stream_id_));
      break;
    default:
      XULOG_ERROR ("failed find action stream, " << to_str (_props->action_));
      break;
    }
  return;
}


void
StorageModule::process_get_runtime_info (GetRuntimeInfo::raw_ptr _props)
{
  auto& _res = _props->stream_infos_;

  _res.clear ();
  _res.reserve (streams_runtime_infos_.size ());

  for (const auto& _stream : streams_runtime_infos_)
    {
      _res.push_back (_stream.second);
    }
  //path_id_type id_path_;      //< Идентификатор пути.
  return;
}


void
StorageModule::process_get_statistic_info (GetStatisticInfo::raw_ptr _props)
{
  auto& _all_size = _props->use_size_;
  _all_size       = 0;

  for (const auto& _stream : streams_runtime_infos_)
    {
      _all_size += _stream.second.count_write_bytes_;
    }

  for (const auto& _stream : streams_infos_)
    {
      _all_size += _stream.second.count_write_bytes_;
    }
  return;
}

}}}      // namespace modules::uuu_storage::appl
