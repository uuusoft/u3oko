#pragma once
/**
\file       video-codec-prop.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::codec
{
/// Событие со свойствами кодеков в системе
class VideoCodecProp : public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoCodecProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoCodecProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoCodecProp)

  explicit VideoCodecProp (const Acessor& = Acessor (0));
  virtual ~VideoCodecProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/codec/video-codec-prop";
    return ret;
  }

  void correct ();
  void reset ();

  // EAI-REFACT to private
  std::string                        dll_name_;               //< Имя DLL с реализацией кодека
  ::libs::events::buf::EventBufsInfo bufs_;                   //< Буфер источника/назначения. Опционален
  std::uint32_t                      max_period_ic_frame_;    //< Максимальный период ICF
  std::uint32_t                      fps_coder_;              //< Количество кадров (декодирумых/кодируемых) в секунду. Если значение <= 0 контроль частоты не производится
  VideoCodecFlatProp                 plane_;                  //< Свойства компрессии, которые будут вложены в каждый сжатый кадр системы
  Writes                             write_codec_strategy_;   //< Стратегия записи данных в буфер для кодека
  bool                               decode_flip_y_;          //< Флаг, отразить изображение по вертикали при декодировании
  bool                               code_flip_y_;            //< Флаг, отразить изображение по вертикали при кодировании
  ::libs::ievents::SelectorImpls     hint_codec_impl_;        //< Опциональный идентификатор реализации. Например "auto", "hard", "soft", etc
  bool                               dump_result2file_;       //< Флаг, для отладки добавляем возможность сбрасывать сжатые данные в файл. Каждый блок попадает в свой файл с автоматически сгенерированным уникальным именем
  std::uint64_t                      dump_counter_frame_;     //< Количество кадров, через которое будет произведен сброс времени работы в лог. 0 - логирование отключено (по умолчанию)

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::props::videos::generic::codec

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::codec::VideoCodecProp);
