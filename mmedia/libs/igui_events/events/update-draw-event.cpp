/**
\file       UpdateDrawEvent.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    uuu_igui_evenets
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "update-draw-event.hpp"

namespace libs::igui_events::events
{
UpdateDrawEvent::UpdateDrawEvent (const Acessor& ph)
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
  U3_CHECK_COPY_EVENT (UpdateDrawEvent);
  super::copy_int (src);
}


template< class Archive >
void
UpdateDrawEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoeventsoBaseGUIEvent", super);
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::UpdateDrawEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::UpdateDrawEvent);
