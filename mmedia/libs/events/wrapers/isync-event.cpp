/**
\file       isync-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "isync-event.hpp"

namespace libs::events
{
ISyncEvent::ISyncEvent (const Acessor& pha, IEvent::ptr val) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), val)
{
  property_name_ = gen_get_mid ();
}


IEvent::ptr
ISyncEvent::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("IWrapBaseEvent", super);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::ISyncEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::events::ISyncEvent);
