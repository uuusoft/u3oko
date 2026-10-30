/**
\file       log-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../module-log-includes_int.hpp"
#include "log-module.hpp"

namespace modules::mlog::appl
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
  ::libs::utility::checks::throw_ifn (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "alloc mem proxy");
}


void
LogModule::init_done_int ()
{
  U3_CALL_TRACE_DBG;
  super::init_done_int ();
  make_dir_for_logs ();
  open_log_file ();
}


void
LogModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  U3_CALL_TRACE_DBG;
  const std::string name_data = "";
  auto              lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  volatile auto     ipstorage = ::libs::iproperties::helpers::get_storage ();
  volatile auto     imstorage = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ();

  U3_MARK_UNUSED_HERE (ipstorage);
  U3_MARK_UNUSED_HERE (imstorage);

  auto temp_link = ::libs::utility::checks::ptr (lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      { { ::libs::link::consts::text::id_appl_name, "mpl_mlog" },
        { ::libs::link::consts::text::id_lib_name, "mpl_mlog" },
        { ::libs::link::consts::text::id_size_shared_mem, ::libs::link::consts::sizes::buf_all2log },
        { ::libs::link::consts::text::id_module_links, ::libs::link::details::ModuleLinks::log },
        { ::libs::link::consts::text::id_code_runs, ::libs::link::details::CodeRuns::appl } })));

  links_.set (syn::mids::log2appl, temp_link);

  //  нужно установить свои связи в свойства разделяемые и спользовать их
  {
    auto* proplinks = ::libs::iproperties::helpers::get_prop_links ();
    auto& links     = proplinks->update_links_lockfree ();
    auto  log2appl  = links_[syn::mids::log2appl];

    links.set (syn::mids::log2appl, log2appl);
    logger_ = log2appl;
  }
}


auto
LogModule::appl_deinit_int () -> bool
{
  U3_CALL_TRACE;
  flush_events ();

  {
    auto* links = ::libs::iproperties::helpers::get_prop_links ();
    links->update_links_lockfree ().reset_link (syn::mids::log2appl);
  }

  links_[syn::mids::log2appl]->destroy ();
  links_.reset_link (syn::mids::log2appl);
  return true;
}


void
LogModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::InfoLogEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::InfoLogEvent > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_info_log (props, msg);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::PropertyLogModuleEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::PropertyLogModuleEvent > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_property_log_module (props);
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

  catch_funcs_[syn::ProcessListLogsEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::ProcessListLogsEvent > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_list_logs (props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::ProcessLogEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::ProcessLogEvent > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_log (props);
      return {};
    }
    return msg;
  };
}
}   // namespace modules::mlog::appl
