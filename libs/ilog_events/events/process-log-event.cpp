//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       process-log-event.cpp
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

ProcessLogEvent::ProcessLogEvent (const Acessor&, const AppllPartLogInfo& _appl) :
  action_ (ActionForProcessLog::get_raw_log)
{
  property_name_ = gen_get_type_text_id ();
}


ProcessLogEvent::~ProcessLogEvent ()
{}


std::string
ProcessLogEvent::text (const TypeLogText& _type) const
{
  UASSERT_SIGNAL ("failed");
  return "???";
}


const ProcessLogEvent::id_session_type&
ProcessLogEvent::get_session () const
{
  return session_;
}


void
ProcessLogEvent::set_session (id_session_type&& _session)
{
  session_.swap (_session);
  return;
}


const ProcessLogEvent::info_session_type&
ProcessLogEvent::get_log_info () const
{
  return info_;
}


void
ProcessLogEvent::set_log_info (info_session_type&& _info)
{
  info_ = _info;
  return;
}


ActionForProcessLog
ProcessLogEvent::get_action () const
{
  return action_;
}


void
ProcessLogEvent::set_action (const ActionForProcessLog& _action)
{
  action_ = _action;
  return;
}


::libs::events::IEvent::ptr
ProcessLogEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<ProcessLogEvent> (this, _deep);
}


void
ProcessLogEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ProcessLogEvent);
  super::copy_int (_src);
  action_  = _dsrc->action_;
  session_ = _dsrc->session_;
  info_    = _dsrc->info_;
  return;
}


template <class Archive>
void
ProcessLogEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (action_);
  ar& BOOST_SERIALIZATION_NVP (session_);
  ar& BOOST_SERIALIZATION_NVP (info_);
  return;
}

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::ProcessLogEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ilog_events::events::ProcessLogEvent);
