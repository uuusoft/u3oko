/**
\file       command-code-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_igui_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "command-code-event.hpp"

namespace libs::igui_events::events
{
CommandCodeEvent::CommandCodeEvent (const Acessor& pha, const std::string& code) :
  code_ (code)
{
  U3_ASSERT (!code_.empty ());
  property_name_ = gen_get_mid ();
}


CommandCodeEvent::~CommandCodeEvent ()
{
}


TypeEvents
CommandCodeEvent::get_type () const
{
  return TypeEvents::command_code;
}


std::string
CommandCodeEvent::get_code () const
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


::libs::events::IEvent::ptr
CommandCodeEvent::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoeventsoBaseGUIEvent", super);
  arh& BOOST_SERIALIZATION_NVP (code_);

  self_correct ();
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::CommandCodeEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::CommandCodeEvent);
