#pragma once
/**
\file       video-codec-flat-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::codec
{
/// Структура для группировки свойств кодеков в системе
/// Может использоваться как POD тип, для бинарного сохранения/восстановления/передачи между различными платформами
struct VideoCodecFlatProp final {
  explicit VideoCodecFlatProp (
    const libs::utility::uids::minor::id_val& format             = libs::utility::uids::minor::id_val::unknown,
    const CodecModes&                         type               = CodecModes::coder,
    std::uint32_t                             quality            = 50,
    float                                     max_percent_pframe = 8.0F,
    std::uint32_t                             max_period_kframe  = 500,
    float                                     percent_block      = 8.0F,
    bool                                      nocolor            = false);

  VideoCodecFlatProp (const VideoCodecFlatProp& op);
  const VideoCodecFlatProp& operator= (const VideoCodecFlatProp& op);

  void correct ();
  void reset ();

  std::uint16_t                      size_ { sizeof (VideoCodecFlatProp) };                     //< Текущий размер данной структуры, требуется для идентификации версии
  libs::utility::uids::minor::id_val format_ { libs::utility::uids::minor::id_val::unknown };   //<
  CodecModes                         type_ { CodecModes::coder };                               //< Режим работы (кодер/декодер)
  std::uint32_t                      quality_ { 50 };                                           //< Качество сжатия от 1 до 100
  float                              max_percent_pframe_ { 8.0F };                              //< Максимальный процент обновляея экрана, при котором будет генерироваться P-frame
  std::uint32_t                      max_period_kframe_ { 500 };                                //< Максимальный период ключевых кадров
  float                              percent_block_ { 8.0F };                                   //<
  bool                               nocolor_ { false };                                        //< Флаг, отбрасывать цвет, даже если он есть в исходном изображении (сжатом/несжатом)
};

auto to_string (const VideoCodecFlatProp&) -> std::string;
auto to_bitrate_x264 (const VideoCodecFlatProp&, std::uint32_t, std::uint32_t) -> std::uint32_t;
auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value&, const VideoCodecFlatProp&) -> void;
auto tag_invoke (::boost::json::value_to_tag< VideoCodecFlatProp >, const ::boost::json::value&) -> VideoCodecFlatProp;
}   // namespace libs::events_base::props::videos::generic::codec
