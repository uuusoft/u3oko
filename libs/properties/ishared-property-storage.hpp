#pragma once
/**
\file       ishared-property-storage.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_properties
\brief      empty brief
*/

namespace libs { namespace properties {
/**
\brief  Интерфейс хранилища свойств, общих для всей системы.
*/
class ISharedPropertyStorage
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (ISharedPropertyStorage);

  ISharedPropertyStorage (const ISharedPropertyStorage& _src) = delete;
  ISharedPropertyStorage& operator= (const ISharedPropertyStorage& _src) = delete;
  //  ISharedPropertyStorage interface
  virtual ISharedProperty::raw_ptr get (const consts::keys::key_property_type& _key)                                        = 0;
  virtual void                     set_prop (const consts::keys::key_property_type& _key, const ISharedProperty::ptr& _ptr) = 0;
  virtual void                     reset_prop (const consts::keys::key_property_type& _key)                                 = 0;


  protected:
  ISharedPropertyStorage ()
  {}

  virtual ~ISharedPropertyStorage ()
  {}
};

}}      // namespace libs::properties
