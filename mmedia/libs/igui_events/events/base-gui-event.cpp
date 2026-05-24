/**
\file       base-gui-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    uuu_igui_evenets
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-gui-event.hpp"
#include "type-events.hpp"

namespace libs::igui_events::events
{
BaseGUIEvent::BaseGUIEvent (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


BaseGUIEvent::~BaseGUIEvent ()
{
}


TypeEvents
BaseGUIEvent::get_type () const
{
  return TypeEvents::mem_block;
}


::libs::events::IEvent::ptr
BaseGUIEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BaseGUIEvent > (this, deep);
}


void
BaseGUIEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (BaseGUIEvent);
  super::copy_int (src);
}


template< class Archive >
void
BaseGUIEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  self_correct ();
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::BaseGUIEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::BaseGUIEvent);
