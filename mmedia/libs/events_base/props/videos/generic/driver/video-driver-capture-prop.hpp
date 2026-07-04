#pragma once
/**
\file       video-driver-capture-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::driver::syn
{
namespace minor = ::libs::utility::uids::minor;
}

namespace libs::events_base::props::videos::generic::driver
{
/// POD Свойства для устройства захвата видео
struct VideoDriverCapturePropInfo {
  using Src2DstEqs = ::libs::events_base::props::videos::generic::convert::Src2DstEqs;

  VideoDriverCapturePropInfo () = default;

  Src2DstEqs         type_resize_         = Src2DstEqs::src_int_dst;               //< Типа масштабирования кадра
  CatchRgns          type_capture_        = CatchRgns::cursor_area;                //< Тип захвата
  std::uint32_t      fps_                 = 0;                                     //< Количество кадров в секунду, снимаемых с устройства
  std::uint32_t      width_               = 1920;                                  //< Ширина кадра
  std::uint32_t      height_              = 1080;                                  //< Высота кадра
  std::uint32_t      count_preload_frame_ = 1;                                     //< Количество буферов в реализации захвата данных с устройства
  std::uint32_t      mem_frames_cycle_    = 0;                                     //< REFACT не используется
  std::uint32_t      ms_delay_load_       = 1000;                                  //< Опциональная задержка перед загрузкой кадра в мс
  bool               mirror_x_            = false;                                 //< Отразить по горизонтали изображение
  bool               mirror_y_            = false;                                 //< Отразить по вертикали изображение
  std::int32_t       rotation_            = 0;                                     //< Вращение изображения, в градусах
  Focus              focus_               = Focus::auto_generic;                   //< Фокус камеры
  syn::minor::id_val px_format_           = syn::minor::id_val::device_specific;   //< Формат пикселей
};

/// Свойства для устройства захвата видео
class VideoDriverCaptureProp final : virtual public events_base::Event
{
  friend class boost::serialization::access;

  protected:
  struct Acessor {
    explicit Acessor (std::int32_t) {};
  };

  public:
  //  ext types
  U3_ADD_POINTERS_TO_SELF (VideoDriverCaptureProp)
  U3_ADD_MAKE_SHARED_THIS (VideoDriverCaptureProp)
  U3_ADD_DELETE_MOVE_COPY (VideoDriverCaptureProp)

  explicit VideoDriverCaptureProp (const Acessor& = Acessor (0));
  virtual ~VideoDriverCaptureProp () = default;

  static constexpr auto
  gen_get_mid () -> const IEvent::hid_type&
  {
    static constexpr const char* chret = "libs/events_base/props/videos/generic/driver/video-driver-capture-prop";
    static constexpr const IEvent::hid_type ret { chret };
    return ret;
  }

  VideoDriverCapturePropInfo capi_;

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
}   // namespace libs::events_base::props::videos::generic::driver

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp);
