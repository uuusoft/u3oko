/**
\file       ioptim-proxy.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.04.2022
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
  ::libs::utility::checks::throw_ifn ((bool) creator_);
  ::libs::optim::io::IOptim::raw_ptr ret = creator_ ();
  ::libs::utility::checks::throw_ifn (ret);
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
  lib_.load (cpath, boost::dll::load_mode::rtld_now | boost::dll::load_mode::search_system_folders);
  creator_ = ::boost::dll::import_symbol< create_ioptim_func_type > (cpath, "create_impl_vdd_doptim");
#endif
  ::libs::utility::checks::throw_ifn ((bool) creator_);
}
}   // namespace libs::proxy
