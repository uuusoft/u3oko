/**
\file       base-log-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-log-event.hpp"

namespace libs::ilog_events::events
{
BaseLogEvent::BaseLogEvent (const BaseLogEvent::Acessor&)
{
  property_name_ = gen_get_mid ();
}


std::string
BaseLogEvent::text (const LogTexts& type) const
{
  U3_ASSERT_SIGNAL ("call BaseLogEvent::text");
  return std::string ("BaseLogEvent placeholder");
}


::libs::events::IEvent::ptr
BaseLogEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BaseLogEvent > (this, deep);
}


void
BaseLogEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseLogEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
BaseLogEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoTimedEvent", super);

  self_correct ();
}
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::BaseLogEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::events::BaseLogEvent);
