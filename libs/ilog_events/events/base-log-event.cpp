//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-log-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "base-log-event.hpp"

namespace libs { namespace ilog_events { namespace events {

BaseLogEvent::BaseLogEvent (const BaseLogEvent::Acessor&)
{
  property_name_ = gen_get_type_text_id ();
}


BaseLogEvent::~BaseLogEvent ()
{}


std::string
BaseLogEvent::text (const TypeLogText& _type) const
{
  UASSERT_SIGNAL ("call BaseLogEvent::text");
  return std::string ("BaseLogEvent placeholder");
}


::libs::events::IEvent::ptr
BaseLogEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<BaseLogEvent> (this, _deep);
}


void
BaseLogEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseLogEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
BaseLogEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::BaseLogEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ilog_events::events::BaseLogEvent);
