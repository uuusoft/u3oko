//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       deep-event-clone-type.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events {
/**
\brief  Перечисление различных способов клонирования события.
*/
enum struct DeepEventCloneType
{
  empty = 0,      //< Клонирование пустого события, у копии совпадает только тип.
  full  = 1       //< Глубокое клонирование события, у коппи совпадает и тип, и значения полей.
};
/**
\brief  ???
*/
inline std::string
to_str (const DeepEventCloneType& _val)
{
  const std::unordered_map<DeepEventCloneType, std::string> _mapper =
    {
      { DeepEventCloneType::empty, "empty" },
      { DeepEventCloneType::full, "full" }
    };

  auto _find = _mapper.find (_val);
  if (_mapper.end () == _find)
    {
      XULOG_WARNING ("unknown type DeepEventCloneType, " << UUU_ICAST_INT (_val));
      return "unknown";
    }

  return _find->second;
}

}}      // namespace libs::events
