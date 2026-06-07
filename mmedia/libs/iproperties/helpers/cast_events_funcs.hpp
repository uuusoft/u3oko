#pragma once
/**
\file       cast_events_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       04.08.2018
\project    u3_iproperties_lib
*/

namespace libs::iproperties::helpers
{
void* cast_event_int (const ::libs::events::IEvent::ptr& event, const ::libs::events::IEvent::hid_type& id);
void* cast_event_int (const ::libs::events::IEvent::cptr& event, const ::libs::events::IEvent::hid_type& id);
void* cast_event_int (::libs::events::IEvent::raw_ptr event, const ::libs::events::IEvent::hid_type& id);
void* cast_event_int (::libs::events::IEvent::craw_ptr event, const ::libs::events::IEvent::hid_type& id);

::libs::events::IEvent::ptr          get_pure_event_int (const ::libs::events::IEvent::hid_type&);
::libs::events::io::IEvents::raw_ptr get_events_impl ();

template< typename T, typename... Args >
auto
get_event_int (const ::libs::events::IEvent::hid_type& id, Args... args) -> ::libs::events::IEvent::ptr
{
  auto impl = get_events_impl ();
  auto res  = impl->get (id);
  U3_CHECK (res, "get_event_int:" + id);
  auto res2 = ::libs::helpers::casts::reinterpret_cast_helper< T* > (cast_event_int (res, id));
  res2->sync_event_props (args...);
  return res;
}


template< typename T, typename... Args >
auto
create_event (::libs::events::IEvent::ptr& event, Args... args) -> T*
{
  U3_ASSERT (!event);
  const auto id = T::gen_get_mid ();
  event         = get_event_int< T, Args... > (id, args...);
  return ::libs::helpers::casts::reinterpret_cast_helper< T* > (cast_event_int (event, id));
}


template< typename T, typename... Args >
auto
create_event_in_list (std::list< ::libs::events::IEvent::ptr >& events, Args... args) -> T*
{
  const auto id = T::gen_get_mid ();
  events.push_back (get_event_int< T, Args... > (id, args...));
  return ::libs::helpers::casts::reinterpret_cast_helper< T* > (cast_event_int (events.back (), id));
}


template< typename T >
auto
cast_event (const ::libs::events::IEvent::cptr& event) -> T*
{
  U3_ASSERT (event);
  const auto id = T::gen_get_mid ();
  return ::libs::helpers::casts::reinterpret_cast_helper< T* > (cast_event_int (event, id));
}


template< typename T >
auto
cast_event (::libs::events::IEvent::raw_ptr event) -> T*
{
  U3_ASSERT (event);
  const auto id = T::gen_get_mid ();
  return ::libs::helpers::casts::reinterpret_cast_helper< T* > (cast_event_int (event, id));
}


template< typename T >
auto
cast_event (::libs::events::IEvent::craw_ptr event) -> const T*
{
  U3_ASSERT (event);
  const auto id = T::gen_get_mid ();
  return ::libs::helpers::casts::reinterpret_cast_helper< T* > (cast_event_int (event, id));
}


template< typename TTEvent >
auto
make_fake_obj_this_type () -> void
{
  volatile const typename TTEvent::ptr temp = std::make_shared< TTEvent > ();
}


template< typename TTEvent >
auto
make_fake_obj_this_event_type () -> void
{
  volatile typename TTEvent::ptr temp = TTEvent::make_shared_this ();
}


template< typename TTEvent >
auto
dbg_check_copy_event (const ::libs::events::IEvent::craw_ptr src) -> const TTEvent*
{
  auto res = ::libs::iproperties::helpers::cast_event< TTEvent > (src);
  U3_CHECK (res, std::string ("invalid event type") + PTR_TOLOG (src) + " empty " + PTR_TOLOG (res));
  return res;
}

bool        event2xml (::libs::events::IEvent::ptr& src, std::string& xml);
std::string event2xml (::libs::events::IEvent::ptr& src);

bool xml2event (const std::string& xml, ::libs::events::IEvent::ptr& dst);
bool xml2event (const char* xml, ::libs::events::IEvent::ptr& dst);

void event2bin (::libs::events::IEvent::ptr& src, std::ostream& bin);
bool bin2event (std::istream& bin, ::libs::events::IEvent::ptr& dst);

::libs::events::IEvent::ptr clone_event (const ::libs::events::IEvent::craw_ptr, const ::libs::events::Deeps& = ::libs::events::Deeps::full);
}   // namespace libs::iproperties::helpers
