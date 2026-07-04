/**
\file       update-listener-events-msg.cpp
\author     Erashov Anton erashov2026@proton.me
\date       17.09.2018
\project    u3_events_base_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-msg-includes_int.hpp"
#include "update-listener-events-msg.hpp"

namespace libs::events_msg::events
{
void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const SubscribeActions& src)
{
  jvs = {
    { "subscribe_actions", U3_CAST_UINT64_FORCE (src) }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< SubscribeActions >, const ::boost::json::value& jvs) -> SubscribeActions
{
  const ::boost::json::object& obj = jvs.as_object ();
  return ::libs::utility::casts::static_cast_helper< SubscribeActions > (::libs::utility::json::get_uint64 (obj.at ("subscribe_actions")));
}


UpdateListenerEventsMsg::UpdateListenerEventsMsg (
  const Acessor&          ph,
  listener_id_type        listener_id,
  hids_storage_type       event_types,
  const SubscribeActions& action) :
  listener_id_ (std::move (listener_id)),
  event_types_ (std::move (event_types)),
  action_ (action)
{
}


auto
UpdateListenerEventsMsg::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return UpdateListenerEventsMsg::gen_get_mid ();
}


void
UpdateListenerEventsMsg::set_listener_id (const listener_id_type& id)
{
  listener_id_ = id;
}


auto
UpdateListenerEventsMsg::get_listener_id () const -> const UpdateListenerEventsMsg::listener_id_type&
{
  return listener_id_;
}


void
UpdateListenerEventsMsg::set_event_types (const hids_storage_type& event_types)
{
  event_types_ = event_types;
}


auto
UpdateListenerEventsMsg::get_event_types () const -> const hids_storage_type&
{
  return event_types_;
}


void
UpdateListenerEventsMsg::set_action (const SubscribeActions& id)
{
  action_ = id;
}


auto
UpdateListenerEventsMsg::get_action () const -> const SubscribeActions&
{
  return action_;
}


auto
UpdateListenerEventsMsg::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< UpdateListenerEventsMsg > (this, deep);
}


void
UpdateListenerEventsMsg::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  // listener_id_ = ::boost::json::value_to< std::string > (obj.at ("listener_id"));
  listener_id_ = obj.at ("listener_id").as_string ();
  action_      = ::boost::json::value_to< SubscribeActions > (obj.at ("subscribe_actions"));
  event_types_ = ::boost::json::value_to< hids_storage_type > (obj.at ("event_types"));

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  id_                   = obj.at ("id").as_string ();
  number_               = ::libs::utility::json::get_int64 (obj.at ("number"));
  request_for_transmit_ = obj.at ("request_for_transmit").as_bool ();
  void   tag_invoke (::boost::json::value_from_tag, ::boost::json::value & jv, const Writes& src);
  Writes tag_invoke (::boost::json::value_to_tag< Writes >, const ::boost::json::value& jvs);
#endif
}


void
UpdateListenerEventsMsg::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["listener_id"]       = ::boost::json::value_from (listener_id_);
  obj["subscribe_actions"] = ::boost::json::value_from (action_);
  obj["event_types"]       = ::boost::json::value_from (event_types_);
}


void
UpdateListenerEventsMsg::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< UpdateListenerEventsMsg > (src);
  super::copy_int (src);

  listener_id_ = dsrc->listener_id_;
  event_types_ = dsrc->event_types_;
  action_      = dsrc->action_;
}


template< class Archive >
void
UpdateListenerEventsMsg::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("BaseEventsMsg", super);
  arh& BOOST_SERIALIZATION_NVP (listener_id_);
  arh& BOOST_SERIALIZATION_NVP (event_types_);
  arh& BOOST_SERIALIZATION_NVP (action_);

  self_correct ();
}
}   // namespace libs::events_msg::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_msg::events::UpdateListenerEventsMsg);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_msg::events::UpdateListenerEventsMsg);
