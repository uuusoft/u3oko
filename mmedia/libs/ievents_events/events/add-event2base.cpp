/**
\file       add-event2base.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       09.09.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../ievents-events-includes_int.hpp"
#include "add-event2base.hpp"

namespace libs::ievents_events::events
{
AddEvent2Base::AddEvent2Base (
  const Acessor&                     ph,
  const ::libs::events::IEvent::ptr& obj,
  const machine_id_type&             machine_id,
  const object_id_type&              object_id) :
  add_event_ (obj),
  machine_id_ (machine_id),
  object_id_ (object_id)
{
  property_name_ = gen_get_mid ();
}


AddEvent2Base::~AddEvent2Base ()
{
}


void
AddEvent2Base::sync_event_props (const machine_id_type& machine_id, const object_id_type& object_id)
{
  machine_id_ = machine_id;
  object_id_  = object_id;
}


void
AddEvent2Base::set_event (::libs::events::IEvent::ptr& obj)
{
  add_event_ = obj;
}


::libs::events::IEvent::ptr
AddEvent2Base::get_event () const
{
  return add_event_;
}


void
AddEvent2Base::set_object_id (const object_id_type& id)
{
  object_id_ = id;
}


const AddEvent2Base::object_id_type&
AddEvent2Base::get_object_id () const
{
  return object_id_;
}


void
AddEvent2Base::set_machine_id (const machine_id_type& id)
{
  machine_id_ = id;
}


const AddEvent2Base::machine_id_type&
AddEvent2Base::get_machine_id () const
{
  return machine_id_;
}


::libs::events::IEvent::ptr
AddEvent2Base::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< AddEvent2Base > (this, deep);
}


void
AddEvent2Base::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
AddEvent2Base::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
AddEvent2Base::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (AddEvent2Base);
  super::copy_int (src);

  machine_id_ = dsrc->machine_id_;
  object_id_  = dsrc->object_id_;
  add_event_  = dsrc->add_event_;
}


template< class Archive >
void
AddEvent2Base::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("BaseEventsEvent", super);
  ar& BOOST_SERIALIZATION_NVP (machine_id_);
  ar& BOOST_SERIALIZATION_NVP (object_id_);
  ar& BOOST_SERIALIZATION_NVP (add_event_);

  self_correct ();
}
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::AddEvent2Base);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents_events::events::AddEvent2Base);
