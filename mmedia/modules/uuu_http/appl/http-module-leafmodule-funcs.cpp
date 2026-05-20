/**
\file       http-module-leafmodule-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.08.2018
\project    u3_http_module
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "../module-http-includes-special.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "http-module-syn.hpp"
#include "http-module.hpp"

namespace modules::uuu_http::appl
{
::libs::ilink::appl::base::BaseModule::recv_links_type
HttpModule::get_recv_link ()
{
  recv_links_type ret;
  ret.push_back (links_.get (syn::mids::http2appl));
  return ret;
}


bool
HttpModule::catch_event (syn::IEvent::ptr& evnt)
{
  return true;
}


bool
HttpModule::is_now_thread_to_sleep (bool now_recv_evnt)
{
  return now_recv_evnt ? false : true;
}
}   // namespace modules::uuu_http::appl
