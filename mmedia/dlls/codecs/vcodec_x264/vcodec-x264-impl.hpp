#pragma once
/**
\file       vcodec-x264-impl.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.08.2018
\project    u3_vcodec_x264
*/

namespace dlls::codecs::vcodec_x264
{
class x264Impl final : public ::dlls::codecs::codec_gen::CodecGeneric
{
  public:
  x264Impl ();
  virtual ~x264Impl ();

  protected:
  //  CodecGeneric overrides
  virtual void init_int (const codec_gen::InfoGenCodec &info) override;
  virtual bool code_int (const ::libs::bufs::Bufs *src, ::libs::bufs::Bufs *dst, syn::TransformInfo::tevents_type *events) override;
  virtual bool decode_int (const ::libs::bufs::Bufs *src, ::libs::bufs::Bufs *dst, syn::TransformInfo::tevents_type *events) override;
  virtual void set_codec_info_int (const syn::VideoCodecProp *info) override;
  virtual void get_codec_info_int (syn::VideoCodecProp *info) override;
  virtual void set_cpu_int (::libs::helpers::sys::cpu::CpuExts optim) override;
  virtual void reset_statistic_info_int () override;

  virtual const syn::StatisticInfo &get_statistic_info_int () const override;

  private:
  bool compress_frame (bool, ::libs::optim::io::ProxyBuf &, const syn::IVideoBuf::raw_ptr, std::int32_t &);
  bool decompress_frame (const syn::HeaderIFrame *, const ::libs::optim::io::ProxyBuf &, const std::int32_t, const syn::IVideoBuf::raw_ptr);

  syn::VideoCodecProp                     cinfo_;              //< Свойства сжатия для кодека
  ::libs::optim::io::hioptim              fx16_x8_;            //< Указатель на реализацию по преобразованию формата кадра из X16 в X8
  ::libs::optim::io::hioptim              fx8_x16_;            //< Указатель на реализацию по преобразованию формата кадра из X8 в X16
  ::libs::optim::io::hioptim              fhsl_to_rgb24_;      //< Указатель на реализацию по преобразованию HSL в RGB24
  ::libs::optim::io::hioptim              i420_to_rgb24_;      //< Указатель на реализацию по преобразованию I420 в RGB24
  syn::StatisticInfo                      statistic_;          //<
  ::libs::optim::mcalls::IMCaller::ptr    pthreads_;           //< Пул рабочих потоков
  syn::IVideoBuf::ptr                     src_buf_;            //< Временный буфер для хранения подготовленного к сжатию кадра в совместимом для этого формате (RGB, Y8, I420 etc)
  syn::AllocBufInfo                       coder_frame_info_;   //< Параметры которые были использованы для создания кодера
  std::unique_ptr< impls::IBaseH264Impl > coder_impl_;         //< Выбранная реализация кодера
};
}   // namespace dlls::codecs::vcodec_x264
