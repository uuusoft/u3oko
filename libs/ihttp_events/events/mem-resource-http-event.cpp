//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mem-resource-http-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.04.2018
\copyright  www.uuusoft.com
\project    uuu_ihttp_events
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "mem-resource-http-event.hpp"

namespace libs { namespace ihttp_events { namespace events {

MemResourceHttpEvent::MemResourceHttpEvent (const Acessor& _ph, const id_mem_type& _id, const number_mem_buff_type& _number) :
  id_ (_id),
  number_ (_number),
  request_for_transmit_ (false)
{
  property_name_ = gen_get_type_text_id ();
}


MemResourceHttpEvent::~MemResourceHttpEvent ()
{}


const MemResourceHttpEvent::id_mem_type&
MemResourceHttpEvent::get_id () const
{
  return id_;
}


void
MemResourceHttpEvent::set_id (const id_mem_type& _id)
{
  id_ = _id;
  return;
}


const MemResourceHttpEvent::number_mem_buff_type&
MemResourceHttpEvent::get_numder () const
{
  return number_;
}


void
MemResourceHttpEvent::set_number (const number_mem_buff_type& _number)
{
  number_ = _number;
  return;
}


bool
MemResourceHttpEvent::get_request () const
{
  return request_for_transmit_;
}


void
MemResourceHttpEvent::set_request (bool _request)
{
  request_for_transmit_ = _request;
  return;
}


::libs::events::IEvent::ptr
MemResourceHttpEvent::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<MemResourceHttpEvent> (this, _deep);
}


void
MemResourceHttpEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (MemResourceHttpEvent);
  super::copy_int (_src);
  id_                   = _dsrc->id_;
  number_               = _dsrc->number_;
  request_for_transmit_ = _dsrc->request_for_transmit_;
  return;
}


template <class Archive>
void
MemResourceHttpEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (id_);
  ar& BOOST_SERIALIZATION_NVP (number_);
  ar& BOOST_SERIALIZATION_NVP (request_for_transmit_);
  return;
}

}}}      // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ihttp_events::events::MemResourceHttpEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ihttp_events::events::MemResourceHttpEvent);
