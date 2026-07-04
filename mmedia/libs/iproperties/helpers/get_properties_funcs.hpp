#pragma once
/**
\file       get_properties_funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_iproperties_lib
\brief      Набор вспомогательных функций доступа к конкретным свойствам для упрощения кода
*/

namespace libs::iproperties::helpers
{
inline auto
get_storage () -> ::libs::properties::ISharedPropertyStorage::raw_ptr
{
  auto proxy = ::libs::iproperties::SharedPropertyStorageProxy::instance ();
  U3_ASSERT (proxy);
  auto impl = proxy->impl ();
  U3_ASSERT (impl);
  return impl;
}


inline auto
check_prop (const std::string& id) -> bool
{
  auto storage = get_storage ();
  if (id.empty () || !storage)
  {
    return false;
  }
  return storage->check (id.c_str ());
}


inline auto
get_prop (const std::string& id) -> ::libs::properties::ISharedProperty::raw_ptr
{
  auto storage = get_storage ();
  U3_ASSERT (!id.empty ());
  U3_ASSERT (storage);
  auto ret = storage->get (id.c_str ());
  U3_ASSERT (ret);
  return ret;
}


inline auto
get_shared_prop_os () -> vers::system::ISystemProperty::raw_ptr
{
  auto rprop = get_prop (::libs::properties::consts::keys::shared_os_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  U3_ASSERT (ret);
  return ::libs::utility::casts::reinterpret_cast_helper< vers::system::ISystemProperty::raw_ptr > (ret);
}


inline auto
get_spec_prop_os () -> void*
{
  ::libs::properties::ISharedProperty::raw_ptr rprop = get_prop (::libs::properties::consts::keys::specific_os_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  U3_ASSERT (ret);
  return ret;
}


inline auto
check_prop_links () -> bool
{
  if (!check_prop (::libs::properties::consts::keys::links_property))
  {
    return false;
  }
  ::libs::properties::ISharedProperty::raw_ptr rprop = get_prop (::libs::properties::consts::keys::links_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  return ret ? true : false;
}


inline auto
get_prop_links () -> ::libs::properties::vers::links::ILinksProperty::raw_ptr
{
  auto rprop = get_prop (::libs::properties::consts::keys::links_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  U3_ASSERT (ret);
  return ::libs::utility::casts::reinterpret_cast_helper< ::libs::properties::vers::links::ILinksProperty::raw_ptr > (ret);
}


inline auto
get_prop_demons () -> void*
{
  ::libs::properties::ISharedProperty::raw_ptr rprop = get_prop (::libs::properties::consts::keys::demons_property);
  U3_ASSERT (rprop);
  void* ret = rprop->cast2top ();
  U3_ASSERT (ret);
  return ret;
}


inline auto
cast_prop_demons () -> ::libs::iproperties::vers::demon::IDemonsProperty::raw_ptr
{
  auto  demon_prop = ::libs::iproperties::helpers::get_prop_demons ();
  auto* ret        = ::libs::utility::casts::reinterpret_cast_helper< ::libs::iproperties::vers::demon::IDemonsProperty::raw_ptr > (demon_prop);
  U3_ASSERT (demon_prop);
  U3_ASSERT (ret);
  return ret;
}
}   // namespace libs::iproperties::helpers
