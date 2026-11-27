/**
\file       link-proxy.cpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/ilink/consts/libs-ilink-const-vals.hpp"
#include "link-proxy.hpp"

#include "mmedia/modules/mappl/-module-appl-includes.hpp"
#include "mmedia/appls/u3oko/-appls-u3oko-includes.hpp"

// #include "mmedia/modules/mlog/-module-log-includes.hpp"

#if (U3_MODULES_ENABLE_MDATA == 1)
#  include "mmedia/modules/mdata/-module-mdata-includes.hpp"
#endif

#if (U3_MODULES_ENABLE_USERS == 1)
#  include "mmedia/modules/musers/-module-users-includes.hpp"
#endif

#if (U3_MODULES_ENABLE_HTTP == 1)
#  include "mmedia/modules/mhttp/appl/-http-module-includes.hpp"
#endif

// #include "mmedia/modules/mnet/-module-net-includes.hpp"

#if (U3_MODULES_ENABLE_GUI == 1)
#  include "mmedia/modules/mgui/-module-gui-includes.hpp"
#endif

#if (U3_MODULES_ENABLE_STORAGE == 1)
#  include "mmedia/modules/mstorage/-module-storage-includes.hpp"
#endif

#if (U3_MODULES_ENABLE_EVENTS == 1)
#  include "mmedia/modules/mevents/-module-events-includes.hpp"
#endif

// EAI-REFACT
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_mpl_mlog () -> ::libs::link::appl::IApplication*;
extern "C" BOOST_SYMBOL_EXPORT void delete_impl_mpl_mlog (::libs::link::appl::IApplication* appl);

namespace libs::proxy
{
auto
get_create_module_func (const std::string& plib_id) -> syn::IApplicationProxy::create_func_type
{
  const auto lib_id = libs::utility::dlls::undecorate_dll_name (plib_id);
#if (U3_MODULES_ENABLE_EVENTS == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mevents)
  {
    return create_impl_mpl_mevents;
  }
#endif
#if (U3_MODULES_ENABLE_GUI == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mgui)
  {
    return create_impl_mpl_mgui;
  }
#endif
#if (U3_MODULES_ENABLE_HTTP == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mhttp)
  {
    return create_impl_mpl_mhttp;
  }
#endif
  if (lib_id == libs::ilink::consts::id_module_dll_mlog)
  {
    return create_impl_mpl_mlog;
  }
#if (U3_MODULES_ENABLE_MDATA == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mdata)
  {
    return create_impl_mpl_mdata;
  }
#endif
#if (U3_MODULES_ENABLE_STORAGE == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mstorage)
  {
    return create_impl_mpl_mstorage;
  }
#endif
#if (U3_MODULES_ENABLE_USERS == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_musers)
  {
    return create_impl_mpl_musers;
  }
#endif
  if (lib_id == "appl_u3oko")
  {
    return create_impl_appl_u3oko;
  }

  ::libs::utility::checks::throw_exception (U3_FORMAT ("find create module funct {}", lib_id));
}


auto
get_delete_module_func (const std::string& plib_id) -> syn::IApplicationProxy::delete_func_type
{
  const auto lib_id = libs::utility::dlls::undecorate_dll_name (plib_id);
#if (U3_MODULES_ENABLE_EVENTS == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mevents)
  {
    return delete_impl_mpl_mevents;
  }
#endif
#if (U3_MODULES_ENABLE_GUI == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mgui)
  {
    return delete_impl_mpl_mgui;
  }
#endif
#if (U3_MODULES_ENABLE_HTTP == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mhttp)
  {
    return delete_impl_mpl_mhttp;
  }
#endif
  if (lib_id == libs::ilink::consts::id_module_dll_mlog)
  {
    return delete_impl_mpl_mlog;
  }
#if (U3_MODULES_ENABLE_MDATA == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mdata)
  {
    return delete_impl_mpl_mdata;
  }
#endif
#if (U3_MODULES_ENABLE_STORAGE == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_mstorage)
  {
    return delete_impl_mpl_mstorage;
  }
#endif
#if (U3_MODULES_ENABLE_USERS == 1)
  if (lib_id == libs::ilink::consts::id_module_dll_musers)
  {
    return delete_impl_mpl_musers;
  }
#endif
  if (lib_id == "appl_u3oko")
  {
    return delete_impl_appl_u3oko;
  }

  ::libs::utility::checks::throw_exception (U3_FORMAT ("find delete module funct {}", lib_id));
}
}   // namespace libs::proxy
