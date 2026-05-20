/**
\file       base-http-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    uuu_ihttp_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-http-event.hpp"

namespace libs::ihttp_events::events
{
BaseHttpEvent::BaseHttpEvent (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


BaseHttpEvent::~BaseHttpEvent ()
{
}


::libs::events::IEvent::ptr
BaseHttpEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BaseHttpEvent > (this, deep);
}


void
BaseHttpEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (BaseHttpEvent);
  super::copy_int (src);
}


template< class Archive >
void
BaseHttpEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoTimedEvent", super);

  self_correct ();
}
}   // namespace libs::ihttp_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ihttp_events::events::BaseHttpEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ihttp_events::events::BaseHttpEvent);
