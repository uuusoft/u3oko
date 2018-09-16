//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       log_module_catch_msg_functs.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "log-module.hpp"

namespace modules { namespace uuu_log { namespace appl {

void
LogModule::update_catch_functs_int ()
{
  super::update_catch_functs_int ();

  catch_functs_[InfoLogEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<InfoLogEvent> (_msg);
        UASSERT (_props);
        process_info_log (_props, _msg);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[mevents::log::PropertyLogModuleEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<mevents::log::PropertyLogModuleEvent> (_msg);
        UASSERT (_props);
        process_property_log_module (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[::libs::ievents::runtime::state::ChangStateProcessTypeEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        auto _props = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::state::ChangStateProcessTypeEvent> (_msg);
        UASSERT (_props);
        proces_change_state_process (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[ProcessListLogsEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("process levents::ProcessListLogsEvent in " << path2sessions_);
        auto _props = ::libs::iproperties::helpers::cast_event<ProcessListLogsEvent> (_msg);
        UASSERT (_props);
        process_list_logs (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };

  catch_functs_[levents::ProcessLogEvent::gen_get_mid ()] = [this](IEvent::ptr _msg, bool _forward) {
    if (_forward)
      {
        XULOG_TRACE ("process levents::ProcessLogEvent in " << path2sessions_);
        auto _props = ::libs::iproperties::helpers::cast_event<levents::ProcessLogEvent> (_msg);
        UASSERT (_props);
        process_log (_props);
        return IEvent::ptr ();
      }
    return _msg;
  };
  return;
}


void
LogModule::process_property_log_module (PropertyLogModuleEvent::raw_ptr _props)
{
  event_props_.module_log_->copy (_props);
  return;
}


void
LogModule::process_info_log (InfoLogEvent::raw_ptr _props, IEvent::ptr _msg)
{
  events_.push_back (_msg);
  return;
}


void
LogModule::proces_change_state_process (ChangStateProcessTypeEvent::raw_ptr _props)
{
  if (!_props->is_start ())
    {
      add_msg_from_self (std::string ("Stop log module"));
      flush_events ();
      stop_module_ = true;
      return;
    }
  add_msg_from_self (std::string ("Start log module"));
  return;
}


void
LogModule::process_list_logs (ProcessListLogsEvent::raw_ptr _props)
{
  const auto _action = _props->get_action ();

  switch (_action)
    {
    case levents::ActionForListLogs::delete_sessions:
      delete_folders (_props->get_sessions ());
      break;
    case levents::ActionForListLogs::get_sessions:
      {
        list_folders_type _folders = helpers::get_sort_by_time_folders (path2sessions_);
        _props->set_sessions (std::move (_folders));
        break;
      }
    default:
      XULOG_ERROR ("unknown type ActionForListLogs, " << to_str (_action));
      break;
    }
  return;
}


void
LogModule::process_log (ProcessLogEvent::raw_ptr _props)
{
  const auto _action = _props->get_action ();

  switch (_action)
    {
    case levents::ActionForProcessLog::get_raw_log:
      {
        const auto        _session      = _props->get_session ();
        const std::string _path2session = ::libs::helpers::files::make_path (path2sessions_, _session);
        const auto        _files        = helpers::get_sort_by_time_files (_path2session);
        auto              _temp_buff    = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ()->alloc (0);
        info_session_type _info;

        for (const auto& _file : _files)
          {
            bfs::path _path2file (::libs::helpers::files::make_path (_path2session, _file));

            if (!::libs::helpers::files::load_file2mem (_path2file.string (), _temp_buff))
              {
                UASSERT_SIGNAL ("failed call ::libs::helpers::files::load_file2mem");
                continue;
              }

            const auto _add_size = _temp_buff->get_data_size ();
            if (!_add_size)
              {
                continue;
              }

            const auto _old_size = _info.data_.size ();
            const auto _new_size = _add_size + _old_size;

            _info.data_.reserve (_new_size);
            std::copy (_temp_buff->get (), _temp_buff->get () + _add_size, std::back_inserter (_info.data_));
            //add_msg_from_self( std::string( "load log file: " + _file + ", _add_size= " + to_str( _add_size ) + ", _info.data_.size=" + to_str( _info.data_.size() ) ) );
          }
        _props->set_log_info (std::move (_info));
        break;
      }
    default:
      UASSERT_SIGNAL ("invalid levents::ActionForProcessLog");
      break;
    }
  return;
}

}}}      // namespace modules::uuu_log::appl
