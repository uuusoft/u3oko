/**
\file       video-sender-filter-dll.cpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_video_sender_dll
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "video-sender-includes_int.hpp"
#include "video-sender-info-filter.hpp"
#include "video-sender-filter-dll.hpp"

namespace dlls::terminals::video_sender
{
Filter::Filter ()
{
  senders_[::libs::ilink::consts::id_http]    = std::make_shared< impl2http::Impl2Http > ();
  senders_[::libs::ilink::consts::id_storage] = std::make_shared< impl2storage::Impl2Storage > ();
  senders_[::libs::ilink::consts::id_gui]     = std::make_shared< impl2gui::Impl2Gui > ();

  init_send_funcs ();
}


void
Filter::init_send_funcs ()
{
}


void
Filter::load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node)
{
  init_pts (&info->pts_);
  finfo_.load (node);
}


void
Filter::call_int (syn::CallInterfInfo& info)
{
  super::prepare_call (info);
  super::call_gen (info);
}


void
Filter::run_int ()
{
}


void
Filter::stop_int ()
{
  if (!finfo_.active_impl_.expired ())
  {
    finfo_.active_impl_.reset ();
  }
}


void
Filter::init_pts (syn::ConnectInfo* info)
{
  U3_ASSERT (info);
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::Points::input);
  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
}


void
Filter::process_events (syn::TransformInfo& info)
{
  if (!info.frame_events_)
  {
    return;
  }

  for (const auto& event : *info.frame_events_)
  {
    auto* devent = ::libs::iproperties::helpers::cast_event< ::libs::events_base::runtime::interf::InterfBaseIdEvent > (event);
    if (devent)
    {
      finfo_.active_impl_ = devent->get_interface ();
      U3_ASSERT (!finfo_.active_impl_.expired ());
    }
  }
}


void
Filter::default_send_func (
  syn::TransformInfo&                  info,
  const syn::Buff2ModuleInfo::craw_ptr minfo,
  const syn::id_link_type&             id)
{
  U3_ASSERT (minfo);
  auto*                   linkprops = ::libs::iproperties::helpers::get_prop_links ();
  auto                    helper    = linkprops->get_links_lockfree ()[syn::mids::mdata2appl].lock ();
  auto&                   bufs      = (**info.ibuf_);
  const auto&             indx_buf  = minfo->indx_buf_;
  syn::IVideoBuf::raw_ptr send_buf  = bufs[indx_buf];

  if (!send_buf || (*send_buf)[::utils::dbufs::MemVars::size_data] <= 0)
  {
    U3_LOG_DATA_DBG ("skip send empty buf");
    return;
  }

  auto impl = senders_.find (id);
  if (impl == senders_.end ())
  {
    U3_LOG_DATA_ERROR ("unknown type senders, skip send for" + STOLOG (id));
    return;
  }

  U3_LOG_DATA_DBG ("send frame to client" + TOLOG (minfo->indx_buf_) + STOLOG (id));
  impl->second->send (finfo_, info, minfo, send_buf);
}
}   // namespace dlls::terminals::video_sender
