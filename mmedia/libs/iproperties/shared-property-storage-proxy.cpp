/**
\file       shared-property-storage-proxy.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-iproperties-includes_int.hpp"
#include "libs-iproperties-includes.hpp"
#include "shared-property-storage-proxy.hpp"

namespace libs::iproperties
{
SharedPropertyStorageProxy::SharedPropertyStorageProxy () :
  ::libs::helpers::proxy::MemProxyBase (::libs::properties::consts::id_proxy_shared_mem, sizeof (SharedPropertyStorage)),
  pobj_ (nullptr)
{
  // lock_type  lock(mtx_);
  pobj_ = pshm_->find_or_construct< SharedPropertyStorage::ptr > (cid_.c_str ()) ();
  U3_ASSERT (pobj_);

  if (!(*pobj_))
  {
    *pobj_.load () = std::make_shared< SharedPropertyStorage > ();
  }

  U3_ASSERT (pobj_);
}


SharedPropertyStorageProxy::raw_ptr
SharedPropertyStorageProxy::instance ()
{
  static SharedPropertyStorageProxy g_inst;
  return &g_inst;
}


syn::ISharedPropertyStorage::raw_ptr
SharedPropertyStorageProxy::impl ()
{
  // lock_type  lock(mtx_);
  U3_ASSERT (pobj_);
  U3_ASSERT (*pobj_);
  return pobj_.load ()->get ();
}
}   // namespace libs::iproperties
