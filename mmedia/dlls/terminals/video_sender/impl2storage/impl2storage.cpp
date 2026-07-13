/**
\file       impl2storage.cpp
\author     Erashov Anton erashov2026@proton.me
\date       14.08.2018
\project    u3_video_sender_dll
*/
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

  auto [evnt, revnt]         = ::libs::iproperties::helpers::create_event< syn::WriteData > ();
  auto [zip_evnt, zip_revnt] = ::libs::iproperties::helpers::create_event< syn::ZipDataEvent > ();

  revnt->set_msg (zip_evnt);
  revnt->set_stream_id (active_stream_);
  zip_revnt->set_id (::dlls::terminals::video_sender::consts::id_zip_buf2storage);
  zip_revnt->set_number (finfo.count_frames_);
  zip_revnt->update_zip (send_buf);

  send_message (evnt, syn::CallSyncs::async, syn::Calls::set);
}


void
Impl2Storage::open_stream ()
{
  if (!active_stream_.empty ())
  {
    return;
  }
#if 0
  auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::UpdateStream > ();

  revnt->obj_id_.val_ = "unimplemented add name source";
  revnt->action_      = ::libs::events_storage::StreamUpdates::open;
  revnt->direction_   = ::libs::events_storage::StreamDirections::unknown;
  revnt->operation_   = ::libs::events_storage::StreamActions::write;

  send_message (evnt);

  auto us_evnt   = ::libs::iproperties::helpers::cast_event< syn::UpdateStream > (evnt);
  active_stream_ = us_evnt->stream_id_;
  U3_CHECK (!active_stream_.empty (), "received null stread_id for write data");
#endif
}


void
Impl2Storage::close_stream ()
{
  if (active_stream_.empty ())
  {
    return;
  }

  auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::UpdateStream > ();

  revnt->action_    = ::libs::events_storage::StreamUpdates::close;
  revnt->direction_ = ::libs::events_storage::StreamDirections::unknown;
  send_message (evnt);
  active_stream_.reset ();
}


void
Impl2Storage::send_message (
  syn::IEvent::ptr&     rmsg,
  const syn::CallSyncs& sync,
  const syn::Calls&     req)
{
  auto* ilink     = ::libs::iproperties::helpers::get_prop_links ();
  auto  data2appl = ilink->get_links_lockfree ()[syn::mids::mdata2appl].lock ();
  U3_ASSERT (data2appl);
  if (!data2appl)
  {
    U3_LOG_DATA_WRN ("skip send msg to storage");
    return;
  }

  data2appl->send_msg (rmsg, { .sync_ = sync, .req_ = req });
}
}   // namespace dlls::terminals::video_sender::impl2storage
