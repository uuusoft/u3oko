/**
\file       shared-property-storage.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-iproperties-includes_int.hpp"
#include "shared-property-storage.hpp"

namespace libs::iproperties
{
SharedPropertyStorage::~SharedPropertyStorage ()
{
  lock_type lock (mtx_);
  props_.clear ();
}


syn::ISharedProperty::raw_ptr
SharedPropertyStorage::get (const syn::key_property_type& key)
{
  // U3_ASSERT (!key.empty ());
  lock_type lock (mtx_);
  auto      find = props_.find (key);

  if (find == props_.end ())
  {
    U3_XLOG_ERROR ("u3_helpers_lib::SharedPropertyStorage::get not found" + TOLOG (key));
    // U3_ASSERT_SIGNAL ("failed"); Допустимо - может быть такое при инициализации системы
    return nullptr;
  }
  return find->second.get ();
}


void
SharedPropertyStorage::set_prop (const syn::key_property_type& key, const syn::ISharedProperty::ptr& ptr)
{
  // U3_ASSERT (!key.empty ());
  lock_type lock (mtx_);
  {
    auto it2old = props_.find (key);
    if (props_.end () != it2old)
    {
      //  перезапись допустима только для пустого значения.
      if (it2old->second)
      {
        U3_ASSERT_SIGNAL ("failed");
        return;
      }
    }
  }

  props_[key] = ptr;
}


void
SharedPropertyStorage::reset_prop (const syn::key_property_type& key)
{
  // U3_ASSERT (!key.empty ());
  lock_type lock (mtx_);
  props_[key] = syn::ISharedProperty::ptr ();
}
}   // namespace libs::iproperties
