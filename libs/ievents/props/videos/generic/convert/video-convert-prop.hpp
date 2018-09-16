#pragma once
/**
\file       video-convert-prop.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      Обявление структуры для группировки сохраняемых свойств фильтра-конвертора форматов цвета.
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace convert {
//  syn
using ::libs::events::buff::EventBuffsInfo;
/**
\brief  empty brief
*/
class VideoConvertProp : public ievents::Event
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
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoConvertProp);
  UUU_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoConvertProp);
  UUU_DISABLE_ACOPY_TYPE (VideoConvertProp);

  explicit VideoConvertProp (const Acessor& = Acessor (0));

  virtual ~VideoConvertProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const std::string _ret = "libs/ievents/props/videos/generic/convert/video-convert-prop";
    return _ret;
  }

  EventBuffsInfo      buff_;                      //< Индекс подготовленного буфера (разница с отфильтрованным шумом) для детекции.
  TypeSrc2Dst         rtype_;                     //< Тип вычисления размеров буфера назначения.
  TypeConvertAccuracy atype_;                     //< Тип точности конверсии.
  int                 rwidth_;                    //< Ширина источника.
  int                 rheight_;                   //< Высота источника.
  bool                duplicate_image_;           //< Флаг, требование продублировать буфера в dupl_l dupl_h dupl_s. Зачем?
  bool                strip_color_;               //< Флаг, требования отбросить цвета при преобразовании. Драматически сказывается на скорости в лучшую сторону.
  bool                debug_skip_transform_;      //< Флаг, требование пропустить конвертацию. Для отладки и тестирования последующих модулей на корректность обработки неправильных данных.
  bool                flip_y_;                    //< Флаг, требования отзеркалить изображения по вертикали во время конверсии. Ряд источников по разному трактуют положение нулевой строки.


  private:
  UUU_THIS_TYPE_HAS_SUPER_CLASS (ievents::Event);

  friend class boost::serialization::access;

  template <class Archive>
  void serialize (Archive& ar, const unsigned int /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::DeepEventCloneType& _deep) const override;
  virtual void                        load_int (const base_functs::xml::itn& _node) override;
  virtual void                        copy_int (const IEvent::craw_ptr _src) override;
};

}}}}}}      // namespace libs::ievents::props::videos::generics::convert

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generics::convert::VideoConvertProp);
