/**
\file       get-statistic-info.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "get-statistic-info.hpp"

namespace libs::istorage_events::events
{
GetStatisticInfo::GetStatisticInfo (const Acessor& ph) :
  use_size_ (0)
{
  property_name_ = gen_get_mid ();
}


GetStatisticInfo::~GetStatisticInfo ()
{
}


::libs::events::IEvent::ptr
GetStatisticInfo::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< GetStatisticInfo > (this, deep);
}


void
GetStatisticInfo::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (GetStatisticInfo);
  super::copy_int (src);
  use_size_ = dsrc->use_size_;
}


template< class Archive >
void
GetStatisticInfo::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoistorage_eventsoeventsoBaseStorageEvent", super);
  ar& BOOST_SERIALIZATION_NVP (use_size_);

  self_correct ();
}
}   // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::GetStatisticInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::istorage_events::events::GetStatisticInfo);
