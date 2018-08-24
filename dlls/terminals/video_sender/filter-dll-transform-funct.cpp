//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       transform_funct.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace terminals { namespace video_sender {

void
Filter::transform_int (TransformInfo& _info)
{
  XULOG_TRACE ("Filter::transform_int: beg");
  prepare_transform (_info);
  process_events (_info);

  if (::libs::events::UsingStateEvent::disabled == finfo_.props_->get_using_state ())
    {
      XULOG_TRACE ("Filter::transform_int: skip");
      return;
    }

  auto _impl = finfo_.active_impl_.lock ();
  if (!_impl)
    {
      return;
    }

  ++finfo_.count_frames_;
  if (finfo_.rprops_->is_notify ())
    {
      send_info_msg (_info);
    }

  XULOG_TRACE ("Filter::transform::beg send: " << to_str (finfo_.count_frames_));
  ILink::ptr _helper = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();
  CHECK_STATE (_helper, "failed, null helper");
  CHECK_STATE (_info.ibuff_, "failed, null ptr buff");
  CHECK_STATE (*_info.ibuff_, "failed, null buff");

  auto& _buffs = (*_info.ibuff_);
  if (_buffs->get_flag (::libs::buffs::TypeBuffsFlags::empty))
    {
      XULOG_TRACE ("Filter::transform_int: skip");
      return;
    }

  _buffs->enum_buffs ([this, &_impl, &_info](const off_buff_type& _indx, const IVideoBuff::cptr& _buff) {
    auto _minfos = _impl->get_module_infos (_indx);
    if (_minfos.empty ())
      {
        return;
      }

    XULOG_TRACE ("Filter::transform::beg send: check " << _indx);
    for (const auto& _minfo : _minfos)
      {
        XULOG_TRACE ("Filter::transform::beg send: process " << _minfo->module_);
        auto _find = functs_.find (_minfo->module_);
        if (functs_.end () == _find)
          {
            default_send_funct (_info, _minfo, _minfo->module_);
          }
        else
          {
            _find->second (_info, _minfo);
          }
      }
    return;
  });

  if (_info.pframe_events_ && !_info.pframe_events_->empty ())
    {
      for (const auto& event : *_info.pframe_events_)
        {
          IEvent::ptr _rmsg;
          auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ihttp_events::events::WrapperHttpEvent> (_rmsg);
          _helper->send_msg (_rmsg);
        }
    }
  XULOG_TRACE ("Filter::transform_int: end");
  return;
}


void
Filter::send_info_msg (TransformInfo& _info)
{
  auto                        _idata = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();
  ::libs::events::IEvent::ptr _rmsg;
  auto                        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::video::FrameDone> (_rmsg);
  _idata->send_msg (_rmsg);
  return;
}

}}}      // namespace dlls::terminals::video_sender
