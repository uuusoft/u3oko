/**
\file       events-module-basemodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    mevents
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-events-includes_int.hpp"
#include "consts/module-events-const-vals.hpp"
#include "events-module-syn.hpp"
#include "events-module.hpp"

namespace modules::mevents::appl
{
void
EventsModule::appl_init_int (const ::libs::link::appl::InitApplication& info)
{
  super::appl_init_int (info);
  check_process ();
}


void
EventsModule::init_proxys_int ()
{
  super::init_proxys_int ();
  U3_CHECK (::libs::iproperties::helpers::cast_prop_demons ()->get_mem_lockfree (), "create block mem allocator");
}


bool
EventsModule::appl_deinit_int ()
{
  U3_XLOG_MARK ("EventsModule::deinit_int begin");
  if (links_.get (libs::properties::vers::links::mids::events2appl))
  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::mevents::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (false);
    links_.get (libs::properties::vers::links::mids::events2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }

  {
    auto links = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    links->update_links_lockfree ().reset_link (libs::properties::vers::links::mids::events2appl);
  }

  links_.get (libs::properties::vers::links::mids::events2appl)->destroy ();
  links_.reset_link (libs::properties::vers::links::mids::events2appl);
  return true;
}


void
EventsModule::init_links_int (const ::libs::link::appl::InitApplication& info)
{
  const std::string                        name_data = "";
  ::libs::link::details::CodeRuns          type_run  = ::libs::link::details::CodeRuns::appl;
  ::libs::ilink::LinkCreatorProxy::raw_ptr lproxy    = ::libs::ilink::LinkCreatorProxy::instance ();

  auto temp_link = lproxy->impl ()->get_listen (
    ::libs::link::CreateInfo (
      type_run,
      name_data,
      "mpl_mevents",
      info.company_name_,
      info.appl_name_,
      "subsys_events",
      ::libs::link::details::ModuleLinks::events,
      ::libs::link::consts::size::buf_all2events));

  links_.set (libs::properties::vers::links::mids::events2appl, temp_link);

  {
    auto  proplinks = U3_CAST_PROP (syn::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ());
    auto& links     = proplinks->update_links_lockfree ();

    links.set (libs::properties::vers::links::mids::events2appl, links_.get (libs::properties::vers::links::mids::events2appl));
    logger_ = links_.get (libs::properties::vers::links::mids::events2appl);
  }

  {
    syn::IEvent::ptr rmsg;
    auto             props = ::libs::iproperties::helpers::create_event< syn::ChangDShowRunsSubSysLogEvent > (rmsg);

    props->change_appl_info (
      ::libs::ilog_events::AppllPartLogInfo (
        ::libs::ievents::props::modules::log::LogLevels::info,
        ::modules::mevents::appl::consts::module_name,
        ::libs::helpers::log::get_module_version ()),
      "");

    props->set_start (true);
    links_.get (libs::properties::vers::links::mids::events2appl)->send_msg (rmsg, ::libs::link::details::CallSyncs::async, ::libs::link::details::Calls::set);
  }
}   // namespace modules::mevents::appl


void
EventsModule::update_catch_funcs_int ()
{
  super::update_catch_funcs_int ();

  catch_funcs_[syn::ChangeStateProcessEvent::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::ChangeStateProcessEvent > (msg);
      U3_ASSERT (props);
      process_change_state_process (msg, props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::WrapperEventsEvent::gen_get_mid ()] =
    [] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    if (forward)
    {
      auto wrap_msg = ::libs::iproperties::helpers::cast_event< syn::WrapperEventsEvent > (msg);
      return wrap_msg->get_msg ();
    }
    return msg;
  };

  catch_funcs_[syn::AddEvent2Base::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    U3_LOG_EVENTS_DEV ("received syn::AddEvent2Base:" + TOLOG (msg->get_mid ()));
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::AddEvent2Base > (msg);
      U3_ASSERT (props);
      process_add_event2base (msg, props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::GetDataGraphsFromEventBase::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    U3_LOG_EVENTS_DEV ("received syn::GetDataGraphsFromEventBase:" + TOLOG (msg->get_mid ()));
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::GetDataGraphsFromEventBase > (msg);
      U3_ASSERT (props);
      process_get_data_graphs (msg, props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };

  catch_funcs_[syn::UpdateListener::gen_get_mid ()] =
    [this] (syn::IEvent::ptr& msg, bool forward, const syn::StateProcessEventExt& process_state) -> syn::IEvent::ptr {
    U3_LOG_EVENTS_DEV ("received syn::UpdateListener:" + TOLOG (msg->get_mid ()));
    if (forward)
    {
      auto props = ::libs::iproperties::helpers::cast_event< syn::UpdateListener > (msg);
      U3_ASSERT (props);
      process_update_listener (msg, props);
      return syn::IEvent::ptr ();
    }
    return msg;
  };
}


void
EventsModule::process_change_state_process (
  syn::IEvent::ptr&                     msg,
  syn::ChangeStateProcessEvent::raw_ptr props)
{
  try
  {
    if (!props->is_start ())
    {
      U3_LOG_EVENTS_INFO ("stop events module");
      stop_module_ = true;
      return;
    }
    U3_LOG_EVENTS_INFO ("start events module");
  }
  catch (const std::exception& e)
  {
    U3_LOG_EVENTS_EXCEPT (e.what ());
  }
}
}   // namespace modules::mevents::appl
