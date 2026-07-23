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
  U3_ADD_POINTERS_TO_SELF (CodecGeneric)
  U3_ADD_DELETE_MOVE_COPY (CodecGeneric)

  CodecGeneric ()          = default;
  virtual ~CodecGeneric () = default;

  void init (const InfoGenCodec &info);
  void code (const ::libs::bufs::Bufs *, ::libs::bufs::Bufs *, syn::TransformInfo::tevents_type *);
  void decode (const ::libs::bufs::Bufs *, ::libs::bufs::Bufs *, syn::TransformInfo::tevents_type *);

  /// Функция устаналивает текущие свойства кодирования и декодирования
  auto set_codec_info (const syn::VideoCodecProp *) -> void;
  auto get_codec_info (syn::VideoCodecProp *) -> void;
  auto set_cpu (syn::CpuExts) -> void;
  auto set_transform_info (const syn::NodeID *, syn::TransformInfo *) -> void;
  auto get_statistic_info () const -> const StatisticInfo &;
  auto reset_statistic_info () -> void;

  protected:
  //  CodecGeneric interface
  virtual auto init_int (const codec_gen::InfoGenCodec &) -> void                                                        = 0;
  virtual auto code_int (const ::libs::bufs::Bufs *, ::libs::bufs::Bufs *, syn::TransformInfo::tevents_type *) -> bool   = 0;
  virtual auto decode_int (const ::libs::bufs::Bufs *, ::libs::bufs::Bufs *, syn::TransformInfo::tevents_type *) -> bool = 0;
  virtual auto set_codec_info_int (const syn::VideoCodecProp *) -> void                                                  = 0;
  virtual auto get_codec_info_int (syn::VideoCodecProp *) -> void                                                        = 0;
  virtual auto set_cpu_int (::libs::utility::sys::cpu::CpuExts) -> void                                                  = 0;
  virtual auto reset_statistic_info_int () -> void                                                                       = 0;
  virtual auto get_statistic_info_int () const -> const StatisticInfo &                                                  = 0;

  InfoGenCodec        iinfo_;                                 //< Общие параметры, разделяемые между всеми реализациями кодеков
  syn::CpuExts        simd_          = syn::CpuExts::usual;   //< Выбранный тип расширения процессора
  std::int64_t        frame_counter_ = 0;                     //< Счетчик кадров в текущем сеансе кодирования/декодирования
  syn::TransformInfo *transinfo_     = nullptr;               //< Указатель на текущий параметр при вызове функции transform
  const syn::NodeID  *id_node_graph_ = nullptr;               //< Указатель на идентификатор объекта графа обработки данных, которому принадлежит данный кодек
};
}   // namespace dlls::codecs::codec_gen
