/**
\file       events-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mevents
*/
#include "../module-events-includes_int.hpp"
#include "consts/module-events-const-vals.hpp"
#include "events-module-syn.hpp"
#include "events-module.hpp"

namespace modules::mevents::appl
{
auto
EventsModule::get_recv_link_int () -> ::libs::ilink::appl::base::BaseModule::recv_links_type
{
  return { links_.get (libs::properties::vers::links::mids::events2appl) };
}


auto
EventsModule::catch_event_int (syn::IEvent::ptr& evnt) -> bool
{
  return true;
}


auto
EventsModule::is_now_thread_to_sleep_int (bool now_recv_evnt) -> bool
{
  return now_recv_evnt ? false : true;
}
}   // namespace modules::mevents::appl
