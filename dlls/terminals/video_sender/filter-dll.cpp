//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       filter-dll.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "info-filter.hpp"
#include "filter-dll.hpp"

namespace dlls { namespace terminals { namespace video_sender {

Filter::Filter ()
{
  senders_[::libs::ilink::consts::id_http]    = std::make_shared<impl2http::Impl2Http> ();
  senders_[::libs::ilink::consts::id_storage] = std::make_shared<impl2storage::Impl2Storage> ();
  senders_[::libs::ilink::consts::id_gui]     = std::make_shared<impl2gui::Impl2Gui> ();
  init_send_functs ();
}


Filter::~Filter ()
{}


void
Filter::init_send_functs ()
{
  return;
}


void
Filter::load_int (FilterInfo* _info, const base_functs::xml::itn& _node)
{
  init_pts (&_info->pts_);
  finfo_.load (_node);
  return;
}


void
Filter::call_int (CallInterfInfo& _info)
{
  super::prepare_call (_info);
  super::call_gen (_info);
  return;
}


void
Filter::init_pts (ConnectInfo* info)
{
  UASSERT (info);
  info->count_ins_ = 1;
  info->ins_[0].set_info (true, ::libs::icore::impl::var1::obj::PointFilter::input);
  info->count_outs_ = 1;
  info->outs_[0].set_info (true);
  return;
}


void
Filter::process_events (TransformInfo& _info)
{
  if (!_info.pframe_events_)
    {
      return;
    }

  XULOG_TRACE ("Filter::process_events: events_->size=" << _info.pframe_events_->size ());
  for (const auto& _event : *_info.pframe_events_)
    {
      const auto _devent = ::libs::iproperties::helpers::cast_event<::libs::ievents::runtime::interf::InterfBaseIdEvent> (_event);
      if (_devent)
        {
          XULOG_TRACE ("Filter::process_events: update active interface");
          finfo_.active_impl_ = _devent->get_interface ();
          UASSERT (!finfo_.active_impl_.expired ());
        }
    }
  return;
}


void
Filter::default_send_funct (TransformInfo& _info, const Buff2ModuleInfo::craw_ptr _minfo, const id_link_module_type& _id)
{
  UASSERT (_minfo);
  ILink::ptr          _helper    = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();
  auto&               _buffs     = (**_info.ibuff_);
  const auto&         _indx_buff = _minfo->indx_buff_;
  IVideoBuff::raw_ptr _send_buff = _buffs[_indx_buff];

  if (!_send_buff || (*_send_buff)[::utils::dbuffs::TypeMemVar::size_data] <= 0)
    {
      XULOG_TRACE ("skip send, " << _indx_buff);
      return;
    }

  auto _impl = senders_.find (_id);
  if (_impl == senders_.end ())
    {
      XULOG_WARNING ("unknown type senders, skip send for" << _id);
      return;
    }

  _impl->second->send (finfo_, _info, _minfo, _send_buff);
  return;
}

}}}      // namespace dlls::terminals::video_sender
