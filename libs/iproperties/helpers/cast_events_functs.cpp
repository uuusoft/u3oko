/**
\file       cast_events_functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       04.08.2018
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      Набор вспомогательных функций доступа к конкретным свойствам для упрощения кода.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "cast_events_functs.hpp"

namespace libs { namespace iproperties { namespace helpers {

::libs::events::io::IEvents::raw_ptr
get_events_impl ()
{
  auto _events = UUU_PROP_CAST (vers::demon::IDemonsProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_demons ())->get_events_lockfree ();
  UASSERT (_events);
  auto _impl = _events->impl ();
  UASSERT (_impl);
  return _impl;
}


::libs::events::IEvent::ptr
get_event_int (const ::libs::events::IEvent::text_id_type& _id)
{
  auto _impl = get_events_impl ();
  auto _res  = _impl->get (_id);
  UASSERT (_res);
  return _res;
}


void*
cast_event_int (const ::libs::events::IEvent::ptr& _event, const ::libs::events::IEvent::text_id_type& _id)
{
  auto _impl = get_events_impl ();
  auto _res  = _impl->dcast (_event.get (), _id);
  return _res;
}


void*
cast_event_int (const ::libs::events::IEvent::cptr& _event, const ::libs::events::IEvent::text_id_type& _id)
{
  auto _impl = get_events_impl ();
  auto _res  = _impl->dcast (_event.get (), _id);
  return _res;
}


void*
cast_event_int (::libs::events::IEvent::raw_ptr _event, const ::libs::events::IEvent::text_id_type& _id)
{
  auto _impl = get_events_impl ();
  auto _res  = _impl->dcast (_event, _id);
  return _res;
}


void*
cast_event_int (::libs::events::IEvent::craw_ptr _event, const ::libs::events::IEvent::text_id_type& _id)
{
  auto _impl = get_events_impl ();
  auto _res  = _impl->dcast (_event, _id);
  return _res;
}

bool
event2xml (::libs::events::IEvent::ptr& _src, std::string& _xml)
{
  auto _impl = get_events_impl ();
  return _impl->event2xml (_src, _xml);
}


bool
xml2event (const std::string& _xml, ::libs::events::IEvent::ptr& _dst)
{
  auto _impl = get_events_impl ();
  return _impl->xml2event (_xml, _dst);
}


::libs::events::IEvent::ptr
clone_event (const ::libs::events::IEvent::craw_ptr _event, const ::libs::events::TypeCloneEvent& _type)
{
  UASSERT (_event);
  auto _impl = get_events_impl ();
  return _impl->clone (_event, _type);
}

}}}      // namespace libs::iproperties::helpers
