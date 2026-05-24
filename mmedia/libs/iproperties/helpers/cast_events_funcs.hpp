#pragma once
/**
\file       cast_events_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       04.08.2018
\project    u3_iproperties_lib
*/

namespace libs::iproperties::helpers
{
#ifndef U3_CAST_FORCE_EVENT_INT
#  define U3_CAST_FORCE_EVENT_INT(ptr, type) reinterpret_cast< type > (ptr)
#endif

void* cast_event_int (const ::libs::events::IEvent::ptr& event, const ::libs::events::IEvent::hid_type& id);
void* cast_event_int (const ::libs::events::IEvent::cptr& event, const ::libs::events::IEvent::hid_type& id);
void* cast_event_int (::libs::events::IEvent::raw_ptr event, const ::libs::events::IEvent::hid_type& id);
void* cast_event_int (::libs::events::IEvent::craw_ptr event, const ::libs::events::IEvent::hid_type& id);

::libs::events::IEvent::ptr          get_pure_event_int (const ::libs::events::IEvent::hid_type&);
::libs::events::io::IEvents::raw_ptr get_events_impl ();

template< typename T, typename... Args >
::libs::events::IEvent::ptr
get_event_int (const ::libs::events::IEvent::hid_type& id, Args... args)
{
  auto impl = get_events_impl ();
  auto res  = impl->get (id);
  U3_CHECK (res, "get_event_int:" + id);
  auto res2 = U3_CAST_FORCE_EVENT_INT (cast_event_int (res, id), T*);
  res2->sync_event_props (args...);
  return res;
}


template< typename T, typename... Args >
T*
create_event (::libs::events::IEvent::ptr& event, Args... args)
{
  U3_ASSERT (!event);
  const auto id = T::gen_get_mid ();
  event         = get_event_int< T, Args... > (id, args...);
  return U3_CAST_FORCE_EVENT_INT (cast_event_int (event, id), T*);
}


template< typename T, typename... Args >
T*
create_event_in_list (std::list< ::libs::events::IEvent::ptr >& events, Args... args)
{
  const auto id = T::gen_get_mid ();
  events.push_back (get_event_int< T, Args... > (id, args...));
  return U3_CAST_FORCE_EVENT_INT (cast_event_int (events.back (), id), T*);
}


template< typename T >
T*
cast_event (const ::libs::events::IEvent::cptr& event)
{
  U3_ASSERT (event);
  const auto id = T::gen_get_mid ();
  return U3_CAST_FORCE_EVENT_INT (cast_event_int (event, id), T*);
}


template< typename T >
T*
cast_event (::libs::events::IEvent::raw_ptr event)
{
  U3_ASSERT (event);
  const auto id = T::gen_get_mid ();
  return U3_CAST_FORCE_EVENT_INT (cast_event_int (event, id), T*);
}


template< typename T >
const T*
cast_event (::libs::events::IEvent::craw_ptr event)
{
  U3_ASSERT (event);
  const auto id = T::gen_get_mid ();
  return U3_CAST_FORCE_EVENT_INT (cast_event_int (event, id), const T*);
}

bool        event2xml (::libs::events::IEvent::ptr& src, std::string& xml);
std::string event2xml (::libs::events::IEvent::ptr& src);

bool xml2event (const std::string& xml, ::libs::events::IEvent::ptr& dst);
bool xml2event (const char* xml, ::libs::events::IEvent::ptr& dst);

void event2bin (::libs::events::IEvent::ptr& src, std::ostream& bin);
bool bin2event (std::istream& bin, ::libs::events::IEvent::ptr& dst);

::libs::events::IEvent::ptr clone_event (const ::libs::events::IEvent::craw_ptr, const ::libs::events::Deeps& = ::libs::events::Deeps::full);
}   // namespace libs::iproperties::helpers
