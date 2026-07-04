/**
\file       wrapper-user-event.cpp
\date       01.06.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_user
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-user-includes_int.hpp"
#include "wrapper-user-event.hpp"

namespace libs::events_user::events
{
WrapperUserEvent::WrapperUserEvent (const Acessor& pha, ::libs::events::IEvent::ptr msg) :
  int_ (msg)
{
}


auto
WrapperUserEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return WrapperUserEvent::gen_get_mid ();
}


::libs::events::IEvent::ptr
WrapperUserEvent::get_msg () const
{
  return int_;
}


void
WrapperUserEvent::set_msg (::libs::events::IEvent::ptr& msg)
{
  int_ = msg;
}


::libs::events::IEvent::ptr
WrapperUserEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< WrapperUserEvent > (this, deep);
}


void
WrapperUserEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< WrapperUserEvent > (src);
  super::copy_int (src);

  int_ = dsrc->int_;
}


template< class Archive >
void
WrapperUserEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_useroeventsoBaseUserEvent", super);
  arh& BOOST_SERIALIZATION_NVP (int_);

  self_correct ();
}
}   // namespace libs::events_user::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_user::events::WrapperUserEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_user::events::WrapperUserEvent);
