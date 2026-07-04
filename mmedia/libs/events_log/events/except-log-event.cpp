/**
\file       except-log-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "except-log-event.hpp"

namespace libs::events_log::events
{
ExceptLogEvent::ExceptLogEvent (const Acessor&, const AppllPartLogInfo& appl, const std::string& info) :
  InfoLogEvent (InfoLogEvent::Acessor (0), appl, info)
{
}


auto
ExceptLogEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ExceptLogEvent::gen_get_mid ();
}


auto
ExceptLogEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ExceptLogEvent > (this, deep);
}


void
ExceptLogEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ExceptLogEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
ExceptLogEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_logoeventsoInfoLogEvent", super);

  self_correct ();
}
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_log::events::ExceptLogEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_log::events::ExceptLogEvent);
