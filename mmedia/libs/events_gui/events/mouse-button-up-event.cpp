/**
\file       MouseButtonUpEvent.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "mouse-button-up-event.hpp"

namespace libs::events_gui::events
{
MouseButtonUpEvent::MouseButtonUpEvent (const Acessor& pha, const TypeMouseButton& type, utils::IPos::ptr pos) :
  type_ (type),
  pos_ (std::move (pos))
{
}


MouseButtonUpEvent::~MouseButtonUpEvent () = default;


auto
MouseButtonUpEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return MouseButtonUpEvent::gen_get_mid ();
}


auto
MouseButtonUpEvent::get_type () const -> TypeEvents
{
  return TypeEvents::mbutton_up;
}


auto
MouseButtonUpEvent::get_type_button () const -> TypeMouseButton
{
  return type_;
}


void
MouseButtonUpEvent::set_type_button (const TypeMouseButton& type)
{
  type_ = type;
}


auto
MouseButtonUpEvent::get_pos () const -> utils::IPos::ptr
{
  return pos_;
}


void
MouseButtonUpEvent::set_pos (const utils::IPos::ptr& pos)
{
  pos_ = pos;
  return;
}


auto
MouseButtonUpEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< MouseButtonUpEvent > (this, deep);
}


void
MouseButtonUpEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< MouseButtonUpEvent > (src);
  super::copy_int (src);
  type_ = dsrc->type_;
  pos_  = dsrc->pos_;
}


template< class Archive >
void
MouseButtonUpEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_guioeventsoBaseGUIEvent", super);
  arh& BOOST_SERIALIZATION_NVP (type_);
  // ar & BOOST_SERIALIZATION_NVP( pos_ );
}
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_gui::events::MouseButtonUpEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_gui::events::MouseButtonUpEvent);
