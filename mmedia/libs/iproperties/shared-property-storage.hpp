#pragma once
/**
\file       shared-property-storage.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties
{
// Функция возвращает указатель на реализацию хранилища.
syn::ISharedPropertyStorage::raw_ptr instance ();

/// Реализация хранилища свойств, общих для всей системы
class SharedPropertyStorage : public ::libs::properties::ISharedPropertyStorage
{
  private:
  //  internal typess
  using storage_type = std::unordered_map< syn::key_property_type, syn::ISharedProperty::ptr >;
  using sync_type    = std::mutex;
  using lock_type    = std::scoped_lock< sync_type >;

  public:
  SharedPropertyStorage () = default;
  virtual ~SharedPropertyStorage ();

  //  ::libs::properties::ISharedPropertyStorage overrides
  virtual auto check (const syn::key_property_type&) const -> bool override;
  virtual auto get (const syn::key_property_type&) -> syn::ISharedProperty::raw_ptr override;
  virtual auto set_prop (const syn::key_property_type&, const syn::ISharedProperty::ptr&) -> void override;
  virtual auto reset_prop (const syn::key_property_type&) -> void override;

  private:
  mutable sync_type mtx_;     //< Для синхронизации доступа к хранилищу
  storage_type      props_;   //< Собственно множество свойств системы
};
}   // namespace libs::iproperties
