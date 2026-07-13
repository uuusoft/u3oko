#pragma once
/**
\file       to-log20-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.04.2026
\project    mlog
*/

namespace modules::mlog::syn
{
using key_storage_type = libs::properties::vers::links::mids::key_storage_type;
using LogLevels        = libs::events_base::props::modules::log::LogLevels;
}   // namespace modules::mlog::syn

namespace modules::mlog
{
enum class LogControl : std::uint8_t
{
  disable = 0,
  enable  = 1,
  unknown = 0xFF
};

template< LogControl = LogControl::enable >
class ToLog final
{
  public:
  ToLog (
    const syn::key_storage_type& key,
    const syn::LogLevels&        level,
    const std::source_location&  place = std::source_location::current ()) :
    key_ (key),
    place_ (place),
    level_ (level)
  {
  }

  template< typename... Args >
  void
  operator() (Args... args)
  {
    if (level_ > ::libs::events_base::props::modules::log::g_log_level)
    {
      return;
    }

    std::stringstream buftemp;
    (buftemp << ... << args);

    msg2cout (buftemp);

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

  private:
  void
  msg2logger (::libs::link::ILink::raw_ptr logger, const std::stringstream& buf)
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

    auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< ::libs::events_log::events::InfoLogEvent > ();
    revnt->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (level_, to_string (key_.first), "wtfversion", place_),
      buf.str ());

    logger->send_msg (evnt);
  }

  void
  msg2cout (const std::stringstream& streambuf)
  {
    if (syn::LogLevels::disable == level_)
    {
      return;
    }

    const auto place_info = ::libs::utility::log::get_text_source_place (place_);
    const auto buf        = streambuf.str () + "......" + place_info;

    switch (level_)
    {
    case syn::LogLevels::debug:
    case syn::LogLevels::develop:
      U3_XLOG_DEV (buf);
      break;
    case syn::LogLevels::exception:
      U3_XLOG_ERROR (buf);
      break;
    case syn::LogLevels::invalid_state:
      U3_XLOG_ERROR (buf);
      break;
    case syn::LogLevels::error:
      U3_XLOG_ERROR (buf);
      break;
    case syn::LogLevels::warning:
      U3_XLOG_WARN (buf);
      break;
    case syn::LogLevels::mark:
      U3_XLOG_MARK (buf);
      break;
    case syn::LogLevels::info:
      U3_XLOG_TIME (buf);
      break;
    case syn::LogLevels::timing:
      U3_XLOG_TIME (buf);
      break;
    case syn::LogLevels::data:
      U3_XLOG_TIME (buf);
      break;
    default:
      U3_XLOG_DEV (buf);
      break;
    }
  }

  const syn::key_storage_type key_   = libs::properties::vers::links::mids::unknown;
  const syn::LogLevels        level_ = syn::LogLevels::develop;
  const std::source_location  place_ = std::source_location::current ();
};
}   // namespace modules::mlog
