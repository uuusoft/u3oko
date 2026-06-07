#pragma once
/**
\file       mjpeg-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  virtual void                      init_int (const codec_gen::InfoGenCodec &info) override;
  virtual bool                      code_int (const ::libs::bufs::Bufs *src, ::libs::bufs::Bufs *dst, syn::TransformInfo::tevents_type *events) override;
  virtual bool                      decode_int (const ::libs::bufs::Bufs *src, ::libs::bufs::Bufs *dst, syn::TransformInfo::tevents_type *events) override;
  virtual void                      set_codec_info_int (const syn::VideoCodecProp *info) override;
  virtual void                      get_codec_info_int (syn::VideoCodecProp *info) override;
  virtual void                      set_cpu_int (::libs::helpers::sys::cpu::CpuExts optim) override;
  virtual void                      reset_statistic_info_int () override;
  virtual const syn::StatisticInfo &get_statistic_info_int () const override;

  private:
  bool comp_iframe (bool colored, ::libs::optim::io::ProxyBuf &dst, int &out_size);
  bool decomp_iframe (const syn::HeaderIFrame *head, const ::libs::optim::io::ProxyBuf &src, const std::int32_t src_size);
  void update_coder (const unsigned long max_size);
  void update_decoder ();

  syn::VideoCodecProp                  cinfo_;                     //< Свойства сжатия для кодека
  ::libs::optim::io::hioptim           fx16_x8_;                   //< Указатель на реализацию по преобразованию формата кадра из X16 в X8
  ::libs::optim::io::hioptim           fx8_x16_;                   //< Указатель на реализацию по преобразованию формата кадра из X8 в X16
  ::libs::optim::io::hioptim           fhsl_to_rgb24_;             //< Указатель на реализацию по преобразованию HSL в RGB
  syn::StatisticInfo                   statistic_;                 //<
  ::libs::optim::mcalls::IMCaller::ptr pthreads_;                  //< Пул рабочих потоков
  syn::IVideoBuf::ptr                  temp_buf_      = 0;         //< Временный буфер для хранения подготовленного к сжатию кадра в совместимом для этого формате (RGB, Y8, etc)
  std::uint8_t                        *jpeg_buf_      = nullptr;   //< Буфер библиотеки JPEG для кодирования
  std::uint32_t                        size_jpeg_buf_ = 0;         //< Размер буфера для кодирования
  tjhandle                             hjpeg_         = nullptr;   //< Устройство для кодирования jpeg
};
}   // namespace dlls::codecs::vcodec_mjpg
