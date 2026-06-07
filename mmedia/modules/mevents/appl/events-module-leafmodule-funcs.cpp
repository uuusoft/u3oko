/**
\file       events-module-leafmodule-funcs.cpp
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
::libs::ilink::appl::base::BaseModule::recv_links_type
EventsModule::get_recv_link ()
{
  return { links_.get (libs::properties::vers::links::mids::events2appl) };
  // recv_links_type ret;
  // ret.push_back (links_.get (libs::properties::vers::links::mids::events2appl));
  // return ret;
}


bool
EventsModule::catch_event (syn::IEvent::ptr& evnt)
{
  return true;
}


bool
EventsModule::is_now_thread_to_sleep (bool now_recv_evnt)
{
  return now_recv_evnt ? false : true;
}
}   // namespace modules::mevents::appl
