/**
\file       update-listener.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       17.09.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../ievents-events-includes_int.hpp"
#include "update-listener.hpp"

namespace libs::ievents_events::events
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const SubscribeActions& src)
{
  jvs = {
    { "action", U3_CAST_UINT64_FORCE (src) }
  };
}


SubscribeActions
tag_invoke (::boost::json::value_to_tag< SubscribeActions >, const ::boost::json::value& jvs)
{
  const ::boost::json::object& obj = jvs.as_object ();
  return ::libs::helpers::casts::static_cast_helper< SubscribeActions > (::libs::helpers::json::get_uint64 (obj.at ("action")));
}


UpdateListener::UpdateListener (
  const Acessor&           ph,
  const listener_id_type&  listener_id,
  const hids_storage_type& event_types,
  const SubscribeActions&  action) :

  listener_id_ (listener_id),
  event_types_ (event_types),
  action_ (action)
{
  property_name_ = gen_get_mid ();
}


void
UpdateListener::set_listener_id (const listener_id_type& id)
{
  listener_id_ = id;
}


const UpdateListener::listener_id_type&
UpdateListener::get_listener_id () const
{
  return listener_id_;
}


void
UpdateListener::set_event_types (const hids_storage_type& event_types)
{
  event_types_ = event_types;
}


const std::vector< ::libs::events::IEvent::hid_type >&
UpdateListener::get_event_types () const
{
  return event_types_;
}


void
UpdateListener::set_action (const SubscribeActions& id)
{
  action_ = id;
}


const SubscribeActions&
UpdateListener::get_action () const
{
  return action_;
}


::libs::events::IEvent::ptr
UpdateListener::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< UpdateListener > (this, deep);
}


void
UpdateListener::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  // listener_id_ = ::boost::json::value_to< std::string > (obj.at ("listener_id"));
  listener_id_ = obj.at ("listener_id").as_string ();
  action_      = ::boost::json::value_to< SubscribeActions > (obj.at ("action"));
  event_types_ = ::boost::json::value_to< hids_storage_type > (obj.at ("event_types"));

#ifdef U3_FAKE_DISABLE
  id_                   = obj.at ("id").as_string ();
  number_               = ::libs::helpers::json::get_int64 (obj.at ("number"));
  request_for_transmit_ = obj.at ("request_for_transmit").as_bool ();
  void   tag_invoke (::boost::json::value_from_tag, ::boost::json::value & jv, const Writes& src);
  Writes tag_invoke (::boost::json::value_to_tag< Writes >, const ::boost::json::value& jvs);
#endif
}


void
UpdateListener::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["listener_id"] = ::boost::json::value_from (listener_id_);
  obj["action"]      = ::boost::json::value_from (action_);
  obj["event_types"] = ::boost::json::value_from (event_types_);
}


void
UpdateListener::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< UpdateListener > (src);
  super::copy_int (src);

  listener_id_ = dsrc->listener_id_;
  event_types_ = dsrc->event_types_;
  action_      = dsrc->action_;
}


template< class Archive >
void
UpdateListener::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("BaseEventsEvent", super);
  arh& BOOST_SERIALIZATION_NVP (listener_id_);
  arh& BOOST_SERIALIZATION_NVP (event_types_);
  arh& BOOST_SERIALIZATION_NVP (action_);

  self_correct ();
}
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::UpdateListener);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents_events::events::UpdateListener);
