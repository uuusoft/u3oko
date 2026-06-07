#pragma once
/**
\file       ishared-property-storage.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  virtual ISharedProperty::raw_ptr get (const consts::keys::key_property_type&)                                   = 0;
  virtual void                     set_prop (const consts::keys::key_property_type&, const ISharedProperty::ptr&) = 0;
  virtual void                     reset_prop (const consts::keys::key_property_type&)                            = 0;

  protected:
  ISharedPropertyStorage ()          = default;
  virtual ~ISharedPropertyStorage () = default;
};
}   // namespace libs::properties
