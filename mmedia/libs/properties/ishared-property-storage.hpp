#pragma once
/**
\file       ishared-property-storage.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_properties_libs
*/

namespace libs::properties
{
///  Интерфейс хранилища свойств, общих для всей системы
class ISharedPropertyStorage
{
  public:
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (ISharedPropertyStorage)

  ISharedPropertyStorage (const ISharedPropertyStorage&)            = delete;
  ISharedPropertyStorage& operator= (const ISharedPropertyStorage&) = delete;

  //  ISharedPropertyStorage interface
  virtual auto check (const consts::keys::key_property_type&) const -> bool                           = 0;
  virtual auto get (const consts::keys::key_property_type&) -> ISharedProperty::raw_ptr               = 0;
  virtual auto set_prop (const consts::keys::key_property_type&, const ISharedProperty::ptr&) -> void = 0;
  virtual auto reset_prop (const consts::keys::key_property_type&) -> void                            = 0;

  protected:
  ISharedPropertyStorage ()          = default;
  virtual ~ISharedPropertyStorage () = default;
};
}   // namespace libs::properties
