#pragma once
/**
\file       video-codec-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::codec::syn
{
using EventBufs = ::libs::events::buf::EventBufs;
}

namespace libs::events_base::props::videos::generic::codec
{
/// Событие со свойствами кодеков в системе
class VideoCodecProp : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (VideoCodecProp)
  U3_ADD_MAKE_SHARED_THIS (VideoCodecProp)
  U3_ADD_DELETE_MOVE_COPY (VideoCodecProp)

  explicit VideoCodecProp (const Acessor& = Acessor (0));
  virtual ~VideoCodecProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/props/videos/generic/codec/video-codec-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  void correct ();
  void reset ();

  // EAI-REFACT to private
  std::string        dll_name_ = "vvd_vcodec_mjpg";                                                                   //< Имя DLL с реализацией кодека
  syn::EventBufs     bufs_ { ::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::http };   //< Буфер источника/назначения. Опционален
  std::uint32_t      max_period_ic_frame_ = 0;                                                                        //< Максимальный период ICF
  std::uint32_t      fps_coder_           = 0;                                                                        //< Количество кадров (декодирумых/кодируемых) в секунду. Если значение <= 0 контроль частоты не производится
  VideoCodecFlatProp plane_;                                                                                          //< Свойства компрессии, которые будут вложены в каждый сжатый кадр системы
  Writes             write_codec_strategy_ = Writes::allways_write;                                                   //< Стратегия записи данных в буфер для кодека
  bool               decode_flip_y_        = false;                                                                   //< Флаг, отразить изображение по вертикали при декодировании
  bool               code_flip_y_          = false;                                                                   //< Флаг, отразить изображение по вертикали при кодировании
  SelectorImpls      hint_codec_impl_      = ::libs::events_base::SelectorImpls::automatic;                           //< Опциональный идентификатор реализации. Например "auto", "hard", "soft", etc
  bool               dump_result2file_     = false;                                                                   //< Флаг, для отладки добавляем возможность сбрасывать сжатые данные в файл. Каждый блок попадает в свой файл с автоматически сгенерированным уникальным именем
  std::uint64_t      dump_counter_frame_   = 0;                                                                       //< Количество кадров, через которое будет произведен сброс времени работы в лог. 0 - логирование отключено (по умолчанию)

  private:
  U3_ADD_SUPER_CLASS (::libs::events_base::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
  // IEvent overrides
  virtual auto get_mid_int () const -> const ::libs::events::IEvent::hid_type& override;
  virtual auto clone_int (const ::libs::events::Deeps&) const -> ::libs::events::IEvent::ptr override;
  virtual auto load_json_int (const ::boost::json::object&) -> void override;
  virtual auto save_json_int (::boost::json::object&) const -> void override;
  virtual auto copy_int (const IEvent::craw_ptr) -> void override;
};
}   // namespace libs::events_base::props::videos::generic::codec

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::codec::VideoCodecProp);
