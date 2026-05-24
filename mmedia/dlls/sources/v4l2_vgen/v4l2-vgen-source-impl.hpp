#pragma once
/**
\file       v4l2-vgen-source-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       20.02.2026
\project    u3_v4l2_vgen
*/

namespace dlls::sources::v4l2_vgen
{
/// Реализация унифицированного захвата данных из системно зависимых устройств
class SourceImpl final : public ::dlls::sources::gen_lib::ISourceImpl
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (SourceImpl)

  SourceImpl () = default;
  virtual ~SourceImpl () noexcept;

  private:
  //  internal typess
  using bufs_type = std::list< utils::dbufs::video::IVideoBuf::ptr >;
  using sync_type = std::mutex;
  using lock_type = std::lock_guard< sync_type >;

  void get_fake_buf (syn::IVideoBuf::raw_ptr buf);
  bool init_device (const ::dlls::sources::gen_lib::SourceImplInfo& info);
  void free_device () noexcept;
  void deinit_device ();
  void start_capture ();
  void stop_capture ();

  //  ::dlls::sources::gen_lib::ISourceImpl
  virtual void init_int () override;
  virtual void start_int () override;
  virtual void stop_int () override;
  virtual void get_sources_int (std::vector< syn::DataSourceInfo >& sources) override;
  virtual void get_raw_data_int (syn::pkeys2bufs_type& bufs, syn::tevents_type* events) override;
  virtual void set_cpu_int (::libs::helpers::sys::cpu::CpuExts current_optim) override;
  virtual void update_source_info_int (const ::dlls::sources::gen_lib::SourceImplInfo& info) override;

  std::unique_ptr< camera::CamImpl > v4l2_impl_;                                                          //<
  bool                               v4l2_init_         = false;                                          //< Флаг инициализации устройства v4l2
  std::uint32_t                      current_           = 0;                                              //<
  std::uint32_t                      total_             = 0;                                              //<
  std::int64_t                       counter_frames_    = 0;                                              //< Счетчик переданных клиентам кадров
  std::int32_t                       camera_error_      = 0;                                              //< Код ошибки (опциональный) от подключенной камеры, если не 0 требуется пересоздать устройство
  syn::time_point_type               last_time_restart_ = std::chrono::high_resolution_clock::now ();     //< Время последнего рестарта устройства
  syn::IHardwareCorrect::ptr         icorrection_       = std::make_shared< syn::IHardwareCorrect > ();   //< Опциональная аппаратная реализация коррекции изображения
  syn::IHardwareCapture::ptr         icapture_          = std::make_shared< syn::IHardwareCapture > ();   //< Опциональная аппаратная реализация захвата изображения
};
}   // namespace dlls::sources::v4l2_vgen
