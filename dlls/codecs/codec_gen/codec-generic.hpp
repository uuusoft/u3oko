#pragma once
/**
\file       codec-generic.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
/**
  \brief  Базовый класс для реализации видео кодека.
  */
class CodecGeneric
{
  public:
  //  ext types
  UUU_THIS_TYPE_HAS_POINTERS_TO_SELF (CodecGeneric);

  CodecGeneric ();

  virtual ~CodecGeneric ();

  CodecGeneric (const CodecGeneric& _src) = delete;
  CodecGeneric& operator= (const CodecGeneric& _src) = delete;

  void init (const InfoGenCodec& _info);

  void code (const Buffs* _src, Buffs* _dst, events_type* _events);

  void decode (const Buffs* _src, Buffs* _dst, events_type* _events);
  /// Функция устаналивает текущие свойства кодирования и декодирования
  void set_codec_info (const VideoCodecProp* _info);

  void get_codec_info (VideoCodecProp* _info);

  void set_cpu (::libs::helpers::sys::cpu::TypeExtCpu _optim);

  const StatisticInfo& get_statistic_info () const;

  void reset_statistic_info ();


  protected:
  //  CodecGeneric interface
  virtual void                 init_int (const InfoGenCodec& _info)                              = 0;
  virtual void                 code_int (const Buffs* _src, Buffs* _dst, events_type* _events)   = 0;
  virtual void                 decode_int (const Buffs* _src, Buffs* _dst, events_type* _events) = 0;
  virtual void                 set_codec_info_int (const VideoCodecProp* _info)                  = 0;
  virtual void                 get_codec_info_int (VideoCodecProp* _info)                        = 0;
  virtual void                 set_cpu_int (::libs::helpers::sys::cpu::TypeExtCpu optim)         = 0;
  virtual const StatisticInfo& get_statistic_info_int () const                                   = 0;
  virtual void                 reset_statistic_info_int ()                                       = 0;

  TypeExtCpu   simd_;       //< ???
  InfoGenCodec iinfo_;      //< ???
};

}}}      // namespace dlls::codecs::codec_gen
