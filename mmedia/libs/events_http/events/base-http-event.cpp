/**
\file       base-http-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_http
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-http-event.hpp"

namespace libs::events_http::events
{
BaseHttpEvent::BaseHttpEvent (const Acessor& pha)
{
}


auto
BaseHttpEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseHttpEvent::gen_get_mid ();
}


auto
BaseHttpEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseHttpEvent > (this, deep);
}


void
BaseHttpEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseHttpEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
BaseHttpEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoTimedEvent", super);

  self_correct ();
}
}   // namespace libs::events_http::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_http::events::BaseHttpEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_http::events::BaseHttpEvent);
