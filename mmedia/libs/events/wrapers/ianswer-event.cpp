/**
\file       ianswer-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "ianswer-event.hpp"

namespace libs::events
{
IAnswerEvent::IAnswerEvent (const Acessor& ph, IEvent::ptr val) :
  IWrapBaseEvent (IWrapBaseEvent::Acessor (0), val)
{
  property_name_ = gen_get_mid ();
}


IAnswerEvent::~IAnswerEvent ()
{
}


IEvent::ptr
IAnswerEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< IAnswerEvent > (this, deep);
}


void
IAnswerEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (IAnswerEvent);
  super::copy_int (src);
}


template< class Archive >
void
IAnswerEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("IWrapBaseEvent", super);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IAnswerEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::events::IAnswerEvent);
