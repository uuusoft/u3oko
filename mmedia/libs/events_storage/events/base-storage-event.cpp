/**
\file       base-storage-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2018
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-storage-includes_int.hpp"
#include "base-storage-event.hpp"

namespace libs::events_storage::events
{
BaseStorageEvent::BaseStorageEvent (const Acessor& pha)
{
}


auto
BaseStorageEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseStorageEvent::gen_get_mid ();
}


auto
BaseStorageEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BaseStorageEvent > (this, deep);
}


void
BaseStorageEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseStorageEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
BaseStorageEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoTimedEvent", super);

  self_correct ();
}
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_storage::events::BaseStorageEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_storage::events::BaseStorageEvent);
