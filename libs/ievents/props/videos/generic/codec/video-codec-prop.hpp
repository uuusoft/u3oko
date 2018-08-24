#pragma once
/**
\file       video-codec-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      Объявление события со свойствами кодирования.
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace codec {
//  syn
using ::libs::events::buff::BuffEventInfo;
/**
  \brief  Событие со свойствами кодеков в системе.
  */
class VideoCodecProp : public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor
  {
    explicit Acessor (int){};
  };

  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoCodecProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoCodecProp);
  UUU_DISABLE_ACOPY_TYPE (VideoCodecProp);

  explicit VideoCodecProp (const Acessor& = Acessor (0));

  virtual ~VideoCodecProp ();

  static const IEvent::text_id_type&
  gen_get_type_text_id ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/codec/video-codec-prop";
    return _ret;
  }

  void correct ();

  void reset ();

  std::string           name_idll_;                    //< Имя файла с реализацией кодека.
  BuffEventInfo         buffs_;                        //< Буфер источника/назначения. Опционален.
  int                   fps_coder_;                    //< Количество кадров (декодирумых/кодируемых) в секунду. Если значение <= 0 контроль частоты не производится.
  unsigned long long    dump_counter_frame_;           //< Количество кадров, через которое будет произведен сброс времени работы в лог. 0 - логирование отключено (по умолчанию).
  VideoCodecFlatProp    plane_;                        //< Свойства компрессии, которые будут вложены в каждый сжатый кадр системы.
  bool                  dump_compressed_to_file_;      //< Флаг, для отладки добавляем возможность сбрасывать сжатые данные в файл. Каждый блок попадает в свой файл с автоматически сгенерированным уникальным именем.
  std::string           hint_impl_;                    //< Опциональная подсказка реализации. Например "auto", "hard", "soft", etc. Определяет возможность использования аппаратными реализациями.
  OverrideCodecDataType write_codec_strategy_;         //< Стратегия записи данных в буфер для кодека.
  bool                  decode_mirror_y_;              //< Флаг, отразить изображение по вертикали при декодировании.
  bool                  code_mirror_y_;                //< Флаг, отразить изображение по вертикали при кодировании.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);
  //  ievents::Event overrides
  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::TypeCloneEvent& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::codec

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::codec::VideoCodecProp);
