/**
\file       ievents-proxy.cpp
\date       14.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/events/includes.hpp"
#include "ievents-proxy.hpp"

namespace libs::proxy
{
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_devents () -> ::libs::events::io::IEvents::raw_ptr;

auto
IEventsProxy::instance (const std::string& dll_path) -> IEventsProxy::raw_ptr
{
  static IEventsProxy g_inst (dll_path);
  return &g_inst;
}


auto
IEventsProxy::impl () -> ::libs::events::io::IEvents::raw_ptr
{
  U3_ASSERT (creator_);
  ::libs::events::io::IEvents::raw_ptr ret = creator_ ();
  U3_ASSERT (ret);
  return ret;
}


IEventsProxy::IEventsProxy (const std::string& dll_path)
{
#if (U3_BUILD_MODULES_AS_LIBS == 1)
  U3_MARK_UNUSED_HERE (lib_);
  creator_ = create_impl_vdd_devents;
#else
  boost::filesystem::path cpath (dll_path);
  cpath /= ::libs::utility::dlls::decorate_dll_name ("vdd_devents");
  lib_.load (cpath, boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);
  creator_ = ::boost::dll::import_symbol< create_func_type > (lib_, "create_impl_vdd_devents");
#endif
  U3_ASSERT (creator_);
}
}   // namespace libs::proxy
