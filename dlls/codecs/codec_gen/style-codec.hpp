#pragma once
/**
\file       style-codec.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
/**
  \brief  Тип, задает стили кодирования в виде флагов.
  */
enum struct StyleCodec
{
  base        = 1,      //< Базовый стиль по умолчанию, для общности.
  only_iframe = 2,      //< Использовать только I кадры.
  strip_color = 4       //< Не кодировать цветовую составляющую.
};
/**
\brief      Функция сброса поля в текстовый вид.
\param[in]  _val указатель на поле.
\return     текстовое описание поля.
*/
inline std::string
to_str (const StyleCodec& _val)
{
  std::string _ret;

  if (UUU_ICAST_INT (_val) & UUU_ICAST_INT (StyleCodec::base))
    {
      _ret += "base";
    }
  if (UUU_ICAST_INT (_val) & UUU_ICAST_INT (StyleCodec::only_iframe))
    {
      _ret += "+only_iframe";
    }
  if (UUU_ICAST_INT (_val) & UUU_ICAST_INT (StyleCodec::strip_color))
    {
      _ret += "+strip_color";
    }
  return _ret;
}

}}}      // namespace dlls::codecs::codec_gen
