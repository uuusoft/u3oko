/**
\file       link-creator-proxy.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_ilink
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "libs-ilink-includes_int.hpp"
#include "impl/libs-ilink-impl-includes.hpp"
#include "link-creator-proxy.hpp"

namespace libs::ilink
{
LinkCreatorProxy::LinkCreatorProxy () :
  ::libs::helpers::proxy::MemProxyBase (::libs::link::consts::text::id_shared_mem_base, sizeof (::libs::link::ILinkCreator::ptr)),
  pimpl_ (nullptr)
{
  pimpl_ = pshm_->find_or_construct< ::libs::link::ILinkCreator::ptr > (cid_.c_str ()) ();
  if (*pimpl_)
  {
    return;
  }

  auto                            ipropos = U3_CAST_PROP (syn::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ());
  syn::ISharedProperty::lock_type lock (ipropos->get_sync ());
  auto                            mainappl = ipropos->get_appl_lockfree ();

  if (mainappl->is_single_process ())
  {
    if ("fast" == mainappl->get_messenger_impl ())
    {
      *pimpl_ = std::make_shared< impl::oneproc::LinkCreatorImplOneProc > ();
      return;
    }
  }

  *pimpl_ = std::make_shared< impl::anyproc::LinkCreatorImplAnyProc > ();
}


LinkCreatorProxy::~LinkCreatorProxy ()
{
}
}   // namespace libs::ilink
