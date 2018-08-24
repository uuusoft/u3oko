//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       process-list-logs-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "process-list-logs-event.hpp"

namespace libs { namespace ilog_events { namespace events {

ProcessListLogsEvent::ProcessListLogsEvent (const Acessor&, const AppllPartLogInfo& _appl) :
  action_ (ActionForListLogs::get_sessions)
{
  property_name_ = gen_get_type_text_id ();
}


ProcessListLogsEvent::~ProcessListLogsEvent ()
{}


std::string
ProcessListLogsEvent::text (const TypeLogText& _type) const
{
  UASSERT_SIGNAL ("failed");
  return "???";
}


const ProcessListLogsEvent::list_folders_type&
ProcessListLogsEvent::get_sessions () const
{
  return folders_;
}


void
ProcessListLogsEvent::set_sessions (list_folders_type&& _folders)
{
  folders_.swap (_folders);
  return;
}


ActionForListLogs
ProcessListLogsEvent::get_action () const
{
  return action_;
}


void
ProcessListLogsEvent::set_action (const ActionForListLogs& _action)
{
  action_ = _action;
  return;
}


::libs::events::IEvent::ptr
ProcessListLogsEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<ProcessListLogsEvent> (this, _deep);
}


void
ProcessListLogsEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ProcessListLogsEvent);
  super::copy_int (_src);
  action_  = _dsrc->action_;
  folders_ = _dsrc->folders_;
  return;
}


template <class Archive>
void
ProcessListLogsEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (action_);
  ar& BOOST_SERIALIZATION_NVP (folders_);
  return;
}

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::ProcessListLogsEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ilog_events::events::ProcessListLogsEvent);
