#pragma once
/**
\file       get_properties_funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_iproperties_lib
\brief      Набор вспомогательных функций доступа к конкретным свойствам для упрощения кода
*/

#ifndef U3_CAST_PROP
#  define U3_CAST_PROP(type) reinterpret_cast< type >
#endif

namespace libs::iproperties::helpers
{
inline ::libs::properties::ISharedPropertyStorage::raw_ptr
get_storage ()
{
  SharedPropertyStorageProxy::raw_ptr proxy = ::libs::iproperties::SharedPropertyStorageProxy::instance ();
  U3_ASSERT (proxy);
  ::libs::properties::ISharedPropertyStorage::raw_ptr impl = proxy->impl ();
  U3_ASSERT (impl);
  return impl;
}


inline ::libs::properties::ISharedProperty::raw_ptr
get_prop (const std::string& id)
{
  ::libs::properties::ISharedPropertyStorage::raw_ptr storage = get_storage ();
  U3_ASSERT (!id.empty ());
  U3_ASSERT (storage);
  ::libs::properties::ISharedProperty::raw_ptr ret = storage->get (id.c_str ());
  U3_ASSERT (ret);
  return ret;
}


inline void*
get_shared_prop_os ()
{
  ::libs::properties::ISharedProperty::raw_ptr rprop = get_prop (::libs::properties::consts::keys::shared_os_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  U3_ASSERT (ret);
  return ret;
}


inline void*
get_spec_prop_os ()
{
  ::libs::properties::ISharedProperty::raw_ptr rprop = get_prop (::libs::properties::consts::keys::specific_os_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  U3_ASSERT (ret);
  return ret;
}


inline void*
get_prop_links ()
{
  ::libs::properties::ISharedProperty::raw_ptr rprop = get_prop (::libs::properties::consts::keys::links_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  U3_ASSERT (ret);
  return ret;
}


inline void*
get_prop_demons ()
{
  ::libs::properties::ISharedProperty::raw_ptr rprop = get_prop (::libs::properties::consts::keys::demons_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  U3_ASSERT (ret);
  return ret;
}


inline ::libs::iproperties::vers::demon::IDemonsProperty::raw_ptr
cast_prop_demons ()
{
  auto demon_prop = ::libs::iproperties::helpers::get_prop_demons ();
  auto ret        = U3_CAST_PROP (::libs::iproperties::vers::demon::IDemonsProperty::raw_ptr) (demon_prop);
  U3_ASSERT (demon_prop);
  U3_ASSERT (ret);
  return ret;
}
}   // namespace libs::iproperties::helpers
