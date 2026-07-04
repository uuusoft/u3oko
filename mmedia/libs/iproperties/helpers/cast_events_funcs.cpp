/**
\file       cast_events_funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       04.08.2018
\project    u3_iproperties_lib
*/
#include "../libs-iproperties-includes_int.hpp"
#include "cast_events_funcs.hpp"

namespace libs::iproperties::helpers
{
auto
get_events_impl () -> ::libs::events::io::IEvents::raw_ptr
{
  auto* events = ::libs::iproperties::helpers::cast_prop_demons ()->get_events_lockfree ();
  U3_CHECK (events, "empty events");
  auto* impl = events->impl ();
  U3_CHECK (impl, "empty events impl");
  return impl;
}


auto
get_pure_event_int (const ::libs::events::IEvent::hid_type& eid) -> ::libs::events::IEvent::ptr
{
  auto* impl = get_events_impl ();
  auto  res  = impl->get (eid);
  U3_CHECK (res, "get_pure_event_int:" + STOLOG (eid));
  return res;
}

#if 1
auto
cast_event_int (const ::libs::events::IEvent::ptr& event, const ::libs::events::IEvent::hid_type& eid) -> void*
{
  if (!event)
  {
    return nullptr;
  }
  auto* impl = get_events_impl ();
  auto* res  = impl->dcast (event.get (), eid);
  return const_cast< void* > (res);
}
#endif

auto
cast_event_int (const ::libs::events::IEvent::cptr& event, const ::libs::events::IEvent::hid_type& eid) -> const void*
{
  if (!event)
  {
    return nullptr;
  }
  auto* impl = get_events_impl ();
  auto* res  = impl->dcast (event.get (), eid);
  return res;
}

#if 1
auto
cast_event_int (::libs::events::IEvent::raw_ptr event, const ::libs::events::IEvent::hid_type& eid) -> void*
{
  if (!event)
  {
    return nullptr;
  }
  auto* impl = get_events_impl ();
  auto* res  = impl->dcast (event, eid);
  return const_cast< void* > (res);
}
#endif

auto
cast_event_int (::libs::events::IEvent::craw_ptr event, const ::libs::events::IEvent::hid_type& eid) -> const void*
{
  if (!event)
  {
    return nullptr;
  }
  auto* impl = get_events_impl ();
  auto* res  = impl->dcast (event, eid);
  return res;
}


auto
event2xml (::libs::events::IEvent::ptr& src, std::string& xml) -> bool
{
  auto* impl = get_events_impl ();
  return impl->event2xml (src, xml);
}


auto
event2xml (::libs::events::IEvent::ptr& src) -> std::string
{
  if (!src)
  {
    return "";
  }

  auto*       impl = get_events_impl ();
  std::string xml;
  U3_CHECK (impl->event2xml (src, xml), "event2xml - " + STOLOG (src->get_mid ()));
  return xml;
}


auto
xml2event (const std::string& xml, ::libs::events::IEvent::ptr& dst) -> bool
{
  auto* impl = get_events_impl ();
  return impl->xml2event (xml, dst);
}


auto
xml2event (const char* xml, ::libs::events::IEvent::ptr& dst) -> bool
{
  auto* impl = get_events_impl ();
  return impl->xml2event (std::string (xml), dst);
}


void
event2bin (::libs::events::IEvent::ptr& src, std::ostream& bin)
{
  auto* impl = get_events_impl ();
  U3_CHECK (impl->event2bin (src, bin), "event2bin - " + STOLOG (src->get_mid ()));
}


auto
bin2event (std::istream& bin, ::libs::events::IEvent::ptr& dst) -> bool
{
  auto* impl = get_events_impl ();
  return impl->bin2event (bin, dst);
}


auto
clone_event (const ::libs::events::IEvent::craw_ptr event, const ::libs::events::Deeps& type) -> ::libs::events::IEvent::ptr
{
  U3_ASSERT (event);
  auto* impl = get_events_impl ();
  return impl->clone (event, type);
}
}   // namespace libs::iproperties::helpers
