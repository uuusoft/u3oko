/**
\file       impl2storage.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
\project    u3_video_sender_dll
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../video-sender-includes_int.hpp"
#include "impl2storage-syn.hpp"
#include "impl2storage.hpp"

namespace dlls::terminals::video_sender::impl2storage
{
Impl2Storage::~Impl2Storage ()
{
  close_stream ();
}


void
Impl2Storage::send_int (
  const InfoFilter&                    finfo,
  const syn::TransformInfo&            info,
  const syn::Buff2ModuleInfo::craw_ptr minfo,
  syn::IVideoBuf::raw_ptr              send_buf)
{
  U3_ASSERT (minfo);
  if (active_stream_.empty ())
  {
    open_stream ();
  }

  syn::IEvent::ptr rmsg;
  syn::IEvent::ptr irmsg;
  auto             dmsg  = ::libs::iproperties::helpers::create_event< syn::WriteData > (rmsg);
  auto             idmsg = ::libs::iproperties::helpers::create_event< syn::ZipDataEvent > (irmsg);

  dmsg->set_msg (irmsg);
  dmsg->set_stream_id (active_stream_);
  idmsg->set_id (::dlls::terminals::video_sender::consts::id_zip_buf2storage);
  idmsg->set_number (finfo.count_frames_);
  idmsg->update_zip (send_buf);

  send_message (rmsg, syn::CallSyncs::async, syn::Calls::set);
}


void
Impl2Storage::open_stream ()
{
  if (!active_stream_.empty ())
  {
    return;
  }

  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< syn::UpdateStream > (rmsg);

  dmsg->obj_id_.val_ = "unimplemented add name source";
  dmsg->action_      = ::libs::istorage_events::StreamUpdates::open;
  dmsg->direction_   = ::libs::istorage_events::StreamDirections::unknown;
  dmsg->operation_   = ::libs::istorage_events::StreamActions::write;

  send_message (rmsg, syn::CallSyncs::sync, syn::Calls::request);

  dmsg           = ::libs::iproperties::helpers::cast_event< syn::UpdateStream > (rmsg);
  active_stream_ = dmsg->stream_id_;

  U3_CHECK (!active_stream_.empty (), "received null stread_id for write data");
}


void
Impl2Storage::close_stream ()
{
  if (active_stream_.empty ())
  {
    return;
  }

  syn::IEvent::ptr rmsg;
  auto             dmsg = ::libs::iproperties::helpers::create_event< syn::UpdateStream > (rmsg);

  dmsg->action_    = ::libs::istorage_events::StreamUpdates::close;
  dmsg->direction_ = ::libs::istorage_events::StreamDirections::unknown;
  // dmsg->time_ = ;
  send_message (rmsg, syn::CallSyncs::async, syn::Calls::set);
  // dmsg          = ::libs::iproperties::helpers::cast_event<syn::UpdateStream> (rmsg);
  //  active_stream_ = dmsg->stream_id_;
  //  U3_CHECK (!active_stream_.empty (), "receivedd null stread id for " <<);
  active_stream_.reset ();
}


void
Impl2Storage::send_message (
  syn::IEvent::ptr&     rmsg,
  const syn::CallSyncs& sync,
  const syn::Calls&     req)
{
  auto*                    ilink     = ::libs::iproperties::helpers::get_prop_links ();
  ::libs::link::ILink::ptr data2appl = ilink->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();
  U3_ASSERT (data2appl);
  if (!data2appl)
  {
    U3_LOG_DATA_WRN ("skip send msg to storage");
    return;
  }

  data2appl->send_msg (rmsg, sync, req);
}
}   // namespace dlls::terminals::video_sender::impl2storage
