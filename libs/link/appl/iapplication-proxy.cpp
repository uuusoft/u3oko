//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       IApplicationProxy.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "iapplication-proxy.hpp"

namespace libs { namespace link { namespace appl {

::libs::helpers::dlls::ForeverLoadDlls IApplicationProxy::freez_libs_;

IApplication::raw_ptr
IApplicationProxy::impl ()
{
  if (!impl_)
    {
      UASSERT (creator_);
      impl_ = creator_ ();
    }

  UASSERT (impl_);
  return impl_;
}


IApplicationProxy::IApplicationProxy (
  const char* _dll_path,
  const char* _name_lib) :
  impl_ (nullptr)
{
  UASSERT (_dll_path);
  UASSERT (_name_lib);

  boost::filesystem::path _cpath (_dll_path);

#if defined(UUU_OS_ANDROID)
  _cpath /= "lib";      //debug
#endif

  _cpath /= ::utils::mem_functs::files::decorate_dll_name (_name_lib);

  lib_.load (_cpath, boost::dll::load_mode::rtld_now);

  XULOG_TRACE ("IApplicationProxy::IApplicationProxy, " << _cpath.string () << ", " << lib_.native ());
  freez_libs_.add (_cpath.string (), lib_);

  creator_ = boost::dll::import_alias<create_obj_type> (lib_, "instance_iapplication");
  deletor_ = boost::dll::import_alias<delete_obj_type> (lib_, "delete_iapplication");

  CHECK_STATE (creator_, ("failed find instance_iapplication from lib, " + _cpath.string ()).c_str ());
  CHECK_STATE (deletor_, ("failed find delete_iapplication from lib, " + _cpath.string ()).c_str ());
}


IApplicationProxy::~IApplicationProxy ()
{
  UASSERT (deletor_);
  deletor_ (impl_);
  impl_ = nullptr;
}

}}}      // namespace libs::link::appl
