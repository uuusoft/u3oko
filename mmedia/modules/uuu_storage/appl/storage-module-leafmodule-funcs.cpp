/**
\file       storage-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_module_storage
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-storage-includes_int.hpp"
#include "storage-module.hpp"

namespace modules::uuu_storage::appl
{
::libs::ilink::appl::base::BaseModule::recv_links_type
StorageModule::get_recv_link ()
{
  recv_links_type ret;
  ret.push_back (links_.get (libs::properties::vers::links::mids::storage2appl));
  return ret;
}


bool
StorageModule::catch_event (::libs::events::IEvent::ptr& evnt)
{
  return true;
}


bool
StorageModule::is_now_thread_to_sleep (bool now_recv_evnt)
{
  return now_recv_evnt ? false : true;
}
}   // namespace modules::uuu_storage::appl
