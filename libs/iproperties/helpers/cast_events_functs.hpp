#pragma once
/**
\file       cast_events_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       04.08.2018
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      ����� ��������������� ������� ������� � ���������� ��������� ��� ��������� ����.
*/

namespace libs { namespace iproperties { namespace helpers {

::libs::events::IEvent::ptr
get_event_int (const ::libs::events::IEvent::hid_type& _id);

void*
cast_event_int (const ::libs::events::IEvent::ptr& _event, const ::libs::events::IEvent::hid_type& _id);

void*
cast_event_int (const ::libs::events::IEvent::cptr& _event, const ::libs::events::IEvent::hid_type& _id);

void*
cast_event_int (::libs::events::IEvent::raw_ptr _event, const ::libs::events::IEvent::hid_type& _id);

void*
cast_event_int (::libs::events::IEvent::craw_ptr _event, const ::libs::events::IEvent::hid_type& _id);

#ifndef UUU_FORCE_DCAST_EVENT_INT
#define UUU_FORCE_DCAST_EVENT_INT(ptr, type) reinterpret_cast<type> (ptr)
#endif
/**
\brief  
*/
template <typename T>
T*
get_and_cast_event (::libs::events::IEvent::ptr& _event)
{
  UASSERT (!_event);
  const auto _id = T::gen_get_mid ();
  _event         = get_event_int (_id);
  auto _ret      = UUU_FORCE_DCAST_EVENT_INT (cast_event_int (_event, _id), T*);
  return _ret;
}
/**
\brief  
*/
template <typename T>
T*
cast_event (const ::libs::events::IEvent::cptr& _event)
{
  UASSERT (_event);
  const auto _id  = T::gen_get_mid ();
  auto       _ret = UUU_FORCE_DCAST_EVENT_INT (cast_event_int (_event, _id), T*);
  return _ret;
}
/**
\brief  
*/
template <typename T>
T*
cast_event (::libs::events::IEvent::raw_ptr _event)
{
  UASSERT (_event);
  const auto _id  = T::gen_get_mid ();
  auto       _ret = UUU_FORCE_DCAST_EVENT_INT (cast_event_int (_event, _id), T*);
  return _ret;
}
/**
\brief  
*/
template <typename T>
const T*
cast_event (::libs::events::IEvent::craw_ptr _event)
{
  UASSERT (_event);
  const auto _id  = T::gen_get_mid ();
  auto       _ret = UUU_FORCE_DCAST_EVENT_INT (cast_event_int (_event, _id), const T*);
  return _ret;
}
/**
\brief  
*/
bool
event2xml (::libs::events::IEvent::ptr& _src, std::string& _xml);
/**
\brief  
*/
bool
xml2event (const std::string& _xml, ::libs::events::IEvent::ptr& _dst);
/**
\brief  
*/
::libs::events::IEvent::ptr
clone_event (const ::libs::events::IEvent::craw_ptr _event, const ::libs::events::DeepEventCloneType& _type = ::libs::events::DeepEventCloneType::full);

}}}      // namespace libs::iproperties::helpers
