#pragma once
/**
\file       style-frame.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_codec_gen
\brief      empty brief
*/

namespace dlls { namespace codecs { namespace codec_gen {
/**
  \brief  Стиль сжатого кадра.
  */
enum struct StyleFrame
{
  unknown = 0,      //< Неизвестно/не установлено, для общности.
  iframe  = 1,      //< I кадр.
  pframe  = 2,      //< P кадр.
  bframe  = 3       //< B кадр.
};
/**
\brief      Функция сброса поля в текстовый вид.
\param[in]  _val указатель на поле.
\return     текстовое описание поля.
*/
inline std::string
to_str (const StyleFrame& _val)
{
  switch (_val)
    {
    case StyleFrame::unknown:
      return "unknown";
    case StyleFrame::iframe:
      return "iframe";
    case StyleFrame::pframe:
      return "pframe";
    case StyleFrame::bframe:
      return "bframe";
    }

  XULOG_WARNING ("unknown style frame, " << UUU_ICAST_INT (_val));
  return "invalid";
}

}}}      // namespace dlls::codecs::codec_gen
