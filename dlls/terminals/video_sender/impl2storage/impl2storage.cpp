/**
\file       impl2storage.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.08.2018
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "syn.hpp"
#include "impl2storage.hpp"

namespace dlls { namespace terminals { namespace video_sender { namespace impl2storage {

Impl2Storage::Impl2Storage ()
{}


Impl2Storage::~Impl2Storage ()
{
  close_stream ();
}


void
Impl2Storage::send_int (const InfoFilter& _finfo, const TransformInfo& _info, const Buff2ModuleInfo::craw_ptr _minfo, IVideoBuff::raw_ptr _send_buff)
{
  UASSERT (_minfo);
  if (active_stream_.empty ())
    {
      open_stream ();
    }

  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::istorage_events::events::WriteData> (_rmsg);
  IEvent::ptr _irmsg;
  auto        _idmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::mem::ZipDataEvent> (_irmsg);

  _dmsg->set_msg (_irmsg);
  _dmsg->set_stream_id (active_stream_);
  _idmsg->set_id (id_zip_buff2storage);
  _idmsg->set_number (_finfo.count_frames_);
  _idmsg->update_zip (_send_buff);
  send_message (_rmsg, SyncCallType::async, RequestCallType::set);
  return;
}


void
Impl2Storage::open_stream ()
{
  XULOG_TRACE ("Impl2Storage::open_stream: beg");
  if (!active_stream_.empty ())
    {
      XULOG_TRACE ("Impl2Storage::open_stream: skip");
      return;
    }

  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::istorage_events::events::UpdateStream> (_rmsg);

  _dmsg->obj_id_.val_ = "unimplemented add name source";
  _dmsg->action_      = TypeUpdateStream::open;
  _dmsg->direction_   = TypeDirectionStream::unknown;
  _dmsg->operation_   = TypeActionStream::write;

  send_message (_rmsg, SyncCallType::sync, RequestCallType::request);
  _dmsg          = ::libs::iproperties::helpers::cast_event<::libs::istorage_events::events::UpdateStream> (_rmsg);
  active_stream_ = _dmsg->stream_id_;
  CHECK_STATE (!active_stream_.empty (), "received null stread_id for write data");
  XULOG_TRACE ("Impl2Storage::open_stream: end, id=" << active_stream_.name ());
  return;
}


void
Impl2Storage::close_stream ()
{
  XULOG_TRACE ("Impl2Storage::close_stream: beg");
  if (active_stream_.empty ())
    {
      XULOG_TRACE ("Impl2Storage::close_stream: skip");
      return;
    }

  IEvent::ptr _rmsg;
  auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::istorage_events::events::UpdateStream> (_rmsg);

  _dmsg->action_    = TypeUpdateStream::close;
  _dmsg->direction_ = TypeDirectionStream::unknown;
  //_dmsg->time_ = ;

  send_message (_rmsg, SyncCallType::async, RequestCallType::set);
  //_dmsg          = ::libs::iproperties::helpers::cast_event<::libs::istorage_events::events::UpdateStream> (_rmsg);
  //active_stream_ = _dmsg->stream_id_;
  //CHECK_STATE (!active_stream_.empty (), "receivedd null stread id for " <<);
  active_stream_.reset ();
  XULOG_TRACE ("Impl2Storage::close_stream: end");
  return;
}


void
Impl2Storage::send_message (IEvent::ptr& _rmsg, const SyncCallType& _sync, const RequestCallType& _req)
{
  ILink::ptr _helper = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();
  UASSERT (_helper);
  XULOG_TRACE ("send buff to id_storage, " << _rmsg->get_mid ());
  _helper->send_msg (_rmsg, _sync, _req);
  return;
}

}}}}      // namespace dlls::terminals::video_sender::impl2storage
