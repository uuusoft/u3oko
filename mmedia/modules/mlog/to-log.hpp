#pragma once
/**
\file       to-log.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.04.2026
*/

namespace modules::mlog::syn
{
using key_storage_type = ::libs::properties::vers::links::mids::key_storage_type;
using LogLevels        = ::libs::events_base::props::modules::log::LogLevels;

namespace log = ::libs::events_base::props::modules::log;
}   // namespace modules::mlog::syn


namespace modules::mlog
{
enum class LogControl : std::uint8_t
{
  disable = 0,     //<
  enable  = 1,     //<
  unknown = 0xFF   //<
};

template< LogControl = LogControl::enable >
class ToLog final
{
  public:
  U3_ADD_DELETE_MOVE_COPY (ToLog);

  ToLog (
    const syn::key_storage_type key,
    const syn::LogLevels&       level,
    const std::thread::id&      thread_id = std::this_thread::get_id (),
    const std::source_location& place     = std::source_location::current ()) :

    key_ (key),
    level_ (level),
    thread_id_ (thread_id),
    place_ (place)
  {
  }

#if 0
  template< typename... Args >
  auto
  operator() (Args&&... args) -> void
  {
    if (level_ > syn::log::g_log_level)
    {
      return;
    }

    std::stringstream buftemp;
    (buftemp << ... << args);

    msg2stream (buftemp);

    if (::libs::iproperties::helpers::check_prop_links ())
    {
      auto* props_links = ::libs::iproperties::helpers::get_prop_links ();
      auto  logger      = props_links ? props_links->get_links_lockfree ()[key_].lock () : nullptr;
      if (logger)
      {
        msg2logger (logger.get (), buftemp);
      }
    }
  }
#endif

  auto
  operator() (const std::string_view par) -> void
  {
    if (level_ > syn::log::g_log_level)
    {
      return;
    }

    const std::string res { par };
    msg2stream (res);

    if (::libs::iproperties::helpers::check_prop_links ())
    {
      auto* props_links = ::libs::iproperties::helpers::get_prop_links ();
      auto  logger      = props_links ? props_links->get_links_lockfree ()[key_].lock () : nullptr;
      if (logger)
      {
        msg2logger (logger.get (), res);
      }
    }
  }


  private:
  auto
  msg2logger (
    ::libs::link::ILink::raw_ptr logger,
    const std::string&           buf) -> void
  {
    if (!logger)
    {
      return;
    }

    const auto msglm_demons = ::libs::iproperties::helpers::cast_prop_demons ();
    const auto msglm_events = msglm_demons->get_events_lockfree ();
    if (!msglm_events)
    {
      return;
    }

    // const auto thread_id = std::format ("{}\t|", std::hash< std::thread::id > {}(thread_id_));
    const auto thread_id = std::format ("{}", std::hash< std::thread::id > {}(thread_id_));
    auto [evnt, revnt]   = ::libs::iproperties::helpers::create_event< ::libs::events_log::events::InfoLogEvent > ();
    revnt->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        level_,
        to_string (key_.first),
        "wtfversion",
        thread_id,
        place_),
      buf);

    logger->send_msg (evnt);
  }


  auto
  msg2logger (
    ::libs::link::ILink::raw_ptr logger,
    const std::stringstream&     buf) -> void
  {
    msg2logger (logger, buf.str ());
  }


  auto
  msg2stream (const std::string& streambuf) -> void
  {
    if (syn::LogLevels::disable == level_)
    {
      return;
    }

    const auto place_info = ::libs::utility::log::get_text_source_place (place_);
    const auto buf        = streambuf + "  <...>  " + place_info;

    switch (level_)
    {
    case syn::LogLevels::debug:
    case syn::LogLevels::develop:
      U3_XLOG_DEV ("{}", buf);
      break;
    case syn::LogLevels::exception:
      U3_XLOG_ERROR ("{}", buf);
      break;
    case syn::LogLevels::invalid_state:
      U3_XLOG_ERROR ("{}", buf);
      break;
    case syn::LogLevels::error:
      U3_XLOG_ERROR ("{}", buf);
      break;
    case syn::LogLevels::warning:
      U3_XLOG_WARN ("{}", buf);
      break;
    case syn::LogLevels::mark:
      U3_XLOG_MARK ("{}", buf);
      break;
    case syn::LogLevels::info:
      U3_XLOG_TIME ("{}", buf);
      break;
    case syn::LogLevels::timing:
      U3_XLOG_TIME ("{}", buf);
      break;
    case syn::LogLevels::data:
      U3_XLOG_TIME ("{}", buf);
      break;
    default:
      U3_XLOG_DEV ("{}", buf);
      break;
    }
  }


  auto
  msg2stream (const std::stringstream& streambuf) -> void
  {
    msg2stream (streambuf.str ());
  }

  const syn::key_storage_type key_ { ::libs::properties::vers::links::mids::unknown };   //<
  const syn::LogLevels        level_ { syn::LogLevels::develop };                        //<
  const std::thread::id       thread_id_;                                                //<
  const std::source_location  place_ { std::source_location::current () };               //<
};
}   // namespace modules::mlog
