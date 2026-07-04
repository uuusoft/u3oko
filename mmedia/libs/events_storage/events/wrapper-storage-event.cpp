/**
\file       wrapper-storage-event.cpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-storage-includes_int.hpp"
#include "wrapper-storage-event.hpp"

namespace libs::events_storage::events
{
WrapperStorageEvent::WrapperStorageEvent (const Acessor& pha, ::libs::events::IEvent::ptr msg) :
  int_ (std::move (msg))
{
}


auto
WrapperStorageEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return WrapperStorageEvent::gen_get_mid ();
}


auto
WrapperStorageEvent::get_msg () const -> ::libs::events::IEvent::ptr
{
  return int_;
}


void
WrapperStorageEvent::set_msg (::libs::events::IEvent::ptr& msg)
{
  int_ = msg;
}


auto
WrapperStorageEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< WrapperStorageEvent > (this, deep);
}


void
WrapperStorageEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< WrapperStorageEvent > (src);
  super::copy_int (src);

  int_ = dsrc->int_;
}


template< class Archive >
void
WrapperStorageEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_storageoeventsoBaseStorageEvent", super);
  arh& BOOST_SERIALIZATION_NVP (int_);

  self_correct ();
}
}   // namespace libs::events_storage::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_storage::events::WrapperStorageEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_storage::events::WrapperStorageEvent);
