/**
\file       storage-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../-module-storage-includes-int.hpp"
#include "storage-module.hpp"

namespace modules::mstorage::appl
{
auto
StorageModule::get_recv_link_int () -> ::libs::ilink::appl::base::BaseModule::recv_links_type
{
  return { links_[syn::mids::storage2appl] };
}


auto
StorageModule::catch_event_int (syn::IEvent::ptr& evnt) -> bool
{
  return true;
}


auto
StorageModule::is_now_thread_to_sleep_int (bool now_recv_evnt) -> bool
{
  return now_recv_evnt ? false : true;
}
}   // namespace modules::mstorage::appl
