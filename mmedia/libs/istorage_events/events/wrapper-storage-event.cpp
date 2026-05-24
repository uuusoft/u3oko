/**
\file       wrapper-storage-event.cpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "wrapper-storage-event.hpp"

namespace libs::istorage_events::events
{
WrapperStorageEvent::WrapperStorageEvent (const Acessor& ph, ::libs::events::IEvent::ptr msg) :
  int_ (msg)
{
  property_name_ = gen_get_mid ();
}


WrapperStorageEvent::~WrapperStorageEvent ()
{
}


::libs::events::IEvent::ptr
WrapperStorageEvent::get_msg () const
{
  return int_;
}


void
WrapperStorageEvent::set_msg (::libs::events::IEvent::ptr& msg)
{
  int_ = msg;
}


::libs::events::IEvent::ptr
WrapperStorageEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< WrapperStorageEvent > (this, deep);
}


void
WrapperStorageEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (WrapperStorageEvent);
  super::copy_int (src);
  int_ = dsrc->int_;
}


template< class Archive >
void
WrapperStorageEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  ar& BOOST_SERIALIZATION_NVP (int_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::WrapperStorageEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::WrapperStorageEvent);
