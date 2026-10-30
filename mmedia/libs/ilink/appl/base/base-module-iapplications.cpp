/**
\file       base-module-iapplication.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "base-module.hpp"

namespace libs::ilink::appl::base
{
void
BaseModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  ::libs::utility::checks::throw_ifn (!sys_info_, "!sys_info_");
  sys_info_ = ::libs::utility::sys::get_impl ();
}


void
BaseModule::init_appl_folders_int ()
{
  ::libs::utility::checks::throw_ifn (!paths_, "!sys_info_");
  paths_ = std::make_shared< ::libs::iproperties::appl_paths::AppPaths > ();
  paths_->load_paths (appl_info_);
}


void
BaseModule::init_appl_data_int ()
{
  U3_CALL_TRACE_INFO_DBG (TOLOG (text_id_module_));
  load_events_props ();
  update_events_props ();
}


void
BaseModule::init_proxys_int ()
{
  U3_CALL_TRACE_INFO_DBG (TOLOG (text_id_module_));
  ::libs::utility::checks::throw_ifn (all2mem_ = syn::BlockMemAllocatorProxy::instance (paths_->get_path (syn::Paths::bins)), "null all2mem");
  ::libs::utility::checks::throw_ifn (all2buf_ = syn::BufAllocatorProxy::instance (paths_->get_path (syn::Paths::bins)), "null all2buf");
  ::libs::utility::checks::throw_ifn (all2optim_ = ::libs::proxy::IOptimProxy::instance (paths_->get_path (syn::Paths::bins)), "null all2optim");
  ::libs::utility::checks::throw_ifn (all2events_ = ::libs::proxy::IEventsProxy::instance (paths_->get_path (syn::Paths::bins)), "null all2events");

  {
    U3_XLOG_DBG ("BaseModule::init_proxys_int:: update shared propertyes");
    auto orinfo = ::libs::iproperties::helpers::cast_prop_demons ();

    syn::ISharedProperty::lock_type lock (orinfo->get_sync ());
    orinfo->set_bufs_lockfree (all2buf_);
    orinfo->set_mem_lockfree (all2mem_);
    orinfo->set_optim_lockfree (all2optim_);
    orinfo->set_events_lockfree (all2events_);
  }

  appl_event_props_.init ();
}


void
BaseModule::init_done_int ()
{
}


void
BaseModule::update_catch_funcs_int ()
{
}


void
BaseModule::appl_force_stop_int ()
{
  stop_module_ = true;
}
}   // namespace libs::ilink::appl::base
