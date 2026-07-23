/**
\file       SizeChangedEvent.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "size-changed-event.hpp"

namespace libs::events_gui::events
{
SizeChangedEvent::SizeChangedEvent (const Acessor& pha, ::libs::events_gui::utils::ISize::ptr size) :
  size_ (std::move (size))
{
}


SizeChangedEvent::~SizeChangedEvent () = default;


auto
SizeChangedEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return SizeChangedEvent::gen_get_mid ();
}


auto
SizeChangedEvent::get_type () const -> TypeEvents
{
  return TypeEvents::size_changed;
}


auto
SizeChangedEvent::get_size () const -> ::libs::events_gui::utils::ISize::ptr
{
  return size_;
}


void
SizeChangedEvent::set_size (const ::libs::events_gui::utils::ISize::ptr& size)
{
  size_ = size;
  return;
}


auto
SizeChangedEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< SizeChangedEvent > (this, deep);
}


void
SizeChangedEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< SizeChangedEvent > (src);
  super::copy_int (src);
  size_ = dsrc->size_;
}


template< class Archive >
void
SizeChangedEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_guioeventsoBaseGUIEvent", super);
  // ar & BOOST_SERIALIZATION_NVP( size_ );
}
}   // namespace libs::events_gui::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_gui::events::SizeChangedEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_gui::events::SizeChangedEvent);
