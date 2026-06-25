/**
\file       event-props-for-application.cpp
\date       02.03.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilinks
*/
#include "../libs-ilink-includes_int.hpp"
#include "libs-ilink-appl-includes_int.hpp"
#include "event-props-for-application.hpp"

namespace libs::ilink::appl
{
void
EventPropsForApplication::init ()
{
  auto* pappl = ::libs::iproperties::helpers::create_event< syn::ApplicationProp > (main_appl_properties_);
  U3_XLOG_DBG ("EventPropsForApplication::init::---->" + TOLOG (pappl->get_messenger_impl ()) + PTR_TOLOG (pappl));
  ::libs::iproperties::helpers::create_event< syn::InfoCPUEvent > (info_cpu_);
  ::libs::iproperties::helpers::create_event< syn::PropertyLogModuleEvent > (module_log_);
  ::libs::iproperties::helpers::create_event< syn::PropertyStorageModuleEvent > (storage_module_);
}
}   // namespace libs::ilink::appl
