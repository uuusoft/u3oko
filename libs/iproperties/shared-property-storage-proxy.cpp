//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**   
\file       shared-property-storage-proxy.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "includes.hpp"
#include "shared-property-storage-proxy.hpp"

namespace libs { namespace iproperties {

SharedPropertyStorageProxy::SharedPropertyStorageProxy () :
  ::libs::helpers::proxy::MemProxyBase (::libs::properties::consts::id_storage_proxy_shared_mem, sizeof (SharedPropertyStorage)),
  pobj_ (nullptr)
{
  //guard_type  _grd(mtx_);
  pobj_ = pshm_->find_or_construct<SharedPropertyStorage::ptr> (cid_.c_str ()) ();
  UASSERT (pobj_);

  if (!(*pobj_))
    {
      *pobj_ = std::make_shared<SharedPropertyStorage> ();
    }

  UASSERT (pobj_);
  return;
}


SharedPropertyStorageProxy::~SharedPropertyStorageProxy ()
{
  //guard_type  _grd(mtx_);
}


SharedPropertyStorageProxy::raw_ptr
SharedPropertyStorageProxy::instance ()
{
  static SharedPropertyStorageProxy g_inst;
  return &g_inst;
}


ISharedPropertyStorage::raw_ptr
SharedPropertyStorageProxy::impl ()
{
  //guard_type  _grd(mtx_);
  UASSERT (pobj_);
  UASSERT (*pobj_);
  return pobj_->get ();
}

}}      // namespace libs::iproperties
