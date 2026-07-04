/**
\file       base-gui-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-gui-event.hpp"
#include "type-events.hpp"

namespace libs::events_gui::events
{
BaseGUIEvent::BaseGUIEvent (const Acessor& pha)
{
}


BaseGUIEvent::~BaseGUIEvent () = default;


auto
BaseGUIEvent::get_type () const -> TypeEvents
{
  return TypeEvents::mem_block;
}


auto
BaseGUIEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseGUIEvent::gen_get_mid ();
}


auto
BaseGUIEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseGUIEvent > (this, deep);
}


void
BaseGUIEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseGUIEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
BaseGUIEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);

  self_correct ();
}
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_gui::events::BaseGUIEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_gui::events::BaseGUIEvent);
