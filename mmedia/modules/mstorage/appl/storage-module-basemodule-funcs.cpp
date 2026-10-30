/**
\file       storage-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../module-storage-includes_int.hpp"
#include "storage-module.hpp"

namespace modules::mstorage::appl
{
void
StorageModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  super::appl_init_int (info);
}


void
StorageModule::init_proxys_int ()
{
  super::init_proxys_int ();
  ::libs::utility::checks::throw_ifn (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "alloc mem proxy");
}


void
StorageModule::init_done_int ()
{
  super::init_done_int ();
}


void
StorageModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  U3_CALL_TRACE_DBG;
  auto                lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  U3_MARK_UNUSED auto ipstorage = ::libs::iproperties::helpers::get_storage ();

  auto temp_link = lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      { { ::libs::link::consts::text::id_appl_name, "mpl_mstorage" },
        { ::libs::link::consts::text::id_lib_name, "mpl_mstorage" },
        { ::libs::link::consts::text::id_size_shared_mem, ::libs::link::consts::sizes::buf_appl2storage },
        { ::libs::link::consts::text::id_module_links, ::libs::link::details::ModuleLinks::storage },
        { ::libs::link::consts::text::id_code_runs, ::libs::link::details::CodeRuns::appl } }));

  links_.set (syn::mids::storage2appl, temp_link);

  //  Нужно установить свои связи в свойства разделяемые и спользовать их.
  {
    auto* proplinks    = ::libs::iproperties::helpers::get_prop_links ();
    auto& links        = proplinks->update_links_lockfree ();
    auto  storage2appl = links_[syn::mids::storage2appl];

    links.set (syn::mids::storage2appl, storage2appl);
    logger_ = storage2appl;
  }

  {
    auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > ();

    revnt->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        ::libs::events_base::props::modules::log::LogLevels::info,
        ::modules::mstorage::appl::consts::module_name,
        ::libs::utility::log::get_module_version ()),
      "");

    revnt->set_start (true);
    links_[syn::mids::storage2appl]->send_msg (evnt);
  }
}


auto
StorageModule::appl_deinit_int () -> bool
{
  U3_CALL_TRACE;
  if (links_[syn::mids::storage2appl])
  {
    auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > ();

    revnt->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        ::libs::events_base::props::modules::log::LogLevels::info,
        ::modules::mstorage::appl::consts::module_name,
        ::libs::utility::log::get_module_version ()),
      "");

    revnt->set_start (false);
    links_[syn::mids::storage2appl]->send_msg (evnt);
  }

  {
    auto* links = ::libs::iproperties::helpers::get_prop_links ();
    links->update_links_lockfree ().reset_link (syn::mids::log2appl);
  }

  links_[syn::mids::storage2appl]->destroy ();
  links_.reset_link (syn::mids::storage2appl);
  return true;
}


void
StorageModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::PropertyStorageModuleEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      U3_LOG_STORAGE_DEV ("catch PropertyStorageModuleEvent and sync")
      auto* props = ::libs::iproperties::helpers::cast_event< syn::PropertyStorageModuleEvent > (msg);
      appl_event_props_.storage_module_->copy (props);
      create_impls (props);
      sync_status_impls ();
      load_binary_statistic ();
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_change_state_process (props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::MemResourceStorageEvent::gen_get_mid ()] =
    [] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      ::libs::utility::checks::throw_exception ("unimplemented");
      U3_MARK_UNUSED auto* props = ::libs::iproperties::helpers::cast_event< syn::MemResourceStorageEvent > (msg);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::GetRuntimeInfo::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::GetRuntimeInfo > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_get_runtime_info (props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::GetObjects::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::GetObjects > (msg);
      ::libs::utility::checks::throw_ifn (props);
      indexer_impl_->get_objects (props->objs_);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::GetStatisticInfo::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      ::libs::utility::checks::throw_exception ("unimplemented");
      auto* props = ::libs::iproperties::helpers::cast_event< syn::GetStatisticInfo > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_get_statistic_info (props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::ReadData::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::ReadData > (msg);
      process_read_data (props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::WriteData::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::WriteData > (msg);
      ::libs::utility::checks::throw_ifn (props);
      U3_LOG_STORAGE_DBG ("write data");
      // debug - stop write
      // process_write_data (props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::UpdateStream::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::UpdateStream > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_update_stream (props);
      return {};
    }
    return msg;
  };
}
}   // namespace modules::mstorage::appl
