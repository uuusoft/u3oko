/**
\file       log-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mlog
*/
#define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
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
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "alloc mem proxy");
}


void
LogModule::init_done_int ()
{
  U3_XLOG_DBG ("LogModule::init_done_int::---->");
  super::init_done_int ();
  make_dir_for_logs ();
  open_log_file ();
  U3_XLOG_DBG ("LogModule::init_done_int::<----");
}


void
LogModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  U3_XLOG_DBG ("LogModule::init_links_int::---->");
  const std::string                        name_data = "";
  const ::libs::link::details::CodeRuns    type_run  = ::libs::link::details::CodeRuns::appl;
  ::libs::ilink::LinkCreatorProxy::raw_ptr lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  volatile auto                            ipstorage = ::libs::iproperties::helpers::get_storage ();
  volatile auto                            imstorage = ::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree ();

  U3_MARK_UNUSED_HERE (ipstorage);
  U3_MARK_UNUSED_HERE (imstorage);
#if 1
  auto temp_link = ::libs::utility::check::ptr (lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      { { ::libs::link::consts::text::id_appl_name, "mpl_mlog" },
        { ::libs::link::consts::text::id_lib_name, "mpl_mlog" },
        { ::libs::link::consts::text::id_subsys_name, "subsys_log" },
        { ::libs::link::consts::text::id_size_shared_mem, ::libs::link::consts::sizes::buf_all2log },
        { ::libs::link::consts::text::id_module_links, ::libs::link::details::ModuleLinks::log },
        { ::libs::link::consts::text::id_code_runs, type_run } })));
#else
  auto temp_link = ::libs::utility::check::ptr (lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      type_run,
      name_data,
      "mpl_mlog",
      info.company_name_,
      info.appl_name_,
      "subsys_appl2log",
      ::libs::link::details::ModuleLinks::log,
      ::libs::link::consts::sizes::buf_all2log)));
#endif
  links_.set (syn::mids::log2appl, temp_link);

  //  нужно установить свои связи в свойства разделяемые и спользовать их
  {
    auto* proplinks = ::libs::iproperties::helpers::get_prop_links ();
    auto& links     = proplinks->update_links_lockfree ();
    auto  log2appl  = links_[syn::mids::log2appl];

    links.set (syn::mids::log2appl, log2appl);
    logger_ = log2appl;
  }
  U3_XLOG_DBG ("LogModule::init_links_int::<----");
}


auto
LogModule::appl_deinit_int () -> bool
{
  U3_XLOG_MARK ("LogModule::deinit_int::---->")
  flush_events ();

  {
    auto* links = ::libs::iproperties::helpers::get_prop_links ();
    links->update_links_lockfree ().reset_link (syn::mids::log2appl);
  }

  links_[syn::mids::log2appl]->destroy ();
  links_.reset_link (syn::mids::log2appl);
  U3_XLOG_MARK ("LogModule::deinit_int::<----")
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
      U3_ASSERT (props);
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
      U3_ASSERT (props);
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
      U3_ASSERT (props);
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
      U3_ASSERT (props);
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
      U3_ASSERT (props);
      process_log (props);
      return {};
    }
    return msg;
  };
}
}   // namespace modules::mlog::appl
