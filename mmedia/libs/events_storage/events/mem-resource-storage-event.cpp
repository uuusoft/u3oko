/**
\file       mem-resource-storage-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2018
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-storage-includes_int.hpp"
#include "mem-resource-storage-event.hpp"

namespace libs::events_storage::events
{
MemResourceStorageEvent::MemResourceStorageEvent (
  const Acessor&             ph,
  id_mem_type                id,
  const number_mem_buf_type& number) :
  id_ (std::move (id)),
  number_ (number)
{
}


auto
MemResourceStorageEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return MemResourceStorageEvent::gen_get_mid ();
}


auto
MemResourceStorageEvent::get_id () const -> const MemResourceStorageEvent::id_mem_type&
{
  return id_;
}


void
MemResourceStorageEvent::set_id (const id_mem_type& id)
{
  id_ = id;
}


auto
MemResourceStorageEvent::get_numder () const -> const MemResourceStorageEvent::number_mem_buf_type&
{
  return number_;
}


void
MemResourceStorageEvent::set_number (const number_mem_buf_type& number)
{
  number_ = number;
}


auto
MemResourceStorageEvent::get_request () const -> bool
{
  return request_for_transmit_;
}


void
MemResourceStorageEvent::set_request (bool request)
{
  request_for_transmit_ = request;
}


auto
MemResourceStorageEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< MemResourceStorageEvent > (this, deep);
}


void
MemResourceStorageEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< MemResourceStorageEvent > (src);
  super::copy_int (src);

  id_                   = dsrc->id_;
  number_               = dsrc->number_;
  request_for_transmit_ = dsrc->request_for_transmit_;
}


template< class Archive >
void
MemResourceStorageEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_storageoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (id_);
  arh& BOOST_SERIALIZATION_NVP (number_);
  arh& BOOST_SERIALIZATION_NVP (request_for_transmit_);

  self_correct ();
}
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_storage::events::MemResourceStorageEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_storage::events::MemResourceStorageEvent);
