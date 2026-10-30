/**
\file       shared-property-storage-proxy.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
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
  ::libs::utility::checks::throw_ifn (pimpl_);
  if (!(*pimpl_))
  {
    *pimpl_.load () = std::make_shared< SharedPropertyStorage > ();
  }

  ::libs::utility::checks::throw_ifn (pimpl_);
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
  ::libs::utility::checks::throw_ifn (pimpl_);
  ::libs::utility::checks::throw_ifn ((bool) *pimpl_);
  return pimpl_.load ()->get ();
}


SharedPropertyStorageProxy::~SharedPropertyStorageProxy ()
{
  U3_CALL_TRACE_DBG;
  if (pimpl_)
  {
    ::libs::utility::checks::assert_soft ((bool) pshm_, "empty shared memory object for SharedPropertyStorageProxy");
    if (pshm_)
    {
      pshm_->destroy< SharedPropertyStorage::ptr > (obj_id_.c_str ());
    }
    pimpl_ = nullptr;
  }
}
}   // namespace libs::iproperties
