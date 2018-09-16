//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       morph-operation-type.hpp
\date       10.09.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace videos { namespace generic { namespace morph {
/**
\brief  Перечисление морфологических операций над изображением.
*/
enum struct MorphOperationType
{
  empty    = 0,      //< Пустая операция, точнее ее отсутствие. Используется для тестов (скорости/стабильности/etc).
  erosion  = 1,      //< Операция эрозии.
  dilation = 2,      //< Операция дилатации.
  binary   = 4       //< Операция бинаризации.
};
/**
\brief      Вспомогательная функция конвертации строки в тип морфологической операции.
\param[in]  _txt  текстовое описание операции.
\return     тип операции.
*/
inline MorphOperationType
str2type_op (const std::string& _txt)
{
  const std::pair<std::string, MorphOperationType> _ops[] = {
    std::pair<std::string, MorphOperationType> ("erosion", MorphOperationType::erosion),
    std::pair<std::string, MorphOperationType> ("dilation", MorphOperationType::dilation),
    std::pair<std::string, MorphOperationType> ("binary", MorphOperationType::binary),
    std::pair<std::string, MorphOperationType> ("skip", MorphOperationType::empty)
  };

  for (const auto& _op : _ops)
    {
      if (_op.first == _txt)
        {
          return _op.second;
        }
    }
  XULOG_WARNING ("unknown text id MorphOperationType " << _txt);
  return MorphOperationType::empty;
}
/**
\brief      Функция конвертации типа морфологической операции в строку.
\param[in]  _val  тип морфологической операции.
|return     строка.
*/
inline std::string
to_str (const MorphOperationType& _val)
{
  const std::unordered_map<MorphOperationType, std::string> _ops = {
    { MorphOperationType::erosion, "erosion" },
    { MorphOperationType::dilation, "dilation" },
    { MorphOperationType::binary, "binary" },
    { MorphOperationType::empty, "skip" }
  };

  auto _find = _ops.find (_val);
  if (_ops.end () == _find)
    {
      XULOG_WARNING ("unknown MorphOperationType " << UUU_ICAST_INT (_val));
      return "unknown";
    }
  return _find->second;
}

}}}}}}      // namespace libs::ievents::props::videos::generic::morph
