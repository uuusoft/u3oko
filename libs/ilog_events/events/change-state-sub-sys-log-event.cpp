//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       change-state-sub-sys-log-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "change-state-sub-sys-log-event.hpp"

namespace libs { namespace ilog_events { namespace events {

ChangStateProcessTypeSubSysLogEvent::ChangStateProcessTypeSubSysLogEvent (const Acessor&) :
  InfoLogEvent (InfoLogEvent::Acessor (0), AppllPartLogInfo ("x1x", __FILE__, __LINE__), "x2x"),
  start_ (true)
{
  property_name_ = gen_get_type_text_id ();
}


ChangStateProcessTypeSubSysLogEvent::ChangStateProcessTypeSubSysLogEvent (const Acessor&, const AppllPartLogInfo& _appl, bool _start) :
  InfoLogEvent (InfoLogEvent::Acessor (0), _appl, "x5x"),
  start_ (_start)
{
  property_name_ = gen_get_type_text_id ();
}


std::string
ChangStateProcessTypeSubSysLogEvent::text (const TypeLogText& _type) const
{
  switch (_type)
    {
    case TypeLogText::subsys:
      return appl_.subsys_;
    case TypeLogText::text:
      return start_ ? "Start subsys." : "Stop subsys.";
    case TypeLogText::function:
      return appl_.funct_;
    case TypeLogText::line:
      return ::to_str (appl_.line_);
    }

  UASSERT_SIGNAL ("failed");
  return "???";
}


bool
ChangStateProcessTypeSubSysLogEvent::is_start () const
{
  return start_;
}


void
ChangStateProcessTypeSubSysLogEvent::set_start (bool _val)
{
  start_ = _val;
  return;
}


::libs::events::IEvent::ptr
ChangStateProcessTypeSubSysLogEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<ChangStateProcessTypeSubSysLogEvent> (this, _deep);
}


void
ChangStateProcessTypeSubSysLogEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (ChangStateProcessTypeSubSysLogEvent);
  super::copy_int (_src);
  start_ = _dsrc->start_;
  return;
}


template <class Archive>
void
ChangStateProcessTypeSubSysLogEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (start_);
  return;
}

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::ChangStateProcessTypeSubSysLogEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ilog_events::events::ChangStateProcessTypeSubSysLogEvent);
