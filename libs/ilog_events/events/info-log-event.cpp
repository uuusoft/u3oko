//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-log-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "info-log-event.hpp"

namespace libs { namespace ilog_events { namespace events {

InfoLogEvent::InfoLogEvent (const Acessor&, const AppllPartLogInfo& _appl, const std::string& _info) :

  info_ (_info),
  appl_ (_appl)
{
  time_          = boost::posix_time::microsec_clock::universal_time ();
  property_name_ = gen_get_type_text_id ();
}


InfoLogEvent::~InfoLogEvent ()
{}


void
InfoLogEvent::update_info (const AppllPartLogInfo& _appl, const std::string& _info)
{
  info_ = _info;
  appl_ = _appl;
  return;
}


std::string
InfoLogEvent::text (const TypeLogText& _type) const
{
  switch (_type)
    {
    case TypeLogText::subsys:
      return appl_.subsys_;
    case TypeLogText::text:
      return info_;
    case TypeLogText::function:
      return appl_.funct_;
    case TypeLogText::line:
      return ::to_str (appl_.line_);
    }

  UASSERT_SIGNAL ("failed");
  return "???";
}


::libs::events::IEvent::ptr
InfoLogEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<InfoLogEvent> (this, _deep);
}


void
InfoLogEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (InfoLogEvent);
  super::copy_int (_src);
  appl_ = _dsrc->appl_;
  info_ = _dsrc->info_;
  time_ = _dsrc->time_;
  return;
}


template <class Archive>
void
InfoLogEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (appl_);
  ar& BOOST_SERIALIZATION_NVP (info_);
  ar& BOOST_SERIALIZATION_NVP (time_);
  return;
}

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::InfoLogEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ilog_events::events::InfoLogEvent);
