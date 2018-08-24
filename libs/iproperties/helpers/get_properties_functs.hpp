#pragma once
/**
\file       get_properties_functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      Набор вспомогательных функций доступа к конкретным свойствам для упрощения кода.
*/

#ifndef UUU_PROP_CAST
#define UUU_PROP_CAST(type) reinterpret_cast<type>
#endif

namespace libs { namespace iproperties { namespace helpers {

inline ::libs::properties::ISharedPropertyStorage::raw_ptr
get_storage ()
{
  SharedPropertyStorageProxy::raw_ptr _proxy = ::libs::iproperties::SharedPropertyStorageProxy::instance ();
  UASSERT (_proxy);
  ::libs::properties::ISharedPropertyStorage::raw_ptr _impl = _proxy->impl ();
  UASSERT (_impl);
  return _impl;
}


inline ::libs::properties::ISharedProperty::raw_ptr
get_prop (const std::string& _id)
{
  UASSERT (!_id.empty ());
  ::libs::properties::ISharedPropertyStorage::raw_ptr _storage = get_storage ();
  ::libs::properties::ISharedProperty::raw_ptr        _ret     = _storage->get (_id);
  UASSERT (_storage);
  UASSERT (_ret);
  return _ret;
}


//inline vers::system::ISystemProperty::raw_ptr
inline void*
get_shared_prop_os ()
{
  ::libs::properties::ISharedProperty::raw_ptr _rprop = get_prop (::libs::properties::consts::keys::shared_os_property);
  //vers::system::ISystemProperty::raw_ptr       _ret   = d1ynamic_cast<vers::system::ISystemProperty::raw_ptr> (_rprop);
  void* _ret = _rprop->cast2top ();
  UASSERT (_rprop);
  UASSERT (_ret);
  return _ret;
}


inline void*
get_spec_prop_os ()
{
  ::libs::properties::ISharedProperty::raw_ptr _rprop = get_prop (::libs::properties::consts::keys::specific_os_property);
  //vers::system::ISystemProperty::raw_ptr       _ret   = d1ynamic_cast<vers::system::ISystemProperty::raw_ptr> (_rprop);
  void* _ret = _rprop->cast2top ();
  UASSERT (_rprop);
  UASSERT (_ret);
  return _ret;
}


//inline ::libs::properties::vers::links::ILinksProperty::raw_ptr
inline void*
get_prop_links ()
{
  ::libs::properties::ISharedProperty::raw_ptr _rprop = get_prop (::libs::properties::consts::keys::links_property);
  //::libs::properties::vers::links::ILinksProperty::raw_ptr _ret   = d1ynamic_cast<::libs::properties::vers::links::ILinksProperty::raw_ptr> (_rprop);
  void* _ret = _rprop->cast2top ();
  UASSERT (_rprop);
  UASSERT (_ret);
  return _ret;
}


inline void*
get_prop_demons ()
{
  ::libs::properties::ISharedProperty::raw_ptr _rprop = get_prop (::libs::properties::consts::keys::demons_property);
  //vers::demon::IDemonsProperty::raw_ptr        _ret   = d1ynamic_cast<vers::demon::IDemonsProperty::raw_ptr> (_rprop);
  void* _ret = _rprop->cast2top ();
  UASSERT (_rprop);
  UASSERT (_ret);
  return _ret;
}


inline ::libs::iproperties::vers::demon::IDemonsProperty::raw_ptr
cast_prop_demons ()
{
  return UUU_PROP_CAST (::libs::iproperties::vers::demon::IDemonsProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_demons ());
}

}}}      // namespace libs::iproperties::helpers
