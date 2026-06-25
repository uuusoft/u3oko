/**
\file       http-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.08.2018
\project    mhttp
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "http-module-syn.hpp"
#include "http-module.hpp"

namespace modules::mhttp::appl
{
::libs::ilink::appl::base::BaseModule::recv_links_type
HttpModule::get_recv_link_int ()
{
  return { links_.get (syn::mids::http2appl) };
}


bool
HttpModule::catch_event_int (syn::IEvent::ptr& evnt)
{
  return true;
}


bool
HttpModule::is_now_thread_to_sleep_int (bool now_recv_evnt)
{
  return now_recv_evnt ? false : true;
}
}   // namespace modules::mhttp::appl
