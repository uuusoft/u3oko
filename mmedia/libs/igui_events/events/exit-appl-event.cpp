/**
\file       ExitApplEvent.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "exit-appl-event.hpp"

namespace libs::igui_events::events
{
ExitApplEvent::ExitApplEvent (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


ExitApplEvent::~ExitApplEvent ()
{
}


TypeEvents
ExitApplEvent::get_type () const
{
  return TypeEvents::exit_appl;
}


::libs::events::IEvent::ptr
ExitApplEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ExitApplEvent > (this, deep);
}


void
ExitApplEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ExitApplEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
ExitApplEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoeventsoBaseGUIEvent", super);

  self_correct ();
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::ExitApplEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::ExitApplEvent);
