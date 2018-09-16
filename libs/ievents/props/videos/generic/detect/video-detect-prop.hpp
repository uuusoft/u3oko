#pragma once
/**
\file       video-detect-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace detect {
//  syn
using ::libs::events::buff::EventBuffsInfo;
/**
\brief  Свойства детекции движения.
*/
class VideoDetectProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoDetectProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoDetectProp);
  UUU_DISABLE_ACOPY_TYPE (VideoDetectProp);

  explicit VideoDetectProp (const Acessor& = Acessor (0));

  virtual ~VideoDetectProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/detect/video-detect-prop";
    return _ret;
  }

  std::string    mode_;                    //< Текстовое описание режима детектирования, для расширения свойств в будущем.
  int            bound_;                   //< Порог, влияет на чувствительность детекции на уровне одного пикселя изображения. Обычные значения 5-50.
  int            size_core_morph_op_;      //< Размер ядра морфологической операции эрозии, влияет на фильтрацию шума. Обычные значения 3-11.
  std::string    id_morph_op_;             //< Тип морфологической операции над результатом разностию Обычные значения dilatation, skip.
  int            counter_morph_op_;        //< Количество морфологических операций. ОБычные значения 0,1,2.
  int            min_size_spot_;           //< Минимальная площадь пятна детекции. 0 если не определена, по умолчанию.
  int            max_size_spot_;           //< Максимальная площадь пятна детекции. 0 если не определена, по умолчанию.
  EventBuffsInfo buffs_;                   //< Индексы буфера источника для детекции и буфера назначения для результат оценки.
  int            time_after_last_move_;    //< Время в секундах, которое должно пройти после последнего движения, чтобы было сгенерировано событие окончания движения. Имеет смысл значения в интервале от 5 до 30 секунд.
  bool           lazy_optim_;              //< Флаг оптимизации детекции, включен по умолчанию, отключается (например) для тестирования.
  int            time_id_;                 //< Опицональный временной идентификатор настройки детектора, может быть привязан к временной зоне, т.к. настроеки могут меняться по времени.
  int            zone_id_;                 //< Опциональный идентификатор зоны детекции.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::detect

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::detect::VideoDetectProp);
