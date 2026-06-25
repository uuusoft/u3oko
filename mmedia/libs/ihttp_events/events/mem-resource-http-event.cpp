/**
\file       mem-resource-http-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.04.2018
\project    u3_ihttp_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "mem-resource-http-event.hpp"

namespace libs::ihttp_events::events
{
MemResourceHttpEvent::MemResourceHttpEvent (
  const Acessor&             ph,
  const id_mem_type&         id,
  const number_mem_buf_type& number) :
  id_ (id),
  number_ (number),
  request_for_transmit_ (false)
{
  property_name_ = gen_get_mid ();
}


const MemResourceHttpEvent::id_mem_type&
MemResourceHttpEvent::get_id () const
{
  return id_;
}


void
MemResourceHttpEvent::set_id (const id_mem_type& id)
{
  id_ = id;
}


const MemResourceHttpEvent::number_mem_buf_type&
MemResourceHttpEvent::get_frame_numder () const
{
  return number_;
}


void
MemResourceHttpEvent::set_frame_number (const number_mem_buf_type& number)
{
  number_ = number;
}


bool
MemResourceHttpEvent::get_request () const
{
  return request_for_transmit_;
}


void
MemResourceHttpEvent::set_request (bool request)
{
  request_for_transmit_ = request;
}


void
MemResourceHttpEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  id_                   = obj.at ("id").as_string ();
  number_               = ::libs::helpers::json::get_int64 (obj.at ("number"));
  request_for_transmit_ = obj.at ("request_for_transmit").as_bool ();
}


void
MemResourceHttpEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["id"]                   = id_;
  obj["number"]               = number_;
  obj["request_for_transmit"] = request_for_transmit_;
}


::libs::events::IEvent::ptr
MemResourceHttpEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< MemResourceHttpEvent > (this, deep);
}


void
MemResourceHttpEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< MemResourceHttpEvent > (src);
  super::copy_int (src);

  id_                   = dsrc->id_;
  number_               = dsrc->number_;
  request_for_transmit_ = dsrc->request_for_transmit_;
}


template< class Archive >
void
MemResourceHttpEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoihttp_eventsoeventsoBaseHttpEvent", super);
  arh& BOOST_SERIALIZATION_NVP (id_);
  arh& BOOST_SERIALIZATION_NVP (number_);
  arh& BOOST_SERIALIZATION_NVP (request_for_transmit_);

  self_correct ();
}
}   // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ihttp_events::events::MemResourceHttpEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ihttp_events::events::MemResourceHttpEvent);
