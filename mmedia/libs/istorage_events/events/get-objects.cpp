/**
\file       get-objects.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "get-objects.hpp"

namespace libs::istorage_events::events
{
GetObjects::GetObjects (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
GetObjects::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (path_id_);
  arh& BOOST_SERIALIZATION_NVP (objs_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::GetObjects);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::GetObjects);
