/**
\file       irequest-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "../includes_int.hpp"
#include "irequest-event.hpp"

namespace libs::events
{
IRequestEvent::IRequestEvent (const Acessor& pha, IEvent::ptr val) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), std::move (val))
{
}


auto
IRequestEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return IRequestEvent::gen_get_mid ();
}


auto
IRequestEvent::clone_int (const ::libs::events::Deeps& deep) const -> IEvent::ptr
{
  return ::libs::events::deep_clone< IRequestEvent > (this, deep);
}


void
IRequestEvent::copy_int (const IEvent::craw_ptr src)
{
  ::libs::iproperties::helpers::dbg_check_copy_event< IRequestEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
IRequestEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("IWrapBaseEvent", super);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IRequestEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events::IRequestEvent);
