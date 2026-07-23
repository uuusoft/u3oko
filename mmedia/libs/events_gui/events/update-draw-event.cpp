/**
\file       UpdateDrawEvent.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "update-draw-event.hpp"

namespace libs::events_gui::events
{
UpdateDrawEvent::UpdateDrawEvent (const Acessor& pha)
{
}


UpdateDrawEvent::~UpdateDrawEvent () = default;


auto
UpdateDrawEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return UpdateDrawEvent::gen_get_mid ();
}


auto
UpdateDrawEvent::get_type () const -> TypeEvents
{
  return TypeEvents::update_draw;
}


auto
UpdateDrawEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< UpdateDrawEvent > (this, deep);
}


void
UpdateDrawEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< UpdateDrawEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
UpdateDrawEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_guioeventsoBaseGUIEvent", super);
}
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_gui::events::UpdateDrawEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_gui::events::UpdateDrawEvent);
