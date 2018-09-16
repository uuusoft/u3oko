//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       video-codec-flat-prop.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace codec {
/**
\brief  Структура для группировки свойств кодеков в системе. 
        Может использоваться как POD тип, для бинарного сохранения/восстановления/передачи между различными платформами.
*/
struct VideoCodecFlatProp
{
  VideoCodecFlatProp ();

  VideoCodecFlatProp (const VideoCodecFlatProp& _op);

  void correct ();

  void reset ();

  const VideoCodecFlatProp& operator= (const VideoCodecFlatProp& _op);

  short         size_;                                                                                          //< Текущий размер данной структуры, требуется для идентификации версии
  TypeCodecMode type_;                                                                                          //< Режим работы (кодер/декодер).
  int           quality_;                                                                                       //< Качество сжатия от 1 до 100
  float         max_percent_pframe_;                                                                            //< Максимальный процент обновляея экрана, при котором будет генерироваться P-frame
  int           max_period_kframe_;                                                                             //< Максимальный период ключевых кадров
  float         percent_block_;                                                                                 //< ???
  bool          monochrome_;                                                                                    //< Флаг, отбрасывать цвет, даже если он есть в исходном изображении (сжатом/несжатом).
  char          entropy_coders_[consts::max_count_entropy_coders][consts::max_len_name_entropy_coder + 1];      //< Список  энтропийных кодеров.
};
/**
\brief      Функция сброса поля в текстовый вид.
\param[in]  _info указатель на поле.
\return     текстовое описание поля.
*/
inline std::string
to_str (const VideoCodecFlatProp& _info)
{
  std::stringstream _str;
  return _str.str ();
}

}}}}}}      // namespace libs::ievents::props::videos::generics::codec
