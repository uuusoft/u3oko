#pragma once
/**
\file       shared-property-storage-proxy.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties
{
/// Класс для доступа к общим свойствам системы в пределах одного процесса
class SharedPropertyStorageProxy final : protected ::libs::helpers::proxy::MemProxyBase
{
  public:
  // ext types
  using create_func_type = syn::ISharedPropertyStorage::raw_ptr ();

  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (SharedPropertyStorageProxy)

  static SharedPropertyStorageProxy::raw_ptr instance ();

  syn::ISharedPropertyStorage::raw_ptr impl ();

  private:
  //  internal typess
  using sync_type = std::mutex;
  using lock_type = std::lock_guard< sync_type >;

  SharedPropertyStorageProxy ();
  ~SharedPropertyStorageProxy ();

  std::atomic< SharedPropertyStorage::ptr* > pobj_;   //< Реализация свойств, которая лежит в разделяемой памяти в пределах одного процесса
};
}   // namespace libs::iproperties
