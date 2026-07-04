/**
\file       base-user-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2018
\project    u3_events_user
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-user-includes_int.hpp"
#include "base-user-event.hpp"

namespace libs::events_user::events
{
BaseUserEvent::BaseUserEvent (const Acessor& pha)
{
}


auto
BaseUserEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseUserEvent::gen_get_mid ();
}


auto
BaseUserEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseUserEvent > (this, deep);
}


void
BaseUserEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseUserEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
BaseUserEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoTimedEvent", super);

  self_correct ();
}
}   // namespace libs::events_user::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_user::events::BaseUserEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_user::events::BaseUserEvent);
