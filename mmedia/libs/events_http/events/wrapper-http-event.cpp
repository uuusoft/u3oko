/**
\file       wrapper-http-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_http
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "wrapper-http-event.hpp"

namespace libs::events_http::events
{
WrapperHttpEvent::WrapperHttpEvent (const Acessor& pha, ::libs::events::IEvent::ptr msg) :
  int_ (std::move (msg))
{
}


auto
WrapperHttpEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return WrapperHttpEvent::gen_get_mid ();
}


auto
WrapperHttpEvent::get_msg () const -> ::libs::events::IEvent::ptr
{
  return int_;
}


void
WrapperHttpEvent::set_msg (::libs::events::IEvent::ptr& msg)
{
  int_ = msg;
}


auto
WrapperHttpEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< WrapperHttpEvent > (this, deep);
}


void
WrapperHttpEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< WrapperHttpEvent > (src);
  super::copy_int (src);

  int_ = dsrc->int_;
}


template< class Archive >
void
WrapperHttpEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoTimedEvent", super);
  arh& BOOST_SERIALIZATION_NVP (int_);

  self_correct ();
}
}   // namespace libs::events_http::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_http::events::WrapperHttpEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_http::events::WrapperHttpEvent);
