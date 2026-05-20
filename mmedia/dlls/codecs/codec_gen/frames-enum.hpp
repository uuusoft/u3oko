#pragma once
/**
\file       frames-enum.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
/// Стиль сжатого кадра
enum class Frames : std::uint32_t
{
  unknown  = 0x0,   //< Неизвестно/не установлено, для общности
  iframe   = 0x1,   //< I кадр
  idrframe = 0x2,   //< IDR кадр
  pframe   = 0x3,   //< P кадр
  bframe   = 0x4    //< B кадр
};

/// Функция сброса поля в текстовый вид
/// \param[in]  val указатель на поле
/// \return     текстовое описание поля.
inline std::string
to_string (const Frames& val)
{
  switch (val)
  {
  case Frames::unknown:
    return "unknown";
  case Frames::iframe:
    return "iframe";
  case Frames::idrframe:
    return "idrframe";
  case Frames::pframe:
    return "pframe";
  case Frames::bframe:
    return "bframe";
  default:
    return "unknown Frames " + VTOLOG (U3_CAST_INT32_FORCE (val));
  }
}
}   // namespace dlls::codecs::codec_gen
