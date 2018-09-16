//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       get-events-from-base.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       09.09.2018
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "get-events-from-base.hpp"

namespace libs { namespace ievents_events { namespace events {

GetEventsFromBase::GetEventsFromBase (const Acessor& _ph)
{
  property_name_ = gen_get_mid ();
}


GetEventsFromBase::~GetEventsFromBase ()
{}


void
GetEventsFromBase::set_events (events_res_type& _events)
{
  events_.swap (_events);
  return;
}


const GetEventsFromBase::events_res_type&
GetEventsFromBase::get_events () const
{
  return events_;
}


void
GetEventsFromBase::set_types (events_types_type& _types)
{
  types_.swap (_types);
  return;
}


const GetEventsFromBase::events_types_type&
GetEventsFromBase::get_types () const
{
  return types_;
}


::libs::events::IEvent::ptr
GetEventsFromBase::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<GetEventsFromBase> (this, _deep);
}


void
GetEventsFromBase::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (GetEventsFromBase);
  super::copy_int (_src);
  events_ = _dsrc->events_;
  types_  = _dsrc->types_;
  return;
}


template <class Archive>
void
GetEventsFromBase::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (events_);
  ar& BOOST_SERIALIZATION_NVP (types_);
  return;
}

}}}      // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::GetEventsFromBase);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents_events::events::GetEventsFromBase);
