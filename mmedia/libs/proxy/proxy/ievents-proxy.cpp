/**
\file       ievents-proxy.cpp
\date       14.04.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/events/includes.hpp"
#include "ievents-proxy.hpp"

namespace libs::proxy
{
extern "C" BOOST_SYMBOL_EXPORT ::libs::events::io::IEvents::raw_ptr create_impl_vdd_devents ();

IEventsProxy::raw_ptr
IEventsProxy::instance (const std::string& dll_path)
{
  static IEventsProxy g_inst (dll_path);
  return &g_inst;
}


::libs::events::io::IEvents::raw_ptr
IEventsProxy::impl ()
{
  U3_ASSERT (creator_);
  ::libs::events::io::IEvents::raw_ptr ret = creator_ ();
  U3_ASSERT (ret);
  return ret;
}


IEventsProxy::IEventsProxy (const std::string& dll_path)
{
#ifdef U3_BUILD_MODULES_AS_LIBS
  U3_MARK_UNUSED_HERE (lib_);
  creator_ = create_impl_vdd_devents;
#else
  boost::filesystem::path cpath (dll_path);
  cpath /= ::libs::helpers::dlls::decorate_dll_name ("vdd_devents");

  try
  {
    lib_.load (cpath, boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);
  }
  catch (boost::exception& e)
  {
    U3_XLOG_ERROR ("load lib " + std::string (boost::diagnostic_information_what (e, true)));
  }

#  if defined(U3_OS_ANDROID)
  creator_ = reinterpret_cast< create_func_type* > (dlsym (lib_.native (), "create_impl_vdd_devents"));
#  else
  creator_ = ::boost::dll::import_symbol< create_func_type > (lib_, "create_impl_vdd_devents");
#  endif
#endif
  U3_ASSERT (creator_);
}


IEventsProxy::~IEventsProxy ()
{
}
}   // namespace libs::proxy
