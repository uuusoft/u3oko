/**
\file       process-log-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "process-list-logs-event.hpp"

namespace libs::events_log::events
{
ProcessLogEvent::ProcessLogEvent (const Acessor&, const AppllPartLogInfo& appl) :
  action_ (LogProcessActions::get_raw_log)
{
}


auto
ProcessLogEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ProcessLogEvent::gen_get_mid ();
}


auto
ProcessLogEvent::text (const LogTexts& type) const -> std::string
{
  U3_ASSERT_SIGNAL ("failed");
  return "ProcessLogEvent::text:: wtf???";
}


auto
ProcessLogEvent::get_session () const -> const InfoLogSession::id_session_type&
{
  return session_;
}


void
ProcessLogEvent::set_session (InfoLogSession::id_session_type&& session)
{
  session_.swap (session);
}


auto
ProcessLogEvent::get_log_info () const -> const ProcessLogEvent::info_session_type&
{
  return info_;
}


void
ProcessLogEvent::set_log_info (info_session_type&& info)
{
  info_ = info;
}


auto
ProcessLogEvent::get_action () const -> LogProcessActions
{
  return action_;
}


void
ProcessLogEvent::set_action (const LogProcessActions& action)
{
  action_ = action;
}


void
ProcessLogEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  action_  = ::boost::json::value_to< LogProcessActions > (obj.at ("log_process_actions"));
  info_    = ::boost::json::value_to< InfoLogSessionFragment > (obj.at ("info"));
  session_ = obj.at ("session").as_string ();
}


void
ProcessLogEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  obj["log_process_actions"] = ::boost::json::value_from (action_);
  obj["info"]                = ::boost::json::value_from (info_);
  obj["session"]             = session_;
}


auto
ProcessLogEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ProcessLogEvent > (this, deep);
}


void
ProcessLogEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ProcessLogEvent > (src);
  super::copy_int (src);

  action_  = dsrc->action_;
  session_ = dsrc->session_;
  info_    = dsrc->info_;
}


template< class Archive >
void
ProcessLogEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_logoeventsoBaseLogEvent", super);
  arh& BOOST_SERIALIZATION_NVP (action_);
  arh& BOOST_SERIALIZATION_NVP (session_);
  arh& BOOST_SERIALIZATION_NVP (info_);

  self_correct ();
}
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_log::events::ProcessLogEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_log::events::ProcessLogEvent);
