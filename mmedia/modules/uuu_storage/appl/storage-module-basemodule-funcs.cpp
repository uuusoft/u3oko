/**
\file       storage-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_module_storage
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-storage-includes_int.hpp"
#include "storage-module.hpp"

namespace modules::uuu_storage::appl
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
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "alloc mem proxy");
}


void
StorageModule::init_done_int ()
{
}


void
StorageModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  const std::string                        name_data = "";
  const ::libs::link::details::CodeRuns    type_run  = ::libs::link::details::CodeRuns::appl;
  ::libs::ilink::LinkCreatorProxy::raw_ptr lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  U3_MARK_UNUSED auto                      ipstorage = ::libs::iproperties::helpers::get_storage ();

  auto temp_link = lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      type_run,
      name_data,
      "mpl_uuu_storage",
      info.company_name_,
      info.appl_name_,
      "subsys_storage",
      ::libs::link::details::ModuleLinks::storage,
      ::libs::link::consts::size::buf_appl2storage));

  links_.set (libs::properties::vers::links::mids::storage2appl, temp_link);

  //  Нужно установить свои связи в свойства разделяемые и спользовать их.
  {
    auto  proplinks    = U3_CAST_PROP (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    auto& links        = proplinks->update_links_lockfree ();
    auto  storage2appl = links_.get (libs::properties::vers::links::mids::storage2appl);

    links.set (libs::properties::vers::links::mids::storage2appl, storage2appl);
    logger_ = storage2appl;
  }

  {
    ::libs::events::IEvent::ptr rmsg;
    auto                        props = ::libs::iproperties::helpers::create_event< ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::uuu_storage::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (true);
    links_.get (libs::properties::vers::links::mids::storage2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }
}


bool
StorageModule::appl_deinit_int ()
{
  U3_XLOG_MARK ("StorageModule::deinit_int begin")
  if (links_.get (libs::properties::vers::links::mids::storage2appl))
  {
    ::libs::events::IEvent::ptr rmsg;
    auto                        props = ::libs::iproperties::helpers::create_event< ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::uuu_storage::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (false);
    links_.get (libs::properties::vers::links::mids::storage2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  {
    auto links = U3_CAST_PROP (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    links->update_links_lockfree ().reset_link (libs::properties::vers::links::mids::log2appl);
  }

  links_.get (libs::properties::vers::links::mids::storage2appl)->destroy ();
  links_.reset_link (libs::properties::vers::links::mids::storage2appl);
  return true;
}


void
StorageModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::PropertyStorageModuleEvent::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        U3_LOG_STORAGE_DEV ("catch PropertyStorageModuleEvent and sync")
        auto props = ::libs::iproperties::helpers::cast_event< syn::PropertyStorageModuleEvent > (msg);
        appl_event_props_.storage_module_->copy (props);
        create_impls (props);
        sync_status_impls ();
        load_binary_statistic ();
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::MemResourceStorageEvent::gen_get_mid ()] =
    [] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        U3_ASSERT_SIGNAL ("unimplemented");
        U3_MARK_UNUSED auto props = ::libs::iproperties::helpers::cast_event< syn::MemResourceStorageEvent > (msg);
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::GetRuntimeInfo::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::GetRuntimeInfo > (msg);
        U3_ASSERT (props);
        process_get_runtime_info (props);
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::GetObjects::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::GetObjects > (msg);
        U3_ASSERT (props);
        indexer_impl_->get_objects (props->objs_);
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::GetStatisticInfo::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        U3_ASSERT_SIGNAL ("unimplemented");
        auto props = ::libs::iproperties::helpers::cast_event< syn::GetStatisticInfo > (msg);
        U3_ASSERT (props);
        process_get_statistic_info (props);
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::ReadData::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::ReadData > (msg);
        process_read_data (props);
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::WriteData::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::WriteData > (msg);
        U3_ASSERT (props);
        U3_LOG_STORAGE_DBG ("write data");
        // debug - stop write
        // process_write_data (props);
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::UpdateStream::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::UpdateStream > (msg);
        U3_ASSERT (props);
        process_update_stream (props);
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (::libs::events::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
        U3_ASSERT (props);
        process_change_state_process (props);
        return ::libs::events::IEvent::ptr ();
      }
      return msg;
    };
}
}   // namespace modules::uuu_storage::appl
