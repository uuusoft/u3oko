/**
\file       SizeChangedEvent.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_igui_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "size-changed-event.hpp"

namespace libs::igui_events::events
{
SizeChangedEvent::SizeChangedEvent (const Acessor& pha, const ::libs::igui_events::utils::ISize::ptr& size) :
  size_ (size)
{
  property_name_ = gen_get_mid ();
}


SizeChangedEvent::~SizeChangedEvent ()
{
}


TypeEvents
SizeChangedEvent::get_type () const
{
  return TypeEvents::size_changed;
}


::libs::igui_events::utils::ISize::ptr
SizeChangedEvent::get_size () const
{
  return size_;
}


void
SizeChangedEvent::set_size (const ::libs::igui_events::utils::ISize::ptr& size)
{
  size_ = size;
  return;
}


::libs::events::IEvent::ptr
SizeChangedEvent::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoigui_eventsoeventsoBaseGUIEvent", super);
  // ar & BOOST_SERIALIZATION_NVP( size_ );
}
}   // namespace libs::igui_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::igui_events::events::SizeChangedEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::igui_events::events::SizeChangedEvent);
