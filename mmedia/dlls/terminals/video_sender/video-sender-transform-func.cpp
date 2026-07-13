/**
\file       video-sender-transform-func.cpp
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
void
Filter::transform_int (syn::TransformInfo& info)
{
  prepare_transform (info);
  process_events (info);

  if (::libs::events::PropertyUsings::disabled == finfo_.ef_props_.front ()->get_using_state ())
  {
    return;
  }

  auto impl = finfo_.active_impl_.lock ();
  if (!impl)
  {
    return;
  }

  ++finfo_.count_frames_;
  if (finfo_.rprops_->is_notify ())
  {
    send_info_msg (info);
  }

  auto* linkprops = ::libs::iproperties::helpers::get_prop_links ();
  auto  helper    = linkprops->get_links_lockfree ()[syn::mids::mdata2appl].lock ();
  if (!helper)
  {
    U3_LOG_DATA_ERROR ("empty sender helper, skip send msg");
    return;
  }

  U3_CHECK (helper, "null helper");
  U3_CHECK (info.ibuf_, "null ptr buf");
  U3_CHECK (*info.ibuf_, "null buf");

  auto& bufs = (*info.ibuf_);
  if (bufs->get_flag (::libs::bufs::BufsFlags::empty))
  {
    return;
  }

  bufs->enum_bufs (
    [this, &impl, &info] (const ::utils::dbufs::video::consts::offs::off_buf_type& indx, const syn::IVideoBuf::cptr& buf) -> void {
      auto minfos = impl->get_module_infos (indx);

      if (minfos.empty ())
      {
        return;
      }

      for (const auto& minfo : minfos)
      {
        auto find = funcs_.find (minfo->dest_module_id_);
        if (funcs_.end () == find)
        {
          default_send_func (info, minfo, minfo->dest_module_id_);
        }
        else
        {
          find->second (info, minfo);
        }
      }
    });

  if (info.frame_events_ && !info.frame_events_->empty ())
  {
    for (auto& frame_revent : *info.frame_events_)
    {
      auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::WrapperHttpEvent > ();
      revnt->set_msg (frame_revent);
      helper->send_msg (evnt);
    }
  }
}


void
Filter::send_info_msg (syn::TransformInfo& info)
{
  auto* linkprops    = ::libs::iproperties::helpers::get_prop_links ();
  auto  idata        = linkprops->get_links_lockfree ()[syn::mids::mdata2appl].lock ();
  auto [evnt, revnt] = ::libs::iproperties::helpers::create_event< syn::FrameDone > ();
  idata->send_msg (evnt);
}
}   // namespace dlls::terminals::video_sender
