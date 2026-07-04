/**
\file       shared-property-storage-proxy.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_iproperties_lib
*/
#include "libs-iproperties-includes_int.hpp"
#include "libs-iproperties-includes.hpp"
#include "shared-property-storage-proxy.hpp"

namespace libs::iproperties
{
SharedPropertyStorageProxy::SharedPropertyStorageProxy () :
  ::libs::utility::proxy::MemProxyBase (::libs::properties::consts::id_proxy_shared_mem, sizeof (SharedPropertyStorage)),
  pimpl_ (nullptr)
{
  // lock_type  lock(mtx_);
  pimpl_ = pshm_->find_or_construct< SharedPropertyStorage::ptr > (obj_id_.c_str ()) ();
  U3_ASSERT (pimpl_);
  if (!(*pimpl_))
  {
    *pimpl_.load () = std::make_shared< SharedPropertyStorage > ();
  }

  U3_ASSERT (pimpl_);
}


auto
SharedPropertyStorageProxy::instance () -> SharedPropertyStorageProxy::raw_ptr
{
  static SharedPropertyStorageProxy g_inst;
  return &g_inst;
}


auto
SharedPropertyStorageProxy::impl () -> syn::ISharedPropertyStorage::raw_ptr
{
  // lock_type  lock(mtx_);
  U3_ASSERT (pimpl_);
  U3_ASSERT (*pimpl_);
  return pimpl_.load ()->get ();
}


SharedPropertyStorageProxy::~SharedPropertyStorageProxy ()
{
  U3_XLOG_DEV ("SharedPropertyStorageProxy::~SharedPropertyStorageProxy::---->");
  if (pimpl_)
  {
    U3_ASSERT_NT (pshm_, "empty shared memory object for SharedPropertyStorageProxy");
    if (pshm_)
    {
      pshm_->destroy< SharedPropertyStorage::ptr > (obj_id_.c_str ());
    }
    pimpl_ = nullptr;
  }
  U3_XLOG_DEV ("SharedPropertyStorageProxy::~SharedPropertyStorageProxy::<----");
}
}   // namespace libs::iproperties
