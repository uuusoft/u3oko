//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       base-events-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "base-events-event.hpp"

namespace libs { namespace ievents_events { namespace events {

BaseEventsEvent::BaseEventsEvent (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


BaseEventsEvent::~BaseEventsEvent ()
{}


::libs::events::IEvent::ptr
BaseEventsEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<BaseEventsEvent> (this, _deep);
}


void
BaseEventsEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (BaseEventsEvent);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
BaseEventsEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}      // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::BaseEventsEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents_events::events::BaseEventsEvent);
