/**
\file       process-list-logs-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "process-list-logs-event.hpp"

namespace libs::ilog_events::events
{
ProcessListLogsEvent::ProcessListLogsEvent (const Acessor&, const AppllPartLogInfo& appl) :
  action_ (LogActions::get_sessions)
{
  property_name_ = gen_get_mid ();
}


ProcessListLogsEvent::~ProcessListLogsEvent ()
{
}


std::string
ProcessListLogsEvent::text (const LogTexts& type) const
{
  U3_ASSERT_SIGNAL ("failed");
  return "?plle?";
}


const ProcessListLogsEvent::list_folders_type&
ProcessListLogsEvent::get_sessions () const
{
  return folders_;
}


void
ProcessListLogsEvent::set_sessions (list_folders_type&& folders)
{
  folders_.swap (folders);
}


LogActions
ProcessListLogsEvent::get_action () const
{
  return action_;
}


void
ProcessListLogsEvent::set_action (const LogActions& action)
{
  action_ = action;
}


::libs::events::IEvent::ptr
ProcessListLogsEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ProcessListLogsEvent > (this, deep);
}


void
ProcessListLogsEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  action_  = ::boost::json::value_to< LogActions > (obj.at ("action"));
  folders_ = ::boost::json::value_to< ProcessListLogsEvent::list_folders_type > (obj.at ("folders"));
}


void
ProcessListLogsEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["action"]  = ::boost::json::value_from (action_);
  obj["folders"] = ::boost::json::value_from (folders_);
}


void
ProcessListLogsEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (ProcessListLogsEvent);
  super::copy_int (src);
  action_  = dsrc->action_;
  folders_ = dsrc->folders_;
}


template< class Archive >
void
ProcessListLogsEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoilog_eventsoeventsoBaseLogEvent", super);
  ar& BOOST_SERIALIZATION_NVP (action_);
  ar& BOOST_SERIALIZATION_NVP (folders_);

  self_correct ();
}
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::ProcessListLogsEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::events::ProcessListLogsEvent);
