#pragma once
/**
\file       video-codec-flat-prop.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::codec
{
/// Структура для группировки свойств кодеков в системе
/// Может использоваться как POD тип, для бинарного сохранения/восстановления/передачи между различными платформами
struct VideoCodecFlatProp final {
  explicit VideoCodecFlatProp (
    const libs::helpers::uids::minor::id_val& format             = libs::helpers::uids::minor::id_val::unknown,
    const CodecModes&                         type               = CodecModes::coder,
    std::uint32_t                             quality            = 50,
    float                                     max_percent_pframe = 8.0f,
    std::uint32_t                             max_period_kframe  = 500,
    float                                     percent_block      = 8.0f,
    bool                                      nocolor            = false);

  VideoCodecFlatProp (const VideoCodecFlatProp& op);
  const VideoCodecFlatProp& operator= (const VideoCodecFlatProp& op);

  void correct ();
  void reset ();

  std::uint16_t                      size_;                 //< Текущий размер данной структуры, требуется для идентификации версии
  libs::helpers::uids::minor::id_val format_;               //<
  CodecModes                         type_;                 //< Режим работы (кодер/декодер)
  std::uint32_t                      quality_;              //< Качество сжатия от 1 до 100
  float                              max_percent_pframe_;   //< Максимальный процент обновляея экрана, при котором будет генерироваться P-frame
  std::uint32_t                      max_period_kframe_;    //< Максимальный период ключевых кадров
  float                              percent_block_;        //<
  bool                               nocolor_;              //< Флаг, отбрасывать цвет, даже если он есть в исходном изображении (сжатом/несжатом)
};

std::string        to_string (const VideoCodecFlatProp& info);
std::uint32_t      to_bitrate_x264 (const VideoCodecFlatProp& info, std::uint32_t width, std::uint32_t height);
void               tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const VideoCodecFlatProp& src);
VideoCodecFlatProp tag_invoke (::boost::json::value_to_tag< VideoCodecFlatProp >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::generic::codec
