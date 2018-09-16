#pragma once
/**
\file       shared-property-storage-proxy.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/

namespace libs { namespace iproperties {
//  syn namespace
namespace bip = boost::interprocess;
//  syn types
using ::libs::properties::ISharedProperty;
using ::libs::properties::ISharedPropertyStorage;
/**
\brief  Класс для доступа к общим свойствам системы в пределах одного процесса.
*/
class SharedPropertyStorageProxy : protected ::libs::helpers::proxy::MemProxyBase
{
  public:
  // ext types
  using create_funct_type = ISharedPropertyStorage::raw_ptr ();
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (SharedPropertyStorageProxy);

  static SharedPropertyStorageProxy::raw_ptr instance ();

  ISharedPropertyStorage::raw_ptr impl ();


  private:
  //  int types
  using sync_type  = std::mutex;
  using guard_type = std::lock_guard<sync_type>;

  SharedPropertyStorageProxy ();

  ~SharedPropertyStorageProxy ();

  SharedPropertyStorage::ptr* pobj_;      //< Реализация свойств, которая лежит в разделяемой памяти в пределах одного процесса.
};

}}      // namespace libs::iproperties
