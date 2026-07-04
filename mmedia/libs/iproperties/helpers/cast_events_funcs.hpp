#pragma once
/**
\file       cast_events_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       04.08.2018
\project    u3_iproperties_lib
*/

namespace libs::iproperties::helpers
{
auto cast_event_int (const ::libs::events::IEvent::ptr&, const ::libs::events::IEvent::hid_type&) -> void*;
auto cast_event_int (const ::libs::events::IEvent::cptr&, const ::libs::events::IEvent::hid_type&) -> const void*;
auto cast_event_int (::libs::events::IEvent::raw_ptr, const ::libs::events::IEvent::hid_type&) -> void*;
auto cast_event_int (::libs::events::IEvent::craw_ptr, const ::libs::events::IEvent::hid_type&) -> const void*;

auto get_pure_event_int (const ::libs::events::IEvent::hid_type&) -> ::libs::events::IEvent::ptr;
auto get_events_impl () -> ::libs::events::io::IEvents::raw_ptr;

auto event2xml (::libs::events::IEvent::ptr&, std::string&) -> bool;
auto event2xml (::libs::events::IEvent::ptr&) -> std::string;

auto xml2event (const std::string&, ::libs::events::IEvent::ptr&) -> bool;
auto xml2event (const char*, ::libs::events::IEvent::ptr&) -> bool;

auto event2bin (::libs::events::IEvent::ptr&, std::ostream&) -> void;
auto bin2event (std::istream&, ::libs::events::IEvent::ptr&) -> bool;

auto clone_event (
  const ::libs::events::IEvent::craw_ptr,
  const ::libs::events::Deeps& = ::libs::events::Deeps::full) -> ::libs::events::IEvent::ptr;

template< typename T, typename... Args >
auto
get_event_int (const ::libs::events::IEvent::hid_type& id, Args... args) -> ::libs::events::IEvent::ptr
{
  auto impl = get_events_impl ();
  auto res  = impl->get (id);
  U3_CHECK (res, " get_event_int:: failed" + std::string { id });
  auto* upres = ::libs::utility::casts::reinterpret_cast_helper< T* > (cast_event_int (res, id));
  upres->sync_event_props (args...);
  return res;
}


template< typename T, typename... Args >
auto
create_event (::libs::events::IEvent::ptr& event, Args... args) -> T*
{
  U3_ASSERT (!event);
  constexpr const auto id = T::gen_get_mid ();

  event = get_event_int< T, Args... > (id, args...);
  return ::libs::utility::casts::reinterpret_cast_helper< T* > (cast_event_int (event, id));
}


template< typename T, typename... Args >
auto
create_event_in_list (std::list< ::libs::events::IEvent::ptr >& events, Args... args) -> T*
{
  constexpr const auto id = T::gen_get_mid ();
  events.push_back (get_event_int< T, Args... > (id, args...));
  return ::libs::utility::casts::reinterpret_cast_helper< T* > (cast_event_int (events.back (), id));
}


template< typename T >
auto
check_cast_event (const ::libs::events::IEvent::cptr& event) -> bool
{
  constexpr const auto id = T::gen_get_mid ();
  return event && ::libs::utility::casts::reinterpret_cast_helper< T* > (cast_event_int (event, id)) ? true : false;
}


template< typename T >
auto
cast_event (const ::libs::events::IEvent::ptr& event) -> T*
{
  constexpr const auto id = T::gen_get_mid ();
  U3_ASSERT_NT (event, "try cast null event to" + STOLOG (id));
  return ::libs::utility::casts::reinterpret_cast_helper< T* > (cast_event_int (event, id));
}


template< typename T >
auto
cast_event (const ::libs::events::IEvent::cptr& event) -> const T*
{
  constexpr const auto id = T::gen_get_mid ();
  U3_ASSERT_NT (event, "try cast null event to" + STOLOG (id));
  return ::libs::utility::casts::reinterpret_cast_helper< const T* > (cast_event_int (event, id));
}


template< typename T >
auto
cast_event (const ::libs::events::IEvent::raw_ptr event) -> T*
{
  constexpr const auto id = T::gen_get_mid ();
  U3_ASSERT_NT (event, "try cast null event to" + STOLOG (id));
  return ::libs::utility::casts::reinterpret_cast_helper< T* > (cast_event_int (event, id));
}


template< typename T >
auto
cast_event (const ::libs::events::IEvent::craw_ptr event) -> const T*
{
  constexpr const auto eid = T::gen_get_mid ();
  U3_ASSERT_NT (event, "try cast null event to" + STOLOG (eid));
  return ::libs::utility::casts::reinterpret_cast_helper< const T* > (cast_event_int (event, eid));
}

// проверка овзможности создания указанного объекта
template< typename TTEvent >
auto
make_stub_obj () -> void
{
  volatile const auto temp = std::make_unique< TTEvent > ();
}


template< typename TTEvent >
auto
dbg_check_copy_event (const ::libs::events::IEvent::craw_ptr src) -> const TTEvent*
{
  auto* res = ::libs::iproperties::helpers::cast_event< TTEvent > (src);
  U3_CHECK (res, std::string ("invalid event type") + PTR_TOLOG (src) + " empty " + PTR_TOLOG (res));
  return res;
}
}   // namespace libs::iproperties::helpers
