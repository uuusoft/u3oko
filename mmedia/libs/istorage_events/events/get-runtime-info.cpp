/**
\file       get-runtime-info.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "get-runtime-info.hpp"

namespace libs::istorage_events::events
{
GetRuntimeInfo::GetRuntimeInfo (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


GetRuntimeInfo::~GetRuntimeInfo ()
{
}


::libs::events::IEvent::ptr
GetRuntimeInfo::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< GetRuntimeInfo > (this, deep);
}


void
GetRuntimeInfo::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (GetRuntimeInfo);
  super::copy_int (src);
  id_path_      = dsrc->id_path_;
  stream_infos_ = dsrc->stream_infos_;
}


template< class Archive >
void
GetRuntimeInfo::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  ar& BOOST_SERIALIZATION_NVP (id_path_);
  ar& BOOST_SERIALIZATION_NVP (stream_infos_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::GetRuntimeInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::GetRuntimeInfo);
