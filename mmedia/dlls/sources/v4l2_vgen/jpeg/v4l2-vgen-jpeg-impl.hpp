#pragma once
/**
\file       v4l2-vgen-jpeg-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
namespace dlls::sources::v4l2_openmax_vgen::jpeg
{
/// Реализация унифицированного захвата данных из системно зависимых устройств
class JpegImpl final
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (JpegImpl)

  explicit JpegImpl (DriverState *device_state);
  ~JpegImpl ();

  bool        init_device (const ::dlls::sources::gen_lib::SourceImplInfo &info);
  void        deinit_device ();
  void        encoder_buf_callback (MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buf);
  IEvent::ptr get_interface_event ();
  int         get_filled_buf (::dlls::sources::gen_lib::syn::pkeys2bufs_type &bufs);
  void        update_source_info (const ::dlls::sources::gen_lib::SourceImplInfo &info);

  private:
  //  internal typess
  using std::list< utils::dbufs::video::IVideoBuf::ptr > bufs_type;
  using std::mutex                                       sync_type;
  using std::scoped_lock< sync_type >                    lock_type;


  bool                      init_device_;         //< Флаг инициализации устройства openmax
  DriverState              *devstate_;            //<
  bufs_type                 empty_jpeg_bufs_;     //< Список буферов для приема данных с устройства
  bufs_type                 ready_jpeg_bufs_;     //< Список буферов для передачи готовых данных в систему
  sync_type                 mtx_;                 //< Для синхронизации доступа к очередям буферов
  JpegCodecImageInterf::ptr jpeg_codec_interf_;   //<
  int                       jpeg_frame_size_;     //< Размео данных текщуего кадра jpeg
  time_type                 jpeg_beg_time_;       //<
  VideoCodecProp::craw_ptr  codec_props_;         //< Указатель на свойства коррекции изображения, которые могут прийти от  клиетов через icorrection_
};

}   // namespace dlls::sources::v4l2_openmax_vgen::jpeg
#endif
