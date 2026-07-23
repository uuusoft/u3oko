/**
\file       obj-source-impl-proxy.cpp
\author     Erashov Anton erashov2026@proton.me
\date       20.05.2017
\project    u3_gen_vgen
*/
#include "gen-vgen-includes_int.hpp"
#include "mmedia/libs/proxy/proxy/gen-vgen-proxy.hpp"
#include "obj-source-impl-proxy.hpp"

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
  const std::string full_path = ::libs::utility::files::make_path (path, ::libs::utility::dlls::decorate_dll_name (impl_name));

  impl_dll_.load (full_path.c_str (), boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);

#if (U3_BUILD_MODULES_AS_LIBS == 1)
  func_get_  = ::libs::proxy::get_create_source_func (impl_name);
  func_free_ = ::libs::proxy::get_free_source_func (impl_name);
#else
  func_get_ = ::boost::dll::import_symbol< gen_lib::get_source_func_type > (
    impl_dll_, ::libs::utility::dlls::make_func_name_lib (impl_name, gen_lib::consts::name_get_funct));

  func_free_ = ::boost::dll::import_symbol< gen_lib::free_source_func_type > (
    impl_dll_, ::libs::utility::dlls::make_func_name_lib (impl_name, gen_lib::consts::name_free_funct));
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

  func_get_  = nullptr;
  func_free_ = nullptr;
  impl_      = nullptr;
}


auto
ObjSourceImplProxy::get_source_impl () -> gen_lib::ISourceImpl::raw_ptr
{
  // U3_CHECK_NT (impl_, "return empty source impl" + TOLOG (impl_dll_.location ().string ()));
  return impl_;
}


auto
ObjSourceImplProxy::get_source_impl_lib () -> ::libs::utility::dlls::dll_type
{
  return impl_dll_;
}
}   // namespace dlls::sources::gen_vgen
