/**
\file       get-objects.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-storage-includes_int.hpp"
#include "get-objects.hpp"

namespace libs::events_storage::events
{
GetObjects::GetObjects (const Acessor& pha)
{
}


auto
GetObjects::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return GetObjects::gen_get_mid ();
}


auto
GetObjects::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< GetObjects > (this, deep);
}


void
GetObjects::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GetObjects > (src);
  super::copy_int (src);

  path_id_ = dsrc->path_id_;
  objs_    = dsrc->objs_;
}


template< class Archive >
void
GetObjects::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_storageoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (path_id_);
  arh& BOOST_SERIALIZATION_NVP (objs_);

  self_correct ();
}
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_storage::events::GetObjects);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_storage::events::GetObjects);
