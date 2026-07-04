/**
\file       base-events-msg.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-msg-includes_int.hpp"
#include "base-events-msg.hpp"

namespace libs::events_msg::events
{
BaseEventsMsg::BaseEventsMsg (const Acessor& pha)
{
}


auto
BaseEventsMsg::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseEventsMsg::gen_get_mid ();
}


auto
BaseEventsMsg::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseEventsMsg > (this, deep);
}


void
BaseEventsMsg::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
}


void
BaseEventsMsg::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
}


void
BaseEventsMsg::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseEventsMsg > (src);
  super::copy_int (src);
}


template< class Archive >
void
BaseEventsMsg::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoTimedEvent", super);
  self_correct ();
}
}   // namespace libs::events_msg::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_msg::events::BaseEventsMsg);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_msg::events::BaseEventsMsg);
