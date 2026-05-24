/**
\file       irequest-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "irequest-event.hpp"

namespace libs::events
{
IRequestEvent::IRequestEvent (const Acessor& ph, IEvent::ptr val) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), val)
{
  property_name_ = gen_get_mid ();
}


IRequestEvent::~IRequestEvent ()
{
}


IEvent::ptr
IRequestEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< IRequestEvent > (this, deep);
}


void
IRequestEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (IRequestEvent);
  super::copy_int (src);
}


template< class Archive >
void
IRequestEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("IWrapBaseEvent", super);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IRequestEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::events::IRequestEvent);
