#pragma once
/**
\file       shared-property-storage.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief    
*/

namespace libs { namespace iproperties {
//  syn types
using ::libs::properties::ISharedProperty;
using ::libs::properties::ISharedPropertyStorage;
using ::libs::properties::consts::keys::key_property_type;
/**
  \brief  Функция возвращает указатель на реализацию хранилища.
  */
ISharedPropertyStorage::raw_ptr instance ();
/**
  \brief  Реализация хранилища свойств, общих для всей системы.
  */
class SharedPropertyStorage : public ISharedPropertyStorage
{
  private:
  //  int types
  using storage_type = std::map<key_property_type, ISharedProperty::ptr>;
  using sync_type    = std::mutex;
  using guard_type   = std::lock_guard<sync_type>;


  public:
  SharedPropertyStorage ();

  virtual ~SharedPropertyStorage ();

  virtual ISharedProperty::raw_ptr get (const key_property_type& _key) override;
  virtual void                     set_prop (const key_property_type& _key, const ISharedProperty::ptr& _ptr) override;
  virtual void                     reset_prop (const key_property_type& _key) override;


  private:
  sync_type    mtx_;        //< Для синхронизации доступа к хранилищу.
  storage_type props_;      //< Собственно множество свойств системы.
};

}}      // namespace libs::iproperties
