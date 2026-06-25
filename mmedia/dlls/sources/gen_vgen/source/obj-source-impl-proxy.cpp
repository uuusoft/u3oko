/**
\file       obj-source-impl-proxy.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_gen_vgen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/proxy/proxy/gen-vgen-proxy.hpp"
#include "gen-vgen-includes_int.hpp"
#include "obj-source-impl-proxy.hpp"

namespace dlls::sources::gen_vgen::internal
{
std::string
make_name_function_for_source_library (
  const std::string& lib_name,
  const std::string& prefix_funct)
{
  return prefix_funct + "_" + libs::helpers::dlls::undecorate_dll_name (lib_name);
}
}   // namespace dlls::sources::gen_vgen::internal

namespace dlls::sources::gen_vgen
{
ObjSourceImplProxy::ObjSourceImplProxy (const std::string& impl_name)
{
  if (!impl_name.empty ())
  {
    init (impl_name);
  }
}


ObjSourceImplProxy::~ObjSourceImplProxy ()
{
  clear ();
}


void
ObjSourceImplProxy::init (const std::string& impl_name)
{
  clear ();
  U3_CHECK (!impl_name.empty (), "empty impl name for capture");
  const std::string path      = ::libs::iproperties::appl_paths::get_current_lib_folder ();
  const std::string full_path = ::libs::helpers::files::make_path (path, ::libs::helpers::dlls::decorate_dll_name (impl_name));

  impl_dll_.load (full_path.c_str (), boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);

#if (U3_BUILD_MODULES_AS_LIBS == 1)
  func_get_  = ::libs::proxy::get_create_source_funct (impl_name);
  func_free_ = ::libs::proxy::get_free_source_funct (impl_name);
#else
#  ifdef U3_OS_ANDROID
  func_get_ = ::libs::helpers::casts::reinterpret_cast_helper< gen_lib::get_source_func_type* > (
    dlsym (impl_dll_.native (), internal::make_name_function_for_source_library (impl_name, gen_lib::consts::name_get_funct).c_str ()));

  func_free_ = ::libs::helpers::casts::reinterpret_cast_helper< gen_lib::free_source_func_type* > (
    dlsym (impl_dll_.native (), internal::make_name_function_for_source_library (impl_name, gen_lib::consts::name_free_funct).c_str ()));
#  else
  func_get_  = ::boost::dll::import_symbol< gen_lib::get_source_func_type > (impl_dll_, internal::make_name_function_for_source_library (impl_name, gen_lib::consts::name_get_funct));
  func_free_ = ::boost::dll::import_symbol< gen_lib::free_source_func_type > (impl_dll_, internal::make_name_function_for_source_library (impl_name, gen_lib::consts::name_free_funct));
#  endif
#endif

  U3_CHECK (func_get_ && func_free_, "get funct");
  U3_CHECK (func_get_ (&impl_), "create impl");
  U3_CHECK (impl_, "create func return empty impl");
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
  // U3_CHECK_NT (impl_, "return empty source impl" + TOLOG (impl_dll_.location ().string ()));
  return impl_;
}


::libs::helpers::dlls::dll_type
ObjSourceImplProxy::get_source_impl_lib ()
{
  return impl_dll_;
}
}   // namespace dlls::sources::gen_vgen
