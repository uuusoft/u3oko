/**
\file       add-event2events-msg.cpp
\author     Erashov Anton erashov2026@proton.me
\date       09.09.2018
\project    u3_events_base_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-msg-includes_int.hpp"
#include "add-event2events-msg.hpp"

namespace libs::events_msg::events
{
AddEvent2EventsMsg::AddEvent2EventsMsg (
  const Acessor&              ph,
  ::libs::events::IEvent::ptr obj,
  const machine_id_type&      machine_id,
  object_id_type              object_id) :
  add_event_ (std::move (obj)),
  machine_id_ (machine_id),
  object_id_ (std::move (object_id))
{
}


auto
AddEvent2EventsMsg::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return AddEvent2EventsMsg::gen_get_mid ();
}


void
AddEvent2EventsMsg::sync_event_props (const machine_id_type& machine_id, const object_id_type& object_id)
{
  machine_id_ = machine_id;
  object_id_  = object_id;
}


void
AddEvent2EventsMsg::set_event (::libs::events::IEvent::ptr& obj)
{
  add_event_ = obj;
}


auto
AddEvent2EventsMsg::get_event () const -> ::libs::events::IEvent::ptr
{
  return add_event_;
}


void
AddEvent2EventsMsg::set_object_id (const object_id_type& id)
{
  object_id_ = id;
}


auto
AddEvent2EventsMsg::get_object_id () const -> const AddEvent2EventsMsg::object_id_type&
{
  return object_id_;
}


void
AddEvent2EventsMsg::set_machine_id (const machine_id_type& id)
{
  machine_id_ = id;
}


auto
AddEvent2EventsMsg::get_machine_id () const -> const AddEvent2EventsMsg::machine_id_type&
{
  return machine_id_;
}


auto
AddEvent2EventsMsg::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< AddEvent2EventsMsg > (this, deep);
}


void
AddEvent2EventsMsg::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "AddEvent2EventsMsg::load_json_int:: wtf???");
}


void
AddEvent2EventsMsg::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "AddEvent2EventsMsg::save_json_int:: wtf???");
}


void
AddEvent2EventsMsg::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< AddEvent2EventsMsg > (src);
  super::copy_int (src);

  machine_id_ = dsrc->machine_id_;
  object_id_  = dsrc->object_id_;
  add_event_  = dsrc->add_event_;
}


template< class Archive >
void
AddEvent2EventsMsg::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("BaseEventsMsg", super);
  arh& BOOST_SERIALIZATION_NVP (machine_id_);
  arh& BOOST_SERIALIZATION_NVP (object_id_);
  arh& BOOST_SERIALIZATION_NVP (add_event_);

  self_correct ();
}
}   // namespace libs::events_msg::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_msg::events::AddEvent2EventsMsg);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_msg::events::AddEvent2EventsMsg);
