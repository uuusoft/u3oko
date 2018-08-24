//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       link-creator-proxy.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "impl/includes.hpp"
#include "link-creator-proxy.hpp"

namespace libs { namespace ilink {

LinkCreatorProxy::LinkCreatorProxy () :
  ::libs::helpers::proxy::MemProxyBase (::libs::link::consts::text::id_shared_mem_base, sizeof (::libs::link::ILinkCreator::ptr)),
  pimpl_ (nullptr)
{
  pimpl_ = pshm_->find_or_construct<::libs::link::ILinkCreator::ptr> (cid_.c_str ()) ();

  if (*pimpl_)
    {
      return;
    }

  ISystemProperty::raw_ptr    _orinfo = UUU_PROP_CAST (::libs::iproperties::vers::system::ISystemProperty::raw_ptr) (::libs::iproperties::helpers::get_shared_prop_os ());
  ISharedProperty::guard_type _guard (_orinfo->get_sync ());
  auto                        _pmain_prop = _orinfo->get_main_appl_lockfree ();

  if (_pmain_prop->is_single_process ())
    {
      if ("fast" == _pmain_prop->get_messenger_impl ())
        {
          *pimpl_ = std::make_shared<impl::oneproc::LinkCreatorImplOneProc> ();
          return;
        }
    }

  *pimpl_ = std::make_shared<impl::anyproc::LinkCreatorImplAnyProc> ();
  return;
}


LinkCreatorProxy::~LinkCreatorProxy ()
{
  return;
}

}}      // namespace libs::ilink
