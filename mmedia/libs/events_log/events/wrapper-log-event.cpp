/**
\file       wrapper-log-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "wrapper-log-event.hpp"

namespace libs::events_log::events
{
WrapperLogEvent::WrapperLogEvent (const Acessor&, ::libs::events::IEvent::ptr msg) :
  int_ (std::move (msg))
{
}


auto
WrapperLogEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return WrapperLogEvent::gen_get_mid ();
}


auto
WrapperLogEvent::get_msg () const -> ::libs::events::IEvent::ptr
{
  return int_;
}


void
WrapperLogEvent::set_msg (::libs::events::IEvent::ptr& msg)
{
  int_ = msg;
}


auto
WrapperLogEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< WrapperLogEvent > (this, deep);
}


void
WrapperLogEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< WrapperLogEvent > (src);
  super::copy_int (src);
  int_ = dsrc->int_;
}


template< class Archive >
void
WrapperLogEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoTimedEvent", super);
  arh& BOOST_SERIALIZATION_NVP (int_);

  self_correct ();
}
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_log::events::WrapperLogEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_log::events::WrapperLogEvent);
