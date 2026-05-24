#pragma once
/**
\file       styles-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_codec_gen
*/

namespace dlls::codecs::codec_gen
{
/// Тип, задает стили кодирования в виде флагов
enum class Styles : std::uint32_t
{
  base        = 0x01,   //< Базовый стиль по умолчанию, для общности
  only_iframe = 0x02,   //< Использовать только I кадры
  strip_color = 0x04,   //< Не кодировать цветовую составляющую
  unknown     = 0xFF    //< Не определенно для общности
};

/// Функция сброса поля в текстовый вид
/// \param[in]  val указатель на поле
/// \return     текстовое описание поля
inline std::string
to_string (const Styles& val)
{
  std::string ret;

  if (U3_CAST_INT32_FORCE (val) & U3_CAST_INT32_FORCE (Styles::base))
  {
    ret += "base";
  }
  if (U3_CAST_INT32_FORCE (val) & U3_CAST_INT32_FORCE (Styles::only_iframe))
  {
    ret += "+only_iframe";
  }
  if (U3_CAST_INT32_FORCE (val) & U3_CAST_INT32_FORCE (Styles::strip_color))
  {
    ret += "+strip_color";
  }
  return ret;
}
}   // namespace dlls::codecs::codec_gen
