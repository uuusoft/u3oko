/**
\file       impl2http.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.03.2022
\project    u3_video_sender_dll
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../video-sender-includes_int.hpp"
#include "impl2http.hpp"

namespace dlls::terminals::video_sender::impl2http
{
void
Impl2Http::send_int (
  const InfoFilter&                    finfo,
  const syn::TransformInfo&            info,
  const syn::Buff2ModuleInfo::craw_ptr minfo,
  syn::IVideoBuf::raw_ptr              send_buf)
{
  U3_ASSERT (minfo);
  auto* ilink     = ::libs::iproperties::helpers::get_prop_links ();
  auto  data2appl = ilink->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();

  if (!data2appl)
  {
    U3_LOG_DATA_WRN ("empty data2appl, skip send msg to http" + VTOLOG (finfo.count_frames_) + VTOLOG (send_buf->get_dim_var (utils::dbufs::video::Dims::height)));
    return;
  }

  syn::IEvent::ptr rmsg;
  syn::IEvent::ptr irmsg;
  auto             dmsg  = ::libs::iproperties::helpers::create_event< syn::WrapperHttpEvent > (rmsg);
  auto             idmsg = ::libs::iproperties::helpers::create_event< syn::ZipDataEvent > (irmsg);

  idmsg->update_zip (send_buf);
  idmsg->set_number (finfo.count_frames_);

  auto              impl  = finfo.active_impl_.lock ();
  const std::string srcid = impl ? impl->get_source_name () : "";

  idmsg->set_id (srcid);
  // idmsg->set_id (appl::consts::id_zip_buf2http + srcid);

  dmsg->set_msg (irmsg);
  data2appl->send_msg (rmsg, syn::CallSyncs::async, syn::Calls::set);
}
}   // namespace dlls::terminals::video_sender::impl2http
