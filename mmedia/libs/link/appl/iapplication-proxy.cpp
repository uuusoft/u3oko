/**
\file       iapplication-proxy.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../_make/libs-link-includes_int.hpp"
#include "mmedia/libs/proxy/proxy/link-proxy.hpp"
#include "iapplication-proxy.hpp"

namespace libs::link::appl
{
::libs::utility::dlls::FreezerDlls IApplicationProxy::frozen_dlls_;

auto
IApplicationProxy::impl () -> IApplication::raw_ptr
{
  U3_CALL_TRACE_DBG;
  if (!impl_)
  {
    ::libs::utility::checks::throw_ifn ((bool) creator_, "empty creator function");
    impl_ = creator_ ();
  }
  ::libs::utility::checks::throw_ifn ((bool) impl_, "failed create impl module");
  return impl_;
}


IApplicationProxy::IApplicationProxy (
  const std::string& dll_path,
  const std::string& name_lib)
{
  U3_CALL_TRACE_INFO_DBG (TOLOG (dll_path) + TOLOG (name_lib));
  ::libs::utility::checks::throw_ifn (!dll_path.empty ());
  ::libs::utility::checks::throw_ifn (!name_lib.empty ());

#ifdef U3_OS_ANDROID
  boost::filesystem::path cpath ("");
#else
  boost::filesystem::path cpath (dll_path);
#endif

  cpath /= ::libs::utility::dlls::decorate_dll_name (name_lib);

#if (U3_BUILD_MODULES_AS_LIBS == 1)
  U3_MARK_UNUSED_HERE (lib_);
  creator_ = ::libs::proxy::get_create_module_func (name_lib);
  erasor_  = ::libs::proxy::get_delete_module_func (name_lib);
#else
  std::error_code load_error;
  lib_.load (cpath, boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders, load_error);
  if (!lib_.is_loaded ())
  {
    U3_XLOG_ERROR ("failed load dll" + TOLOG (name_lib) + TOLOG (cpath.string ()));
    std::terminate ();
  }

  U3_XLOG_DBG ("IApplicationProxy::IApplicationProxy:: prepare frozen dll" + TOLOG (dll_path) + TOLOG (name_lib));
  frozen_dlls_.add (cpath.string (), lib_);

  creator_ = ::boost::dll::import_symbol< create_obj_type > (
    lib_, ::libs::utility::dlls::make_func_name_lib (name_lib, "create_impl").c_str ());

  erasor_ = ::boost::dll::import_symbol< delete_obj_type > (
    lib_, ::libs::utility::dlls::make_func_name_lib (name_lib, "delete_impl").c_str ());
#endif

  ::libs::utility::checks::throw_ifn (
    (bool) creator_,
    "find create_impl from lib, " + cpath.string () + ", " + ::libs::utility::dlls::make_func_name_lib (name_lib, "create_impl"));

  ::libs::utility::checks::throw_ifn (
    (bool) erasor_,
    "find delete_impl from lib, " + cpath.string () + ", " + ::libs::utility::dlls::make_func_name_lib (name_lib, "delete_impl"));
}

IApplicationProxy::~IApplicationProxy ()
{
  ::libs::utility::checks::assert_soft ((bool) erasor_, "empty deleter function");
  if (erasor_)
  {
    erasor_ (impl_);
  }
  impl_ = nullptr;
}
}   // namespace libs::link::appl
