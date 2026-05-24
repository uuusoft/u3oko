/**
\file       mem-resource-storage-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "mem-resource-storage-event.hpp"

namespace libs::istorage_events::events
{
MemResourceStorageEvent::MemResourceStorageEvent (
  const Acessor&             ph,
  const id_mem_type&         id,
  const number_mem_buf_type& number) :
  id_ (id),
  number_ (number),
  request_for_transmit_ (false)
{
  property_name_ = gen_get_mid ();
}


MemResourceStorageEvent::~MemResourceStorageEvent ()
{
}


const MemResourceStorageEvent::id_mem_type&
MemResourceStorageEvent::get_id () const
{
  return id_;
}


void
MemResourceStorageEvent::set_id (const id_mem_type& id)
{
  id_ = id;
}


const MemResourceStorageEvent::number_mem_buf_type&
MemResourceStorageEvent::get_numder () const
{
  return number_;
}


void
MemResourceStorageEvent::set_number (const number_mem_buf_type& number)
{
  number_ = number;
}


bool
MemResourceStorageEvent::get_request () const
{
  return request_for_transmit_;
}


void
MemResourceStorageEvent::set_request (bool request)
{
  request_for_transmit_ = request;
}


::libs::events::IEvent::ptr
MemResourceStorageEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< MemResourceStorageEvent > (this, deep);
}


void
MemResourceStorageEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (MemResourceStorageEvent);
  super::copy_int (src);
  id_                   = dsrc->id_;
  number_               = dsrc->number_;
  request_for_transmit_ = dsrc->request_for_transmit_;
}


template< class Archive >
void
MemResourceStorageEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  ar& BOOST_SERIALIZATION_NVP (id_);
  ar& BOOST_SERIALIZATION_NVP (number_);
  ar& BOOST_SERIALIZATION_NVP (request_for_transmit_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::MemResourceStorageEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::MemResourceStorageEvent);
