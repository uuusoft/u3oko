/**
\file       obj-source-impl-proxy.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.05.2017
\project    u3_gen_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/proxy/proxy/gen-vgen-proxy.hpp"
#include "gen-vgen-includes_int.hpp"
#include "obj-source-impl-proxy.hpp"

namespace dlls::sources::gen_vgen
{
ObjSourceImplProxy::~ObjSourceImplProxy ()
{
  clear ();
}


std::string
make_name_function_for_source_library (
  const std::string& lib_name,
  const std::string& prefix_funct)
{
  return prefix_funct + "_" + libs::helpers::dlls::undecorate_dll_name (lib_name);
}


void
ObjSourceImplProxy::init (const std::string& name_impl)
{
  clear ();
  U3_CHECK (!name_impl.empty (), "empty impl name for capture");

  const std::string path      = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  const std::string full_path = ::libs::helpers::files::make_path (path, ::libs::helpers::dlls::decorate_dll_name (name_impl));

  capture_lib_.load (full_path.c_str (), boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);

#if (U3_BUILD_MODULES_AS_LIBS == 1)
  func_get_  = ::libs::proxy::get_create_source_funct (name_impl);
  func_free_ = ::libs::proxy::get_free_source_funct (name_impl);
#else
#  ifdef U3_OS_ANDROID
  func_get_  = reinterpret_cast< gen_lib::get_source_func_type* > (dlsym (capture_lib_.native (), make_name_function_for_source_library (name_impl, gen_lib::consts::name_get_funct).c_str ()));
  func_free_ = reinterpret_cast< gen_lib::free_source_func_type* > (dlsym (capture_lib_.native (), make_name_function_for_source_library (name_impl, gen_lib::consts::name_free_funct).c_str ()));
#  else
  func_get_  = ::boost::dll::import_symbol< gen_lib::get_source_func_type > (capture_lib_, make_name_function_for_source_library (name_impl, gen_lib::consts::name_get_funct));
  func_free_ = ::boost::dll::import_symbol< gen_lib::free_source_func_type > (capture_lib_, make_name_function_for_source_library (name_impl, gen_lib::consts::name_free_funct));
#  endif
#endif

  U3_CHECK (func_get_ && func_free_, "get funct");
  U3_CHECK (func_get_ (&impl_), "create impl");
  U3_CHECK (impl_, "create empty impl");
  impl_->init ();
}


void
ObjSourceImplProxy::clear ()
{
  if (func_free_ && impl_)
  {
    impl_->stop ();
    func_free_ (&impl_);
  }

  func_get_  = 0;
  func_free_ = 0;
  impl_      = nullptr;
}


gen_lib::ISourceImpl::raw_ptr
ObjSourceImplProxy::get_source_impl ()
{
  return impl_;
}


::libs::helpers::dlls::dll_type
ObjSourceImplProxy::get_source_impl_lib ()
{
  return capture_lib_;
}
}   // namespace dlls::sources::gen_vgen
