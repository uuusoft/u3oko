/**
\file       link-proxy.cpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "link-proxy.hpp"

#if (U3_MODULES_ENABLE_EVENTS == 1)
extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_mevents ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_mevents (::libs::link::appl::IApplication* appl);
#endif

#if (U3_MODULES_ENABLE_GUI == 1)
extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_mgui ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_mgui (::libs::link::appl::IApplication* appl);
#endif

#if (U3_MODULES_ENABLE_HTTP == 1)
extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_mhttp ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_mhttp (::libs::link::appl::IApplication* appl);
#endif

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_mlog ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_mlog (::libs::link::appl::IApplication* appl);

#if (U3_MODULES_ENABLE_MDATA == 1)
extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_mdata ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_mdata (::libs::link::appl::IApplication* appl);
#endif

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_mstorage ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_mstorage (::libs::link::appl::IApplication* appl);

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_appl_u3oko ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_appl_u3oko (::libs::link::appl::IApplication* appl);


namespace libs::proxy
{
::libs::link::appl::IApplicationProxy::create_func_type
get_create_module_funct (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);
#if (U3_MODULES_ENABLE_EVENTS == 1)
  if (lib_id == "mpl_mevents")
  {
    return create_impl_mpl_mevents;
  }
#endif
#if (U3_MODULES_ENABLE_GUI == 1)
  if (lib_id == "mpl_mgui")
  {
    return create_impl_mpl_mgui;
  }
#endif
#if (U3_MODULES_ENABLE_HTTP == 1)
  if (lib_id == "mpl_mhttp")
  {
    return create_impl_mpl_mhttp;
  }
#endif
  if (lib_id == "mpl_mlog")
  {
    return create_impl_mpl_mlog;
  }
#if (U3_MODULES_ENABLE_MDATA == 1)
  if (lib_id == "mpl_mdata")
  {
    return create_impl_mpl_mdata;
  }
#endif
  if (lib_id == "mpl_mstorage")
  {
    return create_impl_mpl_mstorage;
  }
  if (lib_id == "appl_u3oko")
  {
    return create_impl_appl_u3oko;
  }

  U3_THROW_EXCEPTION ("find create module funct" + TOLOG (lib_id));
}


::libs::link::appl::IApplicationProxy::delete_func_type
get_delete_module_funct (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);
#if (U3_MODULES_ENABLE_EVENTS == 1)
  if (lib_id == "mpl_mevents")
  {
    return delete_impl_mpl_mevents;
  }
#endif
#if (U3_MODULES_ENABLE_GUI == 1)
  if (lib_id == "mpl_mgui")
  {
    return delete_impl_mpl_mgui;
  }
#endif
#if (U3_MODULES_ENABLE_HTTP == 1)
  if (lib_id == "mpl_mhttp")
  {
    return delete_impl_mpl_mhttp;
  }
#endif
  if (lib_id == "mpl_mlog")
  {
    return delete_impl_mpl_mlog;
  }
#if (U3_MODULES_ENABLE_MDATA == 1)
  if (lib_id == "mpl_mdata")
  {
    return delete_impl_mpl_mdata;
  }
#endif
  if (lib_id == "mpl_mstorage")
  {
    return delete_impl_mpl_mstorage;
  }
  if (lib_id == "appl_u3oko")
  {
    return delete_impl_appl_u3oko;
  }

  U3_THROW_EXCEPTION ("find delete module funct" + TOLOG (lib_id));
}
}   // namespace libs::proxy
