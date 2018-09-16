//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       wrapper-events-event.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "wrapper-events-event.hpp"

namespace libs { namespace ievents_events { namespace events {

WrapperEventsEvent::WrapperEventsEvent (const Acessor& _ph, ::libs::events::IEvent::ptr _msg) :
  int_ (_msg)
{
  property_name_ = gen_get_mid ();
}


WrapperEventsEvent::~WrapperEventsEvent ()
{}


::libs::events::IEvent::ptr
WrapperEventsEvent::get_msg () const
{
  return int_;
}


void
WrapperEventsEvent::set_msg (::libs::events::IEvent::ptr& _msg)
{
  int_ = _msg;
  return;
}


::libs::events::IEvent::ptr
WrapperEventsEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<WrapperEventsEvent> (this, _deep);
}


void
WrapperEventsEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (WrapperEventsEvent);
  super::copy_int (_src);
  int_ = _dsrc->int_;
  return;
}


template <class Archive>
void
WrapperEventsEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (int_);
  return;
}

}}}      // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::WrapperEventsEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents_events::events::WrapperEventsEvent);
