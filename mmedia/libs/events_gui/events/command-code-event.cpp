/**
\file       command-code-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "command-code-event.hpp"

namespace libs::events_gui::events
{
CommandCodeEvent::CommandCodeEvent (const Acessor& pha, std::string code) :
  code_ (std::move (code))
{
  U3_ASSERT (!code_.empty ());
}


CommandCodeEvent::~CommandCodeEvent () = default;


auto
CommandCodeEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return CommandCodeEvent::gen_get_mid ();
}


auto
CommandCodeEvent::get_type () const -> TypeEvents
{
  return TypeEvents::command_code;
}


auto
CommandCodeEvent::get_code () const -> std::string
{
  U3_ASSERT (!code_.empty ());
  return code_;
}


void
CommandCodeEvent::set_code (const std::string& id)
{
  U3_ASSERT (!id.empty ());
  code_ = id;
}


auto
CommandCodeEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< CommandCodeEvent > (this, deep);
}


void
CommandCodeEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< CommandCodeEvent > (src);
  super::copy_int (src);
  code_ = dsrc->code_;
}


template< class Archive >
void
CommandCodeEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_guioeventsoBaseGUIEvent", super);
  arh& BOOST_SERIALIZATION_NVP (code_);

  self_correct ();
}
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_gui::events::CommandCodeEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_gui::events::CommandCodeEvent);
