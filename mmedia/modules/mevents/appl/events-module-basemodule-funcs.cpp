/**
\file       events-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../module-events-includes_int.hpp"
// #include "consts/module-events-const-vals.hpp"
#include "events-module-syn.hpp"
#include "events-module.hpp"

namespace modules::mevents::appl
{
void
EventsModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  U3_CALL_TRACE_DBG;
  super::appl_init_int (info);
  check_process ();
}


void
EventsModule::init_proxys_int ()
{
  U3_CALL_TRACE_DBG;
  super::init_proxys_int ();
  ::libs::utility::checks::throw_ifn (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "create block mem allocator");
}


auto
EventsModule::appl_deinit_int () -> bool
{
  U3_CALL_TRACE;
  if (links_[syn::mids::events2appl])
  {
    auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > ();
    revnt->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        ::libs::events_base::props::modules::log::LogLevels::info,
        ::modules::mevents::appl::consts::module_name,
        ::libs::utility::log::get_module_version ()),
      "");

    revnt->set_start (false);
    links_[syn::mids::events2appl]->send_msg (evnt);
  }

  {
    auto* links = ::libs::iproperties::helpers::get_prop_links ();
    links->update_links_lockfree ().reset_link (syn::mids::events2appl);
  }

  links_[syn::mids::events2appl]->destroy ();
  links_.reset_link (syn::mids::events2appl);
  return true;
}


void
EventsModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  U3_CALL_TRACE_DBG;
  const std::string name_data = "";
  auto              lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();
  auto              temp_link = lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      { { ::libs::link::consts::text::id_appl_name, "mpl_mevents" },
        { ::libs::link::consts::text::id_lib_name, "mpl_mevents" },
        { ::libs::link::consts::text::id_size_shared_mem, ::libs::link::consts::sizes::buf_all2events },
        { ::libs::link::consts::text::id_module_links, ::libs::link::details::ModuleLinks::events },
        { ::libs::link::consts::text::id_code_runs, ::libs::link::details::CodeRuns::appl } }));

  links_.set (syn::mids::events2appl, temp_link);

  {
    auto* proplinks = ::libs::iproperties::helpers::get_prop_links ();
    auto& links     = proplinks->update_links_lockfree ();

    links.set (syn::mids::events2appl, links_[syn::mids::events2appl]);
    logger_ = links_[syn::mids::events2appl];
  }

  {
    auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > ();
    revnt->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        ::libs::events_base::props::modules::log::LogLevels::info,
        ::modules::mevents::appl::consts::module_name,
        ::libs::utility::log::get_module_version ()),
      "");

    revnt->set_start (true);
    links_[syn::mids::events2appl]->send_msg (evnt);
  }
}   // namespace modules::mevents::appl


void
EventsModule::init_done_int ()
{
  U3_CALL_TRACE_DBG;
  super::init_done_int ();
  impl_->start ();   // prepare_base ();
}


void
EventsModule::update_catch_funcs_int ()
{
  U3_CALL_TRACE_DBG;
  super::update_catch_funcs_int ();

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_change_state_process (msg, props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::WrapperEventsEvent::gen_get_mid ()] =
    [] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* wrap_msg = ::libs::iproperties::helpers::cast_event< syn::WrapperEventsEvent > (msg);
      return wrap_msg->get_msg ();
    }
    return msg;
  };

  catch_funcs_[syn::AddEvent2EventsMsg::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    U3_LOG_EVENTS_DBG ("received syn::AddEvent2EventsMsg:" + STOLOG (msg->get_mid ()));
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::AddEvent2EventsMsg > (msg);
      ::libs::utility::checks::throw_ifn (props);
      impl_->add_event2base (msg, props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::GetDataGraphsEventsMsg::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    U3_LOG_EVENTS_DEV ("received syn::GetDataGraphsEventsMsg:" + STOLOG (msg->get_mid ()));
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::GetDataGraphsEventsMsg > (msg);
      ::libs::utility::checks::throw_ifn (props);
      impl_->get_data_graphs (msg, props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::UpdateListenerEventsMsg::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    U3_LOG_EVENTS_DEV ("received syn::UpdateListenerEventsMsg:" + STOLOG (msg->get_mid ()));
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::UpdateListenerEventsMsg > (msg);
      ::libs::utility::checks::throw_ifn (props);
      process_update_listener (msg, props);
      return {};
    }
    return msg;
  };

  catch_funcs_[syn::GetEventsFromBase::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    U3_LOG_EVENTS_DBG ("received syn::GetEventsFromBase:" + STOLOG (msg->get_mid ()));
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::GetEventsFromBase > (msg);
      ::libs::utility::checks::throw_ifn (props);
      impl_->get_events_from_base (msg, props);
      return {};
    }
    return msg;
  };
}
}   // namespace modules::mevents::appl
