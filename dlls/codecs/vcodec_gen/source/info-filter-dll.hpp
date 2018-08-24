#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace vcodec_gen {
/**
  \brief  empty brief
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  public:
  //  ext types
  using props_type   = VideoCodecProp;
  using icodec_type  = std::array<VideoCodecProp, 4>;
  using icodecs_type = std::vector<icodec_type>;

  InfoFilter ();

  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  void init ();

  ::libs::events::IEvent::ptr      props_;               //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr              rprops_;              //< Настроенный указатель на свойства (для удобства).
  CodecImplInfo                    file_info_;           //< Информация из файла с кодеком.
  codec_gen::CodecGeneric::raw_ptr rcodec_;              //< Указатель на кодек, полученный из библиотеки.
  unsigned long long               counter_frames_;      //< Счетчик кадров.
  ICodecImage::weak_ptr            active_impl_;         //< Выбранная на данный момент реализация кодека. Может например прийти вместе с сообщением ::libs::ievents::runtime::interf::InterfCodecImageEvent
  FpsController                    fps_;                 //< Поле для контроля fps.


  protected:
  //  BaseInfoFilter overrides
  virtual void sync_int (bool _force) override;
};

}}}      // namespace dlls::codecs::vcodec_gen
