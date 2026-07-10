#pragma once
/**
\file       video-convert-prop.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
\brief      Обявление структуры для группировки сохраняемых свойств фильтра-конвертора форматов цвета
*/

namespace libs::events_base::props::videos::generic::convert::syn
{
using EventBufs = ::libs::events::buf::EventBufs;
}

namespace libs::events_base::props::videos::generic::convert
{
class VideoConvertProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (int) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (VideoConvertProp)
  U3_ADD_MAKE_SHARED_THIS (VideoConvertProp)
  U3_ADD_DELETE_MOVE_COPY (VideoConvertProp)

  explicit VideoConvertProp (const Acessor& = Acessor (0));
  virtual ~VideoConvertProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char*            chret = "libs/events_base/props/videos/generic/convert/video-convert-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  syn::EventBufs buf_ { ::utils::dbufs::video::consts::offs::raw, ::utils::dbufs::video::consts::offs::invalid };   //< Индекс подготовленного буфера (разница с отфильтрованным шумом) для детекции
  Src2DstEqs     rtype_                = Src2DstEqs::src_int_dst;                                                   //< Тип вычисления размеров буфера назначения
  Accuracys      atype_                = Accuracys::fast;                                                           //< Тип точности конверсии
  std::int32_t   rwidth_               = 640;                                                                       //< Ширина источника
  std::int32_t   rheight_              = 480;                                                                       //< Высота источника
  bool           duplicate_image_      = false;                                                                     //< Флаг, требование продублировать буфера в dupl_l dupl_h dupl_s Зачем?
  bool           strip_color_          = false;                                                                     //< Флаг, требования отбросить цвета при преобразовании. Драматически сказывается на скорости в лучшую сторону
  bool           debug_skip_transform_ = false;                                                                     //< Флаг, требование пропустить конвертацию. Для отладки и тестирования последующих модулей на корректность обработки неправильных данных
  bool           flip_y_               = true;                                                                      //< Флаг, требования отзеркалить изображения по вертикали во время конверсии. Ряд источников по разному трактуют положение нулевой строки

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
}   // namespace libs::events_base::props::videos::generic::convert

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::convert::VideoConvertProp);
