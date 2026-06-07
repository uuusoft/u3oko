/**
\file       UpdateDrawEvent.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_igui_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "update-draw-event.hpp"

namespace libs::igui_events::events
{
UpdateDrawEvent::UpdateDrawEvent (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


UpdateDrawEvent::~UpdateDrawEvent ()
{
}


TypeEvents
UpdateDrawEvent::get_type () const
{
  return TypeEvents::update_draw;
}


::libs::events::IEvent::ptr
UpdateDrawEvent::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoeventsoBaseGUIEvent", super);
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::UpdateDrawEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::UpdateDrawEvent);
