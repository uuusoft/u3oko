/**
\file       events-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mevents
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../module-events-includes_int.hpp"
#include "consts/module-events-const-vals.hpp"
#include "events-module-syn.hpp"
#include "events-module.hpp"

namespace modules::mevents::appl
{
void
EventsModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  U3_XLOG_DBG ("EventsModule::appl_init_int::---->");
  super::appl_init_int (info);
  check_process ();
}


void
EventsModule::init_proxys_int ()
{
  U3_XLOG_DBG ("EventsModule::init_proxys_int::---->");
  super::init_proxys_int ();
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "create block mem allocator");
}


auto
EventsModule::appl_deinit_int () -> bool
{
  U3_XLOG_MARK ("EventsModule::deinit_int::---->");
  if (links_.get (libs::properties::vers::links::mids::events2appl))
  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        ::libs::events_base::props::modules::log::LogLevels::info,
        ::modules::mevents::appl::consts::module_name,
        ::libs::utility::log::get_module_version ()),
      "");

    props->set_start (false);
    links_.get (libs::properties::vers::links::mids::events2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  {
    auto* links = ::libs::iproperties::helpers::get_prop_links ();
    links->update_links_lockfree ().reset_link (libs::properties::vers::links::mids::events2appl);
  }

  links_.get (libs::properties::vers::links::mids::events2appl)->destroy ();
  links_.reset_link (libs::properties::vers::links::mids::events2appl);
  U3_XLOG_MARK ("EventsModule::deinit_int::<----");
  return true;
}


void
EventsModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  U3_XLOG_DBG ("EventsModule::init_links_int::---->");
  const std::string name_data = "";
  auto              type_run  = ::libs::link::details::CodeRuns::appl;
  auto              lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();

  auto temp_link = lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      type_run,
      name_data,
      "mpl_mevents",
      info.company_name_,
      info.appl_name_,
      "subsys_events",
      ::libs::link::details::ModuleLinks::events,
      ::libs::link::consts::sizes::buf_all2events));

  links_.set (libs::properties::vers::links::mids::events2appl, temp_link);

  {
    auto* proplinks = ::libs::iproperties::helpers::get_prop_links ();
    auto& links     = proplinks->update_links_lockfree ();

    links.set (libs::properties::vers::links::mids::events2appl, links_.get (libs::properties::vers::links::mids::events2appl));
    logger_ = links_.get (libs::properties::vers::links::mids::events2appl);
  }

  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangeStateSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::events_log::AppllPartLogInfo (
        ::libs::events_base::props::modules::log::LogLevels::info,
        ::modules::mevents::appl::consts::module_name,
        ::libs::utility::log::get_module_version ()),
      "");

    props->set_start (true);
    links_.get (libs::properties::vers::links::mids::events2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }
  U3_XLOG_DBG ("EventsModule::init_links_int::<----");
}   // namespace modules::mevents::appl


void
EventsModule::init_done_int ()
{
  U3_XLOG_DBG ("EventsModule::init_done_int::---->");
  super::init_done_int ();
  prepare_base ();
  U3_XLOG_DBG ("EventsModule::init_done_int::<----");
}


void
EventsModule::update_catch_funcs_int ()
{
  U3_XLOG_DBG ("EventsModule::update_catch_funcs_int::---->");
  super::update_catch_funcs_int ();

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
      U3_ASSERT (props);
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
    U3_LOG_EVENTS_DEV ("received syn::AddEvent2EventsMsg:" + STOLOG (msg->get_mid ()));
    if (forward)
    {
      auto* props = ::libs::iproperties::helpers::cast_event< syn::AddEvent2EventsMsg > (msg);
      U3_ASSERT (props);
      process_add_event2base (msg, props);
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
      U3_ASSERT (props);
      process_get_data_graphs (msg, props);
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
      U3_ASSERT (props);
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
      U3_ASSERT (props);
      process_get_events_from_base (msg, props);
      return {};
    }
    return msg;
  };
}
}   // namespace modules::mevents::appl
