#pragma once
/**
\file       video-convert-prop.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
\brief      Обявление структуры для группировки сохраняемых свойств фильтра-конвертора форматов цвета
*/

namespace libs::ievents::props::videos::generic::convert
{
class VideoConvertProp final : public ievents::Event
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
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoConvertProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoConvertProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoConvertProp)

  explicit VideoConvertProp (const Acessor& = Acessor (0));
  virtual ~VideoConvertProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/convert/video-convert-prop";
    return ret;
  }

  ::libs::events::buf::EventBufsInfo buf_;                    //< Индекс подготовленного буфера (разница с отфильтрованным шумом) для детекции
  Src2DstEqs                         rtype_;                  //< Тип вычисления размеров буфера назначения
  Accuracys                          atype_;                  //< Тип точности конверсии
  std::int32_t                       rwidth_;                 //< Ширина источника
  std::int32_t                       rheight_;                //< Высота источника
  bool                               duplicate_image_;        //< Флаг, требование продублировать буфера в dupl_l dupl_h dupl_s Зачем?
  bool                               strip_color_;            //< Флаг, требования отбросить цвета при преобразовании. Драматически сказывается на скорости в лучшую сторону
  bool                               debug_skip_transform_;   //< Флаг, требование пропустить конвертацию. Для отладки и тестирования последующих модулей на корректность обработки неправильных данных
  bool                               flip_y_;                 //< Флаг, требования отзеркалить изображения по вертикали во время конверсии. Ряд источников по разному трактуют положение нулевой строки

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::ievents::Event)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  virtual ::libs::events::IEvent::ptr clone_int (const ::libs::events::Deeps& deep) const override;
  virtual void                        load_json_int (const ::boost::json::object& obj) override;
  virtual void                        save_json_int (::boost::json::object& obj) const override;
  virtual void                        copy_int (const IEvent::craw_ptr src) override;
};
}   // namespace libs::ievents::props::videos::generic::convert

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::convert::VideoConvertProp);
