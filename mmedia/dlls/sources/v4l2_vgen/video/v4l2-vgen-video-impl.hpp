#pragma once
/**
\file       v4l2-vgen-video-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/
#if 0
namespace dlls::sources::v4l2_vgen::video::consts
{
const std::int32_t max_bitrate_mjpeg        = 25000000;   // 25Mbits/s
const std::int32_t max_bitrate_x264_level4  = 25000000;   // 25Mbits/s
const std::int32_t max_bitrate_x264_level42 = 62500000;   // 62.5Mbits/s
}   // namespace dlls::sources::v4l2_vgen::video::consts


namespace dlls::sources::v4l2_vgen::video
{
/**
\brief  Реализация унифицированного захвата данных из системно зависимых устройств.
*/
class VideoImpl final
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (VideoImpl)

  explicit VideoImpl (DriverState* device_state);
  ~VideoImpl ();

  bool                  init_device (const ::dlls::sources::gen_lib::SourceImplInfo& info);
  void                  deinit_device ();
  IEvent::ptr           get_interface_event ();
  VideoCodecInterf::ptr get_codec_interf ();
  int                   get_filled_buf (::dlls::sources::gen_lib::syn::pkeys2bufs_type& bufs);
  void                  update_source_info (const ::dlls::sources::gen_lib::SourceImplInfo& info);

  static void buf_callback (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf);

  private:
  //  internal typess
  using std::list< utils::dbufs::video::IVideoBuf::ptr > bufs_type;
  using std::mutex                                       sync_type;
  using std::lock_guard< sync_type >                     lock_type;

  void buf_callback_int (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf);
  void complete_bufs_int (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf);
  void free_bufs_int (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf);
  void update_codec_props_int (MMAL_PORT_T* port, MMAL_BUFFER_HEADER_T* buf);


  bool                     init_device_;          //< Флаг инициализации устройства openmax
  DriverState*             devstate_;             //<
  bufs_type                empty_video_bufs_;     //< Список буферов для приема данных с устройства
  bufs_type                ready_video_bufs_;     //< Список буферов для передачи готовых данных в систему
  sync_type                mtx_;                  //< Для синхронизации доступа к очередям буферов
  VideoCodecInterf::ptr    video_codec_interf_;   //<
  int                      video_frame_size_;     //< Размео данных текщуего кадра video
  time_type                video_beg_time_;       //< Время начала сжатия кадра
  VideoCodecProp::craw_ptr codec_props_;          //< Указатель на свойства коррекции изображения, которые могут прийти от клиетов через icorrection_
};

}   // namespace dlls::sources::v4l2_vgen::video

#endif
