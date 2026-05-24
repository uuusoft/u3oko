/**
\file       video-sender-transform-funct.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_video_sender_dll
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
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

  ::libs::link::ILink::ptr helper = U3_CAST_PROP (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();
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
    [this, &impl, &info] (const ::utils::dbufs::video::consts::offs::off_buf_type& indx, const syn::IVideoBuf::cptr& buf) {
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
          default_send_funct (info, minfo, minfo->dest_module_id_);
        }
        else
        {
          find->second (info, minfo);
        }
      }
      return;
    });

  if (info.frame_events_ && !info.frame_events_->empty ())
  {
    for (auto& event : *info.frame_events_)
    {
      syn::IEvent::ptr rmsg;
      auto             dmsg = ::libs::helpers::check::ptr (::libs::iproperties::helpers::create_event< syn::WrapperHttpEvent > (rmsg));
      dmsg->set_msg (event);
      helper->send_msg (rmsg, syn::CallSyncs::async, syn::Calls::set);
    }
  }
}


void
Filter::send_info_msg (syn::TransformInfo& info)
{
  auto             idata = U3_CAST_PROP (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().get (libs::properties::vers::links::mids::mdata2appl).lock ();
  syn::IEvent::ptr rmsg;

  U3_CHECK (::libs::iproperties::helpers::create_event< syn::FrameDone > (rmsg), "syn::FrameDone");
  idata->send_msg (rmsg, syn::CallSyncs::async, syn::Calls::set);
}
}   // namespace dlls::terminals::video_sender
