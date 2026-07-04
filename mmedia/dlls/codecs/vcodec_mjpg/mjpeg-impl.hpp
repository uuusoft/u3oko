#pragma once
/**
\file       mjpeg-impl.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vcodec_mjpg
\brief      Объявление mjpeg кодека
*/

namespace dlls::codecs::vcodec_mjpg
{
/// MJPEG кодек
class MjpegImpl final : public ::dlls::codecs::codec_gen::CodecGeneric
{
  public:
  MjpegImpl ();
  virtual ~MjpegImpl ();

  protected:
  //  CodecGeneric overrides
  virtual auto init_int (const codec_gen::InfoGenCodec &) -> void override;
  virtual auto code_int (const ::libs::bufs::Bufs *, ::libs::bufs::Bufs *, syn::TransformInfo::tevents_type *) -> bool override;
  virtual auto decode_int (const ::libs::bufs::Bufs *, ::libs::bufs::Bufs *, syn::TransformInfo::tevents_type *) -> bool override;
  virtual auto set_codec_info_int (const syn::VideoCodecProp *) -> void override;
  virtual auto get_codec_info_int (syn::VideoCodecProp *) -> void override;
  virtual auto set_cpu_int (::libs::utility::sys::cpu::CpuExts) -> void override;
  virtual auto reset_statistic_info_int () -> void override;
  virtual auto get_statistic_info_int () const -> const syn::StatisticInfo & override;

  private:
  bool comp_iframe (bool, ::libs::optim::io::ProxyBuf &, int &);
  bool decomp_iframe (const syn::HeaderIFrame *, const ::libs::optim::io::ProxyBuf &, const std::int32_t);
  void update_coder (const unsigned long max_size);
  void update_decoder ();

  syn::VideoCodecProp        cinfo_;                     //< Свойства сжатия для кодека
  ::libs::optim::io::hioptim fx16_x8_;                   //< Указатель на реализацию по преобразованию формата кадра из X16 в X8
  ::libs::optim::io::hioptim fx8_x16_;                   //< Указатель на реализацию по преобразованию формата кадра из X8 в X16
  ::libs::optim::io::hioptim fhsl_to_rgb24_;             //< Указатель на реализацию по преобразованию HSL в RGB
  syn::StatisticInfo         statistic_;                 //<
  syn::IMCaller::ptr         pthreads_;                  //< Пул рабочих потоков
  syn::IVideoBuf::ptr        temp_buf_      = 0;         //< Временный буфер для хранения подготовленного к сжатию кадра в совместимом для этого формате (RGB, Y8, etc)
  std::uint8_t              *jpeg_buf_      = nullptr;   //< Буфер библиотеки JPEG для кодирования
  std::uint32_t              size_jpeg_buf_ = 0;         //< Размер буфера для кодирования
  tjhandle                   hjpeg_         = nullptr;   //< Устройство для кодирования jpeg
};
}   // namespace dlls::codecs::vcodec_mjpg
