/**
\file       ioptim-proxy.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.04.2022
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim/io/libs-optims-optim-io-includes.hpp"
#include "ioptim-proxy.hpp"

namespace libs::proxy
{
extern "C" BOOST_SYMBOL_EXPORT ::libs::optim::io::IOptim::raw_ptr create_impl_vdd_doptim ();

IOptimProxy::raw_ptr
IOptimProxy::instance (const std::string& dll_path)
{
  static IOptimProxy g_inst (dll_path);
  return &g_inst;
}


::libs::optim::io::IOptim::raw_ptr
IOptimProxy::impl ()
{
  U3_ASSERT (creator_);
  ::libs::optim::io::IOptim::raw_ptr ret = creator_ ();
  U3_ASSERT (ret);
  return ret;
}


IOptimProxy::IOptimProxy (const std::string& dll_path)
{
#if (U3_BUILD_MODULES_AS_LIBS == 1)
  U3_MARK_UNUSED_HERE (lib_);
  creator_ = create_impl_vdd_doptim;
#else
  boost::filesystem::path cpath (dll_path);
  cpath /= ::libs::helpers::dlls::decorate_dll_name ("vdd_doptim");

  try
  {
    lib_.load (cpath, boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);
  }
  catch (U3_MARK_UNUSED boost::exception& e)
  {
    U3_XLOG_ERROR ("load lib " + std::string (boost::diagnostic_information_what (e, true)));
  }

#  if defined(U3_OS_ANDROID)
  creator_ = reinterpret_cast< create_ioptim_func_type* > (dlsym (lib_.native (), "create_impl_vdd_doptim"));
#  else
  creator_ = ::boost::dll::import_symbol< create_ioptim_func_type > (cpath, "create_impl_vdd_doptim");
#  endif
#endif
  U3_ASSERT (creator_);
}
}   // namespace libs::proxy
