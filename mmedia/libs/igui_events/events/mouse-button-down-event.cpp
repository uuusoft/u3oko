/**
\file       mouse-button-down-event.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_igui_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "mouse-button-down-event.hpp"

namespace libs::igui_events::events
{
MouseButtonDownEvent::MouseButtonDownEvent (const Acessor& pha, const TypeMouseButton& type, const utils::IPos::ptr& pos) :
  type_ (type),
  pos_ (pos)
{
  property_name_ = gen_get_mid ();
}


MouseButtonDownEvent::~MouseButtonDownEvent ()
{
}


TypeEvents
MouseButtonDownEvent::get_type () const
{
  return TypeEvents::mbutton_down;
}


TypeMouseButton
MouseButtonDownEvent::get_type_button () const
{
  return type_;
}


void
MouseButtonDownEvent::set_type_button (const TypeMouseButton& type)
{
  type_ = type;
  return;
}


utils::IPos::ptr
MouseButtonDownEvent::get_pos () const
{
  return pos_;
}


void
MouseButtonDownEvent::set_pos (const utils::IPos::ptr& pos)
{
  pos_ = pos;
}


::libs::events::IEvent::ptr
MouseButtonDownEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< MouseButtonDownEvent > (this, deep);
}


void
MouseButtonDownEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< MouseButtonDownEvent > (src);
  super::copy_int (src);
  type_ = dsrc->type_;
  pos_  = dsrc->pos_;
}


template< class Archive >
void
MouseButtonDownEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoeventsoBaseGUIEvent", super);
  arh& BOOST_SERIALIZATION_NVP (type_);
  // ar & BOOST_SERIALIZATION_NVP( pos_ );

  self_correct ();
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::MouseButtonDownEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::MouseButtonDownEvent);
