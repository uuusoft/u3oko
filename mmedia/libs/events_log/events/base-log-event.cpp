/**
\file       base-log-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "base-log-event.hpp"

namespace libs::events_log::events
{
BaseLogEvent::BaseLogEvent (const BaseLogEvent::Acessor&)
{
}


auto
BaseLogEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BaseLogEvent::gen_get_mid ();
}


auto
BaseLogEvent::text (const LogTexts& type) const -> std::string
{
  U3_ASSERT_SIGNAL ("call BaseLogEvent::text");
  return std::string ("BaseLogEvent placeholder");
}


auto
BaseLogEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoTimedEvent", super);

  self_correct ();
}
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_log::events::BaseLogEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_log::events::BaseLogEvent);
