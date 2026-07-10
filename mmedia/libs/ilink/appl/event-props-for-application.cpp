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
  U3_XLOG_DBG ("EventPropsForApplication::init::---->");
  main_appl_properties_ = ::libs::iproperties::helpers::create_event< syn::ApplicationProp > ().first;
  info_cpu_             = ::libs::iproperties::helpers::create_event< syn::InfoCPUEvent > ().first;
  module_log_           = ::libs::iproperties::helpers::create_event< syn::PropertyLogModuleEvent > ().first;
  storage_module_       = ::libs::iproperties::helpers::create_event< syn::PropertyStorageModuleEvent > ().first;
}
}   // namespace libs::ilink::appl
