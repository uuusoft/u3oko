/**
\file       link-creator-proxy.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_ilink
*/
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

  auto*                           ipropos = ::libs::iproperties::helpers::get_shared_prop_os ();
  syn::ISharedProperty::lock_type lock (ipropos->get_sync ());

  auto       mainappl = ipropos->get_appl_lockfree ();
  const auto implname = mainappl->get_messenger_impl ();
  const auto issingle = mainappl->is_single_process ();
  U3_XLOG_MARK ("init link proxy" + VTOLOG (issingle) + TOLOG (implname));

  if (issingle)
  {
    if ("fast" == implname)
    {
      *pimpl_ = std::make_shared< impl::oneproc::LinkCreatorImplOneProc > ();
      return;
    }
  }
  else
  {
    if ("anyproc" == implname)
    {
      *pimpl_ = std::make_shared< impl::anyproc::LinkCreatorImplAnyProc > ();
      return;
    }
    else if ("rabbitmq" == implname)
    {
      U3_ASSERT_SIGNAL ("not implementated" + VTOLOG (issingle) + TOLOG (implname));
      return;
    }
  }
  U3_ASSERT_SIGNAL ("unknown impl name for process" + VTOLOG (issingle) + TOLOG (implname));
}
}   // namespace libs::ilink
