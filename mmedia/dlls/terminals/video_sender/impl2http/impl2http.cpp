/**
\file       impl2http.cpp
\author     Erashov Anton erashov2026@proton.me
\date       06.03.2022
\project    u3_video_sender_dll
*/
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
  auto  data2appl = ilink->get_links_lockfree ()[syn::mids::mdata2appl].lock ();

  if (!data2appl)
  {
    U3_LOG_DATA_WRN ("empty data2appl, skip send msg to http" + VTOLOG (finfo.count_frames_) + VTOLOG (send_buf->get_dim_var (utils::dbufs::video::Dims::height)));
    return;
  }

  auto [evnt, revnt]       = ::libs::iproperties::helpers::create_event< syn::WrapperHttpEvent > ();
  auto [zd_evnt, zd_revnt] = ::libs::iproperties::helpers::create_event< syn::ZipDataEvent > ();

  zd_revnt->update_zip (send_buf);
  zd_revnt->set_number (finfo.count_frames_);

  auto              impl  = finfo.active_impl_.lock ();
  const std::string srcid = impl ? impl->get_source_name () : "";
  zd_revnt->set_id (srcid);
  // zd_revnt->set_id (appl::consts::id_zip_buf2http + srcid);

  revnt->set_msg (zd_evnt);
  data2appl->send_msg (evnt);
}
}   // namespace dlls::terminals::video_sender::impl2http
