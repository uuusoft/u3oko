#pragma once
/**
\file       video-detect-prop.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::detect
{
/// Свойства детекции движения
class VideoDetectProp final : public ievents::Event
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoDetectProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoDetectProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoDetectProp)

  explicit VideoDetectProp (const Acessor& = Acessor (0));
  virtual ~VideoDetectProp () = default;

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/detect/video-detect-prop";
    return ret;
  }

  std::string   mode_               = "default";                                     //< Текстовое описание режима детектирования, для расширения свойств в будущем
  std::int32_t  bound_              = 5;                                             //< Порог, влияет на чувствительность детекции на уровне одного пикселя изображения. Обычные значения 5-50
  std::int32_t  size_core_morph_op_ = 7;                                             //< Размер ядра морфологической операции эрозии, влияет на фильтрацию шума. Обычные значения 3-11
  std::string   id_morph_op_;                                                        //< Тип морфологической операции над результатом разностию Обычные значения dilation, skip
  std::int32_t  counter_morph_op_     = 1;                                           //< Количество морфологических операций. ОБычные значения 0,1,2
  std::int32_t  min_size_spot_        = 0;                                           //< Минимальная площадь пятна детекции. 0 если не определена, по умолчанию
  std::int32_t  max_size_spot_        = 0;                                           //< Максимальная площадь пятна детекции. 0 если не определена, по умолчанию
  std::int32_t  time_after_last_move_ = 10;                                          //< Время в секундах, которое должно пройти после последнего движения, чтобы было сгенерировано событие окончания движения. Имеет смысл значения в интервале от 5 до 30 секунд
  bool          lazy_optim_           = true;                                        //< Флаг оптимизации детекции, включен по умолчанию, отключается (например) для тестирования
  std::int32_t  time_id_              = ::libs::helpers::consts::iinvalid;           //< Опицональный временной идентификатор настройки детектора, может быть привязан к временной зоне, т.к. настроеки могут меняться по времени
  std::int32_t  zone_id_              = ::libs::helpers::consts::iinvalid;           //< Опциональный идентификатор зоны детекции
  SelectorImpls hint_detector_impl_   = ::libs::ievents::SelectorImpls::automatic;   //< Опциональный идентифкатор реализации. Например "auto", "hard", "soft", etc
  /// Индексы буфера источника для детекции и буфера назначения для результат оценки
  ::libs::events::buf::EventBufsInfo bufs_ { libs::events::buf::EventBufsInfo (utils::dbufs::video::consts::offs::lit, utils::dbufs::video::consts::offs::move_detect_res) };


  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
  virtual void                        self_correct_int () override;
};
}   // namespace libs::ievents::props::videos::generic::detect

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::detect::VideoDetectProp);
