/**
\file       base-module-iapplication.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "base-module.hpp"

namespace libs::ilink::appl::base
{
void
BaseModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  U3_CHECK (!sys_info_, "!sys_info_");
  sys_info_ = ::libs::utility::sys::get_impl ();
}


void
BaseModule::init_appl_folders_int ()
{
  U3_CHECK (!paths_, "!sys_info_");
  paths_ = std::make_shared< ::libs::iproperties::appl_paths::AppPaths > ();
  paths_->load_paths (appl_info_);
}


void
BaseModule::init_appl_data_int ()
{
  U3_XLOG_DBG ("BaseModule::init_appl_data_int::---->" + TOLOG (text_id_module_));
  load_events_props ();
  update_events_props ();
}


void
BaseModule::init_proxys_int ()
{
  U3_XLOG_DBG ("BaseModule::init_proxys_int::---->" + TOLOG (text_id_module_));

  U3_CHECK (all2mem_ = syn::BlockMemAllocatorProxy::instance (paths_->get_path (syn::Paths::bins)), "null all2mem");
  U3_CHECK (all2buf_ = syn::BufAllocatorProxy::instance (paths_->get_path (syn::Paths::bins)), "null all2buf");
  U3_CHECK (all2optim_ = ::libs::proxy::IOptimProxy::instance (paths_->get_path (syn::Paths::bins)), "null all2optim");
  U3_CHECK (all2events_ = ::libs::proxy::IEventsProxy::instance (paths_->get_path (syn::Paths::bins)), "null all2events");

#if 1
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
#endif
  U3_XLOG_DBG ("BaseModule::init_proxys_int::<----");
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
