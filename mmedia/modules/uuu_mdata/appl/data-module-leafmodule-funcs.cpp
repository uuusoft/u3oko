/**
\file       data-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_module_data
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-mdata-includes_int.hpp"
#include "data-module.hpp"

namespace modules::uuu_mdata::appl
{
::libs::ilink::appl::base::BaseModule::recv_links_type
DataModule::get_recv_link ()
{
  return { links_.get (libs::properties::vers::links::mids::mdata2appl) };
  // recv_links_type ret;
  // ret.emplace_back (links_.get (libs::properties::vers::links::mids::mdata2appl));
  // return ret;
}


bool
DataModule::catch_event (syn::IEvent::ptr& evnt)
{
  return true;
}


bool
DataModule::is_now_thread_to_sleep (bool now_recv_evnt)
{
  return now_recv_evnt ? false : true;
}
}   // namespace modules::uuu_mdata::appl
