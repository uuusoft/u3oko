#pragma once
/**
\file       mjpeg-impl.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vcodec_mjpg
\brief      Объявление mjpeg кодека.
*/

namespace dlls { namespace codecs { namespace vcodec_mjpg {
/**
\brief  MJPEG кодек.
*/
class MjpegImpl : public ::dlls::codecs::codec_gen::CodecGeneric
{
  public:
  MjpegImpl ();

  virtual ~MjpegImpl ();


  protected:
  //  CodecGeneric overrides
  virtual void                 init_int (const codec_gen::InfoGenCodec &_info) override;
  virtual void                 code_int (const Buffs *_src, Buffs *_dst, events_type *_events) override;
  virtual void                 decode_int (const Buffs *_src, Buffs *_dst, events_type *_events) override;
  virtual void                 set_codec_info_int (const VideoCodecProp *_info) override;
  virtual void                 get_codec_info_int (VideoCodecProp *_info) override;
  virtual void                 set_cpu_int (::libs::helpers::sys::cpu::TypeExtCpu _optim) override;
  virtual const StatisticInfo &get_statistic_info_int () const override;
  virtual void                 reset_statistic_info_int () override;


  private:
  void comp_iframe (bool _colored, ProxyBuff &_dst, int &_out_size);

  void decomp_iframe (const HeaderIFrame *_head, const ProxyBuff &_src, const int _src_size);

  VideoCodecProp             cinfo_;               //< Свойства сжатия для кодека.
  ::libs::optim::io::hioptim fx16_x8_;             //< Указатель на реализацию по преобразованию формата кадра из X16 в X8
  ::libs::optim::io::hioptim fx8_x16_;             //< Указатель на реализацию по преобразованию формата кадра из X8 в X16
  ::libs::optim::io::hioptim fhsl_to_rgb24_;       //< Указатель на реализацию по преобразованию HSL в RGB
  StatisticInfo              statistic_;           //< ???
  CallerImpl::ptr            pthreads_;            //< Пул рабочих потоков
  IVideoBuff::ptr            temp_buff_;           //< Временный буфер для хранения подготовленного к сжатию кадра в совместимом для этого формате (RGB, Y8, etc).
  unsigned char *            jpeg_buff_;           //< Буфер библиотеки JPEG для кодирования
  unsigned int               size_jpeg_buff_;      //< Размер буфера для кодирования.
  tjhandle                   hjpeg_;               //< Устройство для кодирования jpeg.
};

}}}      // namespace dlls::codecs::vcodec_mjpg
