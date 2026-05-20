#pragma once
/**
\file       codec-generic.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
/// Базовый класс для реализации видео кодеков
class CodecGeneric
{
  public:
  //  ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (CodecGeneric)

  CodecGeneric ();
  virtual ~CodecGeneric ();

  CodecGeneric (const CodecGeneric&)            = delete;
  CodecGeneric& operator= (const CodecGeneric&) = delete;

  void init (const InfoGenCodec& info);
  void code (const ::libs::bufs::Bufs*, ::libs::bufs::Bufs*, syn::TransformInfo::tevents_type*);
  void decode (const ::libs::bufs::Bufs*, ::libs::bufs::Bufs*, syn::TransformInfo::tevents_type*);

  /// Функция устаналивает текущие свойства кодирования и декодирования
  void                 set_codec_info (const syn::VideoCodecProp* info);
  void                 get_codec_info (syn::VideoCodecProp* info);
  void                 set_cpu (syn::CpuExts optim);
  void                 set_transform_info (const syn::NodeID* id_node, syn::TransformInfo*);
  const StatisticInfo& get_statistic_info () const;
  void                 reset_statistic_info ();

  protected:
  //  CodecGeneric interface
  virtual void                 init_int (const InfoGenCodec&)                                                                 = 0;
  virtual bool                 code_int (const ::libs::bufs::Bufs*, ::libs::bufs::Bufs*, syn::TransformInfo::tevents_type*)   = 0;
  virtual bool                 decode_int (const ::libs::bufs::Bufs*, ::libs::bufs::Bufs*, syn::TransformInfo::tevents_type*) = 0;
  virtual void                 set_codec_info_int (const syn::VideoCodecProp*)                                                = 0;
  virtual void                 get_codec_info_int (syn::VideoCodecProp*)                                                      = 0;
  virtual void                 set_cpu_int (syn::CpuExts optim)                                                               = 0;
  virtual void                 reset_statistic_info_int ()                                                                    = 0;
  virtual const StatisticInfo& get_statistic_info_int () const                                                                = 0;

  syn::CpuExts        simd_;             //< Выбранный тип расширения процессора
  InfoGenCodec        iinfo_;            //< Общие параметры, разделяемые между всеми реализациями кодеков
  std::int64_t        counter_frames_;   //< Счетчик кадров в текущем сеансе кодирования/декодирования
  syn::TransformInfo* transinfo_;        //< Указатель на текущий параметр при вызове функции transform
  const syn::NodeID*  id_node_graph_;    //< Указатель на идентификатор объекта графа обработки данных, которому принадлежит данный кодек
};
}   // namespace dlls::codecs::codec_gen
