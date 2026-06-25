/**
\file       shared-property-storage.cpp
\author     Erashov Anton erashov2026@proton.me
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


auto
SharedPropertyStorage::check (const syn::key_property_type& key) const -> bool
{
  lock_type lock (mtx_);
  auto      find = props_.find (key);
  return find == props_.end () ? false : true;
}


syn::ISharedProperty::raw_ptr
SharedPropertyStorage::get (const syn::key_property_type& key)
{
  lock_type lock (mtx_);
  auto      find = props_.find (key);

  if (find == props_.end ())
  {
    // Допустимо - может быть такое при инициализации системы
    U3_XLOG_WARN ("u3_helpers_lib::SharedPropertyStorage::get not found" + TOLOG (key));
    return nullptr;
  }
  return find->second.get ();
}


void
SharedPropertyStorage::set_prop (const syn::key_property_type& key, const syn::ISharedProperty::ptr& ptr)
{
  lock_type lock (mtx_);

  {
    auto checkit = props_.find (key);
    if (props_.end () != checkit)
    {
      // перезапись допустима только для пустого значения.
      if (checkit->second)
      {
        U3_CHECK_NT (!checkit->second, "skip, try change not empty property" + TOLOG (key) + PTR_TOLOG (checkit->second.get ()) + PTR_TOLOG (ptr.get ()));
        return;
      }
    }
  }

  U3_XLOG_DBG ("update prop" + TOLOG (key) + PTR_TOLOG (ptr.get ()));
  props_[key] = ptr;
}


void
SharedPropertyStorage::reset_prop (const syn::key_property_type& key)
{
  lock_type lock (mtx_);
  U3_XLOG_DBG ("reset prop" + TOLOG (key));
  props_[key] = syn::ISharedProperty::ptr ();
}
}   // namespace libs::iproperties
