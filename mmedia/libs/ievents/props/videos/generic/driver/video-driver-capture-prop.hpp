#pragma once
/**
\file       video-driver-capture-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::driver
{
/// POD Свойства для устройства захвата видео
struct VideoDriverCapturePropInfo {
  using Src2DstEqs = ::libs::ievents::props::videos::generic::convert::Src2DstEqs;

  VideoDriverCapturePropInfo () = default;

  Src2DstEqs                           type_resize_         = Src2DstEqs::src_int_dst;                                 //< Типа масштабирования кадра
  CatchRgns                            type_capture_        = CatchRgns::cursor_area;                                  //< Тип захвата
  std::uint32_t                        fps_                 = 0;                                                       //< Количество кадров в секунду, снимаемых с устройства
  std::uint32_t                        width_               = 1920;                                                    //< Ширина кадра
  std::uint32_t                        height_              = 1080;                                                    //< Высота кадра
  std::uint32_t                        count_preload_frame_ = 1;                                                       //< Количество буферов в реализации захвата данных с устройства
  std::uint32_t                        mem_frames_cycle_    = 0;                                                       //< REFACT не используется
  std::uint32_t                        ms_delay_load_       = 1000;                                                    //< Опциональная задержка перед загрузкой кадра в мс
  bool                                 mirror_x_            = false;                                                   //< Отразить по горизонтали изображение
  bool                                 mirror_y_            = false;                                                   //< Отразить по вертикали изображение
  std::int32_t                         rotation_            = 0;                                                       //< Вращение изображения, в градусах
  Focus                                focus_               = Focus::auto_generic;                                     //< Фокус камеры
  ::libs::helpers::uids::minor::id_val px_format_           = ::libs::helpers::uids::minor::id_val::device_specific;   //< Формат пикселей
};

/// Свойства для устройства захвата видео
class VideoDriverCaptureProp final : public ievents::Event
{
  friend class boost::serialization::access;
  friend ::dlls::devents::impl::EventsImpl;
  friend struct RegisterHelper;

  protected:
  struct Acessor {
    explicit Acessor (std::int32_t) {};
  };

  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoDriverCaptureProp)
  U3_HELPER_ADD_MAKE_SHARED_FUNCT2THIS_TYPE (VideoDriverCaptureProp)
  U3_HELPER_DISABLE_ACOPY_TYPE (VideoDriverCaptureProp)

  explicit VideoDriverCaptureProp (const Acessor& = Acessor (0));
  virtual ~VideoDriverCaptureProp ();

  static const IEvent::hid_type&
  gen_get_mid ()
  {
    static const IEvent::hid_type ret = "libs/ievents/props/videos/generic/driver/video-driver-capture-prop";
    return ret;
  }

  VideoDriverCapturePropInfo capi_;

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
}   // namespace libs::ievents::props::videos::generic::driver

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp);
