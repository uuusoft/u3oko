/**
\file       events-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
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
::libs::ilink::appl::base::BaseModule::recv_links_type
EventsModule::get_recv_link_int ()
{
  return { links_.get (libs::properties::vers::links::mids::events2appl) };
}


bool
EventsModule::catch_event_int (syn::IEvent::ptr& evnt)
{
  return true;
}


bool
EventsModule::is_now_thread_to_sleep_int (bool now_recv_evnt)
{
  return now_recv_evnt ? false : true;
}
}   // namespace modules::mevents::appl
