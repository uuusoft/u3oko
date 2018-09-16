#pragma once
/**
\file       impl2http.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.08.2018
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/

namespace dlls { namespace terminals { namespace video_sender { namespace impl2http {
/**
\brief  Реализация передачи данных в http модуль.
*/
class Impl2Http final : public IImplSender
{
  public:
  Impl2Http ()
  {}

  virtual ~Impl2Http ()
  {}


  private:
  //  IImplSender overrides
  virtual void
  send_int (const InfoFilter& _finfo, const TransformInfo& _info, const Buff2ModuleInfo::craw_ptr _minfo, IVideoBuff::raw_ptr _send_buff) override
  {
    UASSERT (_minfo);
    ILink::ptr  _helper = UUU_PROP_CAST (::libs::properties::vers::links::ILinksProperty::raw_ptr) (::libs::iproperties::helpers::get_prop_links ())->get_links_lockfree ().data2appl_.lock ();
    IEvent::ptr _rmsg;
    auto        _dmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ihttp_events::events::WrapperHttpEvent> (_rmsg);
    IEvent::ptr _irmsg;
    auto        _idmsg = ::libs::iproperties::helpers::get_and_cast_event<::libs::ievents::runtime::mem::ZipDataEvent> (_irmsg);

    _idmsg->update_zip (_send_buff);
    _idmsg->set_number (_finfo.count_frames_);
    _idmsg->set_id (id_zip_buff2http);
    _dmsg->set_msg (_irmsg);

    _helper->send_msg (_rmsg);
    return;
  }
};

}}}}      // namespace dlls::terminals::video_sender::impl2http
