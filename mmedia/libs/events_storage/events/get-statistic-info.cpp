/**
\file       get-statistic-info.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-storage-includes_int.hpp"
#include "get-statistic-info.hpp"

namespace libs::events_storage::events
{
GetStatisticInfo::GetStatisticInfo (const Acessor& pha)
{
}


auto
GetStatisticInfo::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return GetStatisticInfo::gen_get_mid ();
}


auto
GetStatisticInfo::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< GetStatisticInfo > (this, deep);
}


void
GetStatisticInfo::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GetStatisticInfo > (src);
  super::copy_int (src);

  use_size_ = dsrc->use_size_;
}


template< class Archive >
void
GetStatisticInfo::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_storageoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (use_size_);

  self_correct ();
}
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_storage::events::GetStatisticInfo);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_storage::events::GetStatisticInfo);
