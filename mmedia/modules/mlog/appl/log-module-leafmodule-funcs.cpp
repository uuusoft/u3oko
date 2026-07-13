/**
\file       log-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mlog
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../module-log-includes_int.hpp"
#include "log-module.hpp"

namespace modules::mlog::appl
{
auto
LogModule::get_recv_link_int () -> ::libs::ilink::appl::base::BaseModule::recv_links_type
{
  return { links_[syn::mids::log2appl] };
}


auto
LogModule::catch_event_int (syn::IEvent::ptr& evnt) -> bool
{
  return true;
}


auto
LogModule::is_now_thread_to_sleep_int (bool now_recv_evnt) -> bool
{
  // EAI-MODULE-REFACT
#if 0  
  auto* logprop = ::libs::iproperties::helpers::cast_event< syn::PropertyLogModuleEvent > (appl_event_props_.module_log_);
  if (logprop && events_for_save_.size () > logprop->get_val (syn::LogVals::max_cache_events))
  {
    flush_events ();
  }
#endif
  return now_recv_evnt ? false : true;
}
}   // namespace modules::mlog::appl
