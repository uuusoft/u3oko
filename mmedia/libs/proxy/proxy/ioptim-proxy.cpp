/**
\file       ioptim-proxy.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.04.2022
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/optim/io/libs-optims-optim-io-includes.hpp"
#include "ioptim-proxy.hpp"

namespace libs::proxy
{
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_doptim () -> ::libs::optim::io::IOptim::raw_ptr;

auto
IOptimProxy::instance (const std::string& dll_path) -> IOptimProxy::raw_ptr
{
  static IOptimProxy g_inst (dll_path);
  return &g_inst;
}


auto
IOptimProxy::impl () -> ::libs::optim::io::IOptim::raw_ptr
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
  cpath /= ::libs::utility::dlls::decorate_dll_name ("vdd_doptim");

  try
  {
    lib_.load (cpath, boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);
  }
  catch (U3_MARK_UNUSED boost::exception& excpt)
  {
    U3_XLOG_ERROR ("load lib " + std::string (boost::diagnostic_information_what (excpt, true)));
  }

#  if defined(U3_OS_ANDROID)
  creator_ = ::libs::utility::casts::reinterpret_cast_helper< create_ioptim_func_type* > (dlsym (lib_.native (), "create_impl_vdd_doptim"));
#  else
  creator_ = ::boost::dll::import_symbol< create_ioptim_func_type > (cpath, "create_impl_vdd_doptim");
#  endif
#endif
  U3_ASSERT (creator_);
}
}   // namespace libs::proxy
