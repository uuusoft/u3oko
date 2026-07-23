/**
\file       ExitApplEvent.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "exit-appl-event.hpp"

namespace libs::events_gui::events
{
ExitApplEvent::ExitApplEvent (const Acessor& pha)
{
}


ExitApplEvent::~ExitApplEvent () = default;


auto
ExitApplEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ExitApplEvent::gen_get_mid ();
}


auto
ExitApplEvent::get_type () const -> TypeEvents
{
  return TypeEvents::exit_appl;
}


auto
ExitApplEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_guioeventsoBaseGUIEvent", super);

  self_correct ();
}
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_gui::events::ExitApplEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_gui::events::ExitApplEvent);
