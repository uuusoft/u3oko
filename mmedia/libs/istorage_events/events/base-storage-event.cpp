/**
\file       base-storage-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "base-storage-event.hpp"

namespace libs::istorage_events::events
{
BaseStorageEvent::BaseStorageEvent (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


BaseStorageEvent::~BaseStorageEvent ()
{
}


::libs::events::IEvent::ptr
BaseStorageEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BaseStorageEvent > (this, deep);
}


void
BaseStorageEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (BaseStorageEvent);
  super::copy_int (src);
}


template< class Archive >
void
BaseStorageEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoTimedEvent", super);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::BaseStorageEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::BaseStorageEvent);
