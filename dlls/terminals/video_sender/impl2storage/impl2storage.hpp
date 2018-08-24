#pragma once
/**
\file       impl2storage.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.08.2018
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/

namespace dlls { namespace terminals { namespace video_sender { namespace impl2storage {
/**
  \brief  –елизаци€ передачи данных в модуль-хранилище.
  */
class Impl2Storage final : public IImplSender
{
  public:
  Impl2Storage ();

  virtual ~Impl2Storage ();


  private:
  //  IImplSender overrides
  virtual void send_int (const InfoFilter& _finfo, const TransformInfo& _info, const Buff2ModuleInfo::craw_ptr _minfo, IVideoBuff::raw_ptr _send_buff) override;

  void open_stream ();

  void close_stream ();

  void send_message (IEvent::ptr& _rmsg, const TypeSyncCall& _sync, const TypeRequestCall& _req);

  stream_id_type active_stream_;      //< “екущий открытый поток на запись в хранилище.
};

}}}}      // namespace dlls::terminals::video_sender::impl2storage
