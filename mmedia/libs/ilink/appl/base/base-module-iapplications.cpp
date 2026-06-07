/**
\file       leaf-module-basemodule.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "base-module.hpp"

namespace libs::ilink::appl::base
{
void
BaseModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  sys_info_ = ::libs::helpers::sys::get_impl ();
}


void
BaseModule::init_appl_folders_int ()
{
  paths_ = std::make_shared< ::libs::iproperties::appl_paths::AppPaths > ();
  paths_->load_paths (appl_info_);
}


void
BaseModule::init_appl_data_int ()
{
  load_events_props ();
  update_events_props ();
}


void
BaseModule::init_proxys_int ()
{
  all2mem_    = ::utils::mem_funcs::impl::BlockMemAllocatorProxy::instance (paths_->get_path (::libs::iproperties::appl_paths::Paths::bins));
  all2buf_    = ::utils::dbufs::allocator::BufAllocatorProxy::instance (paths_->get_path (::libs::iproperties::appl_paths::Paths::bins));
  all2optim_  = ::libs::proxy::IOptimProxy::instance (paths_->get_path (::libs::iproperties::appl_paths::Paths::bins));
  all2events_ = ::libs::proxy::IEventsProxy::instance (paths_->get_path (::libs::iproperties::appl_paths::Paths::bins));

  U3_CHECK (all2mem_, "null all2mem");
  U3_CHECK (all2buf_, "empty all2buf");
  U3_CHECK (all2optim_, "null all2optim");
  U3_CHECK (all2events_, "null all2events");

  {
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
