/**
\file       log-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mlog
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-log-includes_int.hpp"
#include "log-module.hpp"

namespace modules::mlog::appl
{
::libs::ilink::appl::base::BaseModule::recv_links_type
LogModule::get_recv_link_int ()
{
  return { links_.get (libs::properties::vers::links::mids::log2appl) };
}


bool
LogModule::catch_event_int (syn::IEvent::ptr& evnt)
{
  return true;
}


bool
LogModule::is_now_thread_to_sleep_int (bool now_recv_evnt)
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
