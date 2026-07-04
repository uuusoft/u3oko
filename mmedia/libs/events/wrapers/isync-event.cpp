/**
\file       isync-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "../includes_int.hpp"
#include "isync-event.hpp"

namespace libs::events
{
ISyncEvent::ISyncEvent (const Acessor& pha, IEvent::ptr val) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), std::move (val))
{
}


auto
ISyncEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ISyncEvent::gen_get_mid ();
}


auto
ISyncEvent::clone_int (const ::libs::events::Deeps& deep) const -> IEvent::ptr
{
  return ::libs::events::deep_clone< ISyncEvent > (this, deep);
}


void
ISyncEvent::copy_int (const IEvent::craw_ptr src)
{
  ::libs::iproperties::helpers::dbg_check_copy_event< ISyncEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
ISyncEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("IWrapBaseEvent", super);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::ISyncEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events::ISyncEvent);
