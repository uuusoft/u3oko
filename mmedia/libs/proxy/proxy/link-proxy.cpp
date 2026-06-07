/**
\file       link-proxy.cpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "link-proxy.hpp"

#if (U3_MODULES_ENABLE_EVENTS == 1)
extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_u3_events ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_u3_events (::libs::link::appl::IApplication* appl);
#endif

#ifdef U3_GUI_ENABLE
extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_uuu_gui ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_uuu_gui (::libs::link::appl::IApplication* appl);
#endif

#if (U3_MODULES_ENABLE_HTTP == 1)
extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_uuu_http ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_uuu_http (::libs::link::appl::IApplication* appl);
#endif

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_uuu_log ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_uuu_log (::libs::link::appl::IApplication* appl);

#if (U3_MODULES_ENABLE_MDATA == 1)
extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_uuu_mdata ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_uuu_mdata (::libs::link::appl::IApplication* appl);
#endif

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_mpl_uuu_storage ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_mpl_uuu_storage (::libs::link::appl::IApplication* appl);

extern "C" BOOST_SYMBOL_EXPORT ::libs::link::appl::IApplication* create_impl_appl_u3oko ();
extern "C" BOOST_SYMBOL_EXPORT void                              delete_impl_appl_u3oko (::libs::link::appl::IApplication* appl);


namespace libs::proxy
{
::libs::link::appl::IApplicationProxy::create_func_type
get_create_module_funct (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);
#if (U3_MODULES_ENABLE_EVENTS == 1)
  if (lib_id == "mpl_u3_events")
  {
    return create_impl_mpl_u3_events;
  }
#endif
#ifdef U3_GUI_ENABLE
  if (lib_id == "mpl_uuu_gui")
  {
    return create_impl_mpl_uuu_gui;
  }
#endif
#if (U3_MODULES_ENABLE_HTTP == 1)
  if (lib_id == "mpl_uuu_http")
  {
    return create_impl_mpl_uuu_http;
  }
#endif
  if (lib_id == "mpl_uuu_log")
  {
    return create_impl_mpl_uuu_log;
  }
#if (U3_MODULES_ENABLE_MDATA == 1)
  if (lib_id == "mpl_uuu_mdata")
  {
    return create_impl_mpl_uuu_mdata;
  }
#endif
  if (lib_id == "mpl_uuu_storage")
  {
    return create_impl_mpl_uuu_storage;
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
  if (lib_id == "mpl_u3_events")
  {
    return delete_impl_mpl_u3_events;
  }
#endif
#ifdef U3_GUI_ENABLE
  if (lib_id == "mpl_uuu_gui")
  {
    return delete_impl_mpl_uuu_gui;
  }
#endif
#if (U3_MODULES_ENABLE_HTTP == 1)
  if (lib_id == "mpl_uuu_http")
  {
    return delete_impl_mpl_uuu_http;
  }
#endif
  if (lib_id == "mpl_uuu_log")
  {
    return delete_impl_mpl_uuu_log;
  }
#if (U3_MODULES_ENABLE_MDATA == 1)
  if (lib_id == "mpl_uuu_mdata")
  {
    return delete_impl_mpl_uuu_mdata;
  }
#endif
  if (lib_id == "mpl_uuu_storage")
  {
    return delete_impl_mpl_uuu_storage;
  }
  if (lib_id == "appl_u3oko")
  {
    return delete_impl_appl_u3oko;
  }

  U3_THROW_EXCEPTION ("find delete module funct" + TOLOG (lib_id));
}
}   // namespace libs::proxy
