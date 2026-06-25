/**
\file       log_module.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mlog
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-log-includes_int.hpp"
#include "log-module.hpp"

namespace modules::mlog::appl
{
std::string
make_suppressor_key (const syn::IEvent::ptr& val)
{
  auto       evnt = ::libs::helpers::check::ptr (::libs::iproperties::helpers::cast_event< syn::InfoLogEvent > (val));
  const auto info = evnt->get_appl_info ();
  return info.file_ + ":" + std::to_string (info.line_);
}


LogModule::LogModule ()
{
  text_id_module_ = ::libs::ilink::consts::id_log;
}


void
LogModule::check_process ()
{
}


void
LogModule::add_msg_from_self (const std::string& info)
{
  U3_ASSERT (!info.empty ());
  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< syn::InfoLogEvent > (rmsg);

  dmsg->change_appl_info (
    ::libs::ilog_events::AppllPartLogInfo (
      ::libs::ievents::props::modules::log::LogLevels::info,
      ::libs::ilink::consts::id_log,
      "wtfversion"),
    info);

  events_for_save_.push_back (rmsg);
}


void
LogModule::process_property_log_module (syn::PropertyLogModuleEvent::raw_ptr props)
{
  try
  {
    appl_event_props_.module_log_->copy (props);
  }
  catch (const std::exception& excpt)
  {
    add_msg_from_self (excpt.what ());
  }
}


void
LogModule::process_info_log (syn::InfoLogEvent::raw_ptr props, syn::IEvent::ptr msg)
{
  try
  {
    if (suppressor_.process (msg, make_suppressor_key))
    {
      events_for_save_.push_back (msg);
    }
  }
  catch (const std::exception& excpt)
  {
    add_msg_from_self (excpt.what ());
  }
}


void
LogModule::process_change_state_process (syn::ChangeStateProcessEvent::raw_ptr props)
{
  U3_XLOG_MARK ("LogModule::process_change_state_process::---->" + VTOLOG (props->is_start ()));
  try
  {
    if (!props->is_start ())
    {
      add_msg_from_self (std::string ("stop log module"));
      flush_events ();
      stop_module_ = true;
      return;
    }

    add_msg_from_self (std::string ("start log module"));
  }
  catch (const std::exception& excpt)
  {
    add_msg_from_self (excpt.what ());
  }
}


void
LogModule::process_list_logs (syn::ProcessListLogsEvent::raw_ptr props)
{
  try
  {
    const auto action = props->get_action ();
    U3_XLOG_DBG ("LogModule::process_list_logs::---->" + TOLOG (to_string (action)));
    switch (action)
    {
    case ::libs::ilog_events::events::LogActions::delete_sessions: {
      delete_folders (props->get_sessions ());
      break;
    }
    case ::libs::ilog_events::events::LogActions::get_sessions: {
      const auto             folders = libs::helpers::files::get_sort_by_time_folders (path2sessions_);
      syn::list_folders_type sessions;

      sessions.reserve (folders.size ());
      U3_XLOG_DBG ("refresh sessions list" + VTOLOG (folders.size ()));

      for (const auto& folder : folders)
      {
        const std::string                     path2files = ::libs::helpers::files::make_path (path2sessions_, folder);
        ::libs::helpers::files::NodeEnumFiles enum_files;

        ::libs::helpers::files::get_files (
          path2files,
          enum_files,
          { ::libs::helpers::files::IncludeSubFolders::disabled, ::libs::helpers::files::IncludeFiles::enabled, ::libs::helpers::files::Recursives::disabled },
          ::libs::helpers::files::DefaultFileMask ("?.log?"));

        std::uint64_t size_files = 0;
        for (const auto& file : enum_files.files_)
        {
          size_files += file.size_;
        }

        U3_XLOG_DBG ("session" + TOLOG (path2files) + VTOLOG (enum_files.files_.size ()) + VTOLOG (size_files));
        sessions.emplace_back (folder, size_files);
        // sessions.emplace_back (syn::InfoLogSession (folder, size_files));
      }
      props->set_sessions (std::move (sessions));
      break;
    }
    default:
      U3_XLOG_ERROR ("unknown type LogActions " + to_string (action));
      break;
    }
  }
  catch (const std::exception& excpt)
  {
    add_msg_from_self (excpt.what ());
  }
}


void
LogModule::process_log (syn::ProcessLogEvent::raw_ptr props)
{
  try
  {
    const auto action = props->get_action ();

    switch (action)
    {
    case ::libs::ilog_events::events::LogProcessActions::get_raw_log: {
      const auto         raw_session  = props->get_session ();
      const std::string& session      = raw_session.empty () ? active_session_folder_ : raw_session;
      const std::string  path2session = ::libs::helpers::files::make_path (path2sessions_, session);
      const auto         files        = libs::helpers::files::get_sort_by_time_files (path2session);
      auto               temp_buf     = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ()->impl ()->alloc (0);

      flush_events ();

      syn::ProcessLogEvent::info_session_type info;
      U3_XLOG_MARK ("process LogProcessActions::get_raw_log" + VTOLOG (files.size ()));
      for (const auto& file : files)
      {
        ::boost::filesystem::path path2file (::libs::helpers::files::make_path (path2session, file));

        if (!::libs::helpers::files::load_file2mem (path2file.string (), temp_buf))
        {
          add_msg_from_self ("call ::libs::helpers::files::load_file2mem" + TOLOG (path2file.string ()));
          continue;
        }

        const auto add_size = temp_buf->get_data_size ();
        if (!add_size)
        {
          continue;
        }

        const auto old_size = info.data_.size ();
        const auto new_size = add_size + old_size;
        U3_XLOG_MARK ("add raw file to log" + VTOLOG (old_size) + VTOLOG (new_size) + TOLOG (path2file.string ()));
        info.data_.reserve (new_size);
        std::copy (temp_buf->get (), temp_buf->get () + add_size, std::back_inserter (info.data_));
        // add_msg_from_self( std::string( "load log file: " + file + ", add_size= " + to_str( add_size ) + ", info.data_.size=" + to_str( info.data_.size() ) ) );
      }

      props->set_log_info (std::move (info));
      break;
    }
    default: {
      add_msg_from_self ("invalid value ::libs::ilog_events::events::LogProcessActions: " + to_string (action));
      break;
    }
    }
  }
  catch (const std::exception& excpt)
  {
    add_msg_from_self (std::string ("exception:") + excpt.what ());
  }
}
}   // namespace modules::mlog::appl
