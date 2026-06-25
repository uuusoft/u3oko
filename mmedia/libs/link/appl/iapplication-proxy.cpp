/**
\file       iapplication-proxy.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_link
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../libs-link-includes_int.hpp"
#include "mmedia/libs/proxy/proxy/link-proxy.hpp"
#include "iapplication-proxy.hpp"

namespace libs::link::appl
{
::libs::helpers::dlls::FreezerDlls IApplicationProxy::frozen_dlls_;

IApplication::raw_ptr
IApplicationProxy::impl ()
{
  U3_XLOG_DBG ("IApplicationProxy::implIApplicationProxy::impl::---->");
  if (!impl_)
  {
    U3_CHECK (creator_, "empty creator function");
    impl_ = creator_ ();
  }
  U3_CHECK (impl_, "failed create impl module");
  U3_XLOG_DBG ("IApplicationProxy::implIApplicationProxy::impl::<----");
  return impl_;
}


std::string
make_name_function_for_library (const std::string& lib_name, const std::string& prefix_funct)
{
  return prefix_funct + "_" + libs::helpers::dlls::undecorate_dll_name (lib_name);
}


IApplicationProxy::IApplicationProxy (
  const std::string& dll_path,
  const std::string& name_lib)
{
  U3_XLOG_DBG ("IApplicationProxy::IApplicationProxy::---->" + TOLOG (dll_path) + TOLOG (name_lib));
  U3_ASSERT (!dll_path.empty ());
  U3_ASSERT (!name_lib.empty ());

#ifdef U3_OS_ANDROID
  boost::filesystem::path cpath ("");
#else
  boost::filesystem::path cpath (dll_path);
#endif

  cpath /= ::libs::helpers::dlls::decorate_dll_name (name_lib);

#if (U3_BUILD_MODULES_AS_LIBS == 1)
  U3_MARK_UNUSED_HERE (lib_);
  creator_ = ::libs::proxy::get_create_module_funct (name_lib);
  erasor_  = ::libs::proxy::get_delete_module_funct (name_lib);
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

#  ifdef U3_OS_ANDROID
  creator_ = ::libs::helpers::casts::reinterpret_cast_helper< create_obj_type* > (dlsym (lib_.native (), make_name_function_for_library (name_lib, "create_impl").c_str ()));
  erasor_  = ::libs::helpers::casts::reinterpret_cast_helper< delete_obj_type* > (dlsym (lib_.native (), make_name_function_for_library (name_lib, "delete_impl").c_str ()));
#  else
  creator_ = ::boost::dll::import_symbol< create_obj_type > (lib_, make_name_function_for_library (name_lib, "create_impl").c_str ());
  erasor_  = ::boost::dll::import_symbol< delete_obj_type > (lib_, make_name_function_for_library (name_lib, "delete_impl").c_str ());
#  endif
#endif

  U3_CHECK (creator_, ("find create_impl from lib, " + cpath.string () + ", " + make_name_function_for_library (name_lib, "create_impl")).c_str ());
  U3_CHECK (erasor_, ("find delete_impl from lib, " + cpath.string () + ", " + make_name_function_for_library (name_lib, "delete_impl")).c_str ());
  U3_XLOG_DBG ("IApplicationProxy::IApplicationProxy::<----" + TOLOG (dll_path) + TOLOG (name_lib));
}

IApplicationProxy::~IApplicationProxy ()
{
  U3_ASSERT_NT (erasor_, "empty deleter function");
  if (erasor_)
  {
    erasor_ (impl_);
  }
  impl_ = nullptr;
}
}   // namespace libs::link::appl
