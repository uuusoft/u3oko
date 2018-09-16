#pragma once
/**
\file       iimpl-sender.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.08.2018
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/

namespace dlls { namespace terminals { namespace video_sender {
/**
\brief  Интерфейс для реализаций передачи данных в конкретные модули (http/storage/etc).
*/
class IImplSender
{
  public:
  // ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (IImplSender);

  virtual ~IImplSender ()
  {}

  void
  send (const InfoFilter& _finfo, const TransformInfo& _info, const Buff2ModuleInfo::craw_ptr _minfo, IVideoBuff::raw_ptr _send_buff)
  {
    return send_int (_finfo, _info, _minfo, _send_buff);
  }


  protected:
  IImplSender ()
  {}


  private:
  //  IImplSender interface
  virtual void send_int (const InfoFilter&, const TransformInfo&, const Buff2ModuleInfo::craw_ptr, IVideoBuff::raw_ptr) = 0;
};

}}}      // namespace dlls::terminals::video_sender
