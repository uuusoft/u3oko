/**
\file       leaf-module.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_ilink
*/
#include "../../libs-ilink-includes_int.hpp"
#include "../libs-ilink-appl-includes_int.hpp"
#include "leaf-module.hpp"

namespace libs::ilink::appl::leaf
{
auto
LeafModule::catch_event (::libs::events::IEvent::ptr& evnt) -> bool
{
  return catch_event_int (evnt);
}


auto
LeafModule::is_now_thread_to_sleep (bool now_recv_evnt) -> bool
{
  return is_now_thread_to_sleep_int (now_recv_evnt);
}
}   // namespace libs::ilink::appl::leaf
