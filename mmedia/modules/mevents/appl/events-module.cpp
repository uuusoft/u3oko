/**
\file       events-module.cpp
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
free_error_callback (void* parg, int code, const char* msg)
{
  U3_CALL_TRACE_DBG;
  auto*             parent     = ::libs::utility::casts::reinterpret_cast_helper< EventsModule* > (parg);
  const std::string error_text = std::string (msg) + ", " + std::to_string (code);
  parent->error_callback (error_text);
}


EventsModule::EventsModule ()
{
  U3_CALL_TRACE_DBG;
  text_id_module_ = ::libs::ilink::consts::id_events;
#if (U3_COMMERCIAL_PART == 1)
  impl_ = std::make_unique< impls::sqlite::SqliteEventModuleImpl > ();
#else
  impl_ = std::make_unique< impls::test::TestEventModuleImpl > ();
#endif
}


EventsModule::~EventsModule ()
{
  try
  {
    impl_->stop ();
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
  }
}


void
EventsModule::check_process ()
{
}


void
EventsModule::error_callback (const std::string& error_text)
{
  U3_LOG_EVENTS_ERROR (std::string ("sqlite error: ") + error_text);
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
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
    process_error (msg, excpt.what ());
  }
}


void
EventsModule::process_update_listener (
  syn::IEvent::ptr&                     msg,
  syn::UpdateListenerEventsMsg::raw_ptr props)
{
  U3_CALL_TRACE_DBG;
  try
  {
    switch (props->get_action ())
    {
    case syn::SubscribeActions::enable:
      U3_LOG_EVENTS_DEV ("syn::SubscribeActions::enable == action");
      break;
    case syn::SubscribeActions::disable:
      U3_LOG_EVENTS_DEV ("syn::SubscribeActions::disable == action");
      break;
    default:
      U3_LOG_EVENTS_ERROR ("unknown syn::SubscribeActions value");
      break;
    }
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
    process_error (msg, excpt.what ());
  }
}


auto
process_error (syn::IEvent::ptr& msg, const std::string_view info) noexcept -> void
{
  U3_CALL_TRACE;
  try
  {
    auto* props = ::libs::iproperties::helpers::cast_event< syn::OpsStatusEvent > (msg);
    ::libs::utility::checks::throw_ifn (props, "failed cast to OpsStatusEvent for return error" + STOLOG (info));
    props->set_ops_status (::libs::events_base::OpsStatus::failed);
    props->set_ops_info (std::string (info));
  }
  catch (const std::exception& excpt)
  {
    U3_LOG_EVENTS_EXCEPT (excpt.what ());
  }
}
}   // namespace modules::mevents::appl
