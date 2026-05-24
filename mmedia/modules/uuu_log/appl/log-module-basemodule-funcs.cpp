/**
\file       log-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_log
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-log-includes_int.hpp"
#include "log-module.hpp"

namespace modules::uuu_log::appl
{
void
LogModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  super::appl_init_int (info);
  check_process ();
}


void
LogModule::init_proxys_int ()
{
  super::init_proxys_int ();
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "alloc mem proxy");
}


void
LogModule::init_done_int ()
{
  make_dir_for_logs ();
  open_log_file ();
}


void
LogModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  const std::string                        name_data = "";
  const ::libs::link::details::CodeRuns    type_run  = ::libs::link::details::CodeRuns::appl;
  ::libs::ilink::LinkCreatorProxy::raw_ptr lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  volatile auto                            ipstorage = ::libs::iproperties::helpers::get_storage ();
  volatile auto                            imstorage = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ();

  ipstorage;
  imstorage;

  auto temp_link = ::libs::helpers::check::ptr (lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      type_run,
      name_data,
      "mpl_uuu_log",
      info.company_name_,
      info.appl_name_,
      "subsys_appl2log",
      ::libs::link::details::ModuleLinks::log,
      ::libs::link::consts::size::buf_all2log)));

  links_.set (libs::properties::vers::links::mids::log2appl, temp_link);

  ::libs::helpers::check::must_valid_ptr (links_.get (libs::properties::vers::links::mids::log2appl));

  //  нужно установить свои связи в свойства разделяемые и спользовать их
  {
    auto  proplinks = U3_CAST_PROP (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    auto& links     = proplinks->update_links_lockfree ();
    auto  log2appl  = links_.get (libs::properties::vers::links::mids::log2appl);

    links.set (libs::properties::vers::links::mids::log2appl, log2appl);
    logger_ = log2appl;
  }
#if 0
  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::uuu_log::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (true);
    links_.get(libs::properties::vers::links::mids::mdata2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }
#endif
}


bool
LogModule::appl_deinit_int ()
{
  U3_XLOG_MARK ("LogModule::deinit_int begin")
  flush_events ();

#if 0
  if (links_.get(libs::properties::vers::links::mids::mdata2appl))
  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::uuu_log::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (false);
    links_.get(libs::properties::vers::links::mids::mdata2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }
#endif
  {
    auto links = U3_CAST_PROP (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    links->update_links_lockfree ().reset_link (libs::properties::vers::links::mids::log2appl);
  }

  links_.get (libs::properties::vers::links::mids::log2appl)->destroy ();
  links_.reset_link (libs::properties::vers::links::mids::log2appl);
  return true;
}


void
LogModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::InfoLogEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::InfoLogEvent > (msg);
        U3_ASSERT (props);
        process_info_log (props, msg);
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::PropertyLogModuleEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::PropertyLogModuleEvent > (msg);
        U3_ASSERT (props);
        process_property_log_module (props);
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
        U3_ASSERT (props);
        process_change_state_process (props);
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::ProcessListLogsEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::ProcessListLogsEvent > (msg);
        U3_ASSERT (props);
        process_list_logs (props);
        return syn::IEvent::ptr ();
      }
      return msg;
    };

  catch_funcs_[syn::ProcessLogEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) {
      if (forward)
      {
        auto props = ::libs::iproperties::helpers::cast_event< syn::ProcessLogEvent > (msg);
        U3_ASSERT (props);
        process_log (props);
        return syn::IEvent::ptr ();
      }
      return msg;
    };
}
}   // namespace modules::uuu_log::appl
