//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       mem-resource-storage-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "mem-resource-storage-event.hpp"

namespace libs { namespace istorage_events { namespace events {

MemResourceStorageEvent::MemResourceStorageEvent (const Acessor& _ph, const id_mem_type& _id, const number_mem_buff_type& _number) :
  id_ (_id),
  number_ (_number),
  request_for_transmit_ (false)
{
  property_name_ = gen_get_mid ();
}


MemResourceStorageEvent::~MemResourceStorageEvent ()
{}


const MemResourceStorageEvent::id_mem_type&
MemResourceStorageEvent::get_id () const
{
  return id_;
}


void
MemResourceStorageEvent::set_id (const id_mem_type& _id)
{
  id_ = _id;
  return;
}


const MemResourceStorageEvent::number_mem_buff_type&
MemResourceStorageEvent::get_numder () const
{
  return number_;
}


void
MemResourceStorageEvent::set_number (const number_mem_buff_type& _number)
{
  number_ = _number;
  return;
}


bool
MemResourceStorageEvent::get_request () const
{
  return request_for_transmit_;
}


void
MemResourceStorageEvent::set_request (bool _request)
{
  request_for_transmit_ = _request;
  return;
}


::libs::events::IEvent::ptr
MemResourceStorageEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<MemResourceStorageEvent> (this, _deep);
}


void
MemResourceStorageEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (MemResourceStorageEvent);
  super::copy_int (_src);
  id_                   = _dsrc->id_;
  number_               = _dsrc->number_;
  request_for_transmit_ = _dsrc->request_for_transmit_;
  return;
}


template <class Archive>
void
MemResourceStorageEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (id_);
  ar& BOOST_SERIALIZATION_NVP (number_);
  ar& BOOST_SERIALIZATION_NVP (request_for_transmit_);
  return;
}

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::MemResourceStorageEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::istorage_events::events::MemResourceStorageEvent);
