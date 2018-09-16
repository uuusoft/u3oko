#pragma once
/**
\file       impl2gui.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.08.2018
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      empty brief
*/

namespace dlls { namespace terminals { namespace video_sender { namespace impl2gui {
/**
\brief  Реализация передачи данных в gui модуль.
*/
class Impl2Gui final : public IImplSender
{
  public:
  Impl2Gui ();

  virtual ~Impl2Gui ();


  private:
  //  IImplSender overrides
  virtual void send_int (const InfoFilter& _finfo, const TransformInfo& _info, const Buff2ModuleInfo::craw_ptr _minfo, IVideoBuff::raw_ptr _send_buff) override;

  bool fill_frame (const TransformInfo& _info, void* _pmem);

  void send_frame (const InfoFilter& _finfo, const TransformInfo& _info, ILink::ptr _helper);

  bool is_empty_frame (const void* _pmem) const;

  ::libs::link::mem::IBlockMem last_hmem_;          //< Последний использованный блок памяти для хранения несжатого кадра.
  ::libs::buffs::Buffs::ptr    fast_buff2gui_;      //< Буфер с данными, разделяемый с графическим интерфейсом в режиме одного процесса.
};

}}}}      // namespace dlls::terminals::video_sender::impl2gui
