/**
\file       except-log-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "except-log-event.hpp"

namespace libs::ilog_events::events
{
ExceptLogEvent::ExceptLogEvent (const Acessor&, const AppllPartLogInfo& appl, const std::string& info) :
  InfoLogEvent (InfoLogEvent::Acessor (0), appl, info)
{
  property_name_ = gen_get_mid ();
}


ExceptLogEvent::~ExceptLogEvent ()
{
}


::libs::events::IEvent::ptr
ExceptLogEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ExceptLogEvent > (this, deep);
}


void
ExceptLogEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (ExceptLogEvent);
  super::copy_int (src);
}


template< class Archive >
void
ExceptLogEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoilog_eventsoeventsoInfoLogEvent", super);

  self_correct ();
}
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::ExceptLogEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::events::ExceptLogEvent);
