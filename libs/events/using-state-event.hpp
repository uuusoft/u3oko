//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       using-state-event.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      Объявление состояний "использование" свойства.
*/

namespace libs { namespace events {
/**
\brief  Перечисление различных состояний, в которых может находится свойство.
*/
enum struct UsingStateEvent
{
  disabled  = 0,      //< Свойство отключено.
  enabled   = 1,      //< Свойство включено.
  automatic = 2       //< Свойство используется автоматически.
};
/**
\brief      ???
\param[in]  _val
\return     ???
*/
inline std::string
to_str (const UsingStateEvent& _val)
{
  const std::unordered_map<UsingStateEvent, std::string> _mapper =
    {
      { UsingStateEvent::disabled, "disabled" },
      { UsingStateEvent::enabled, "enabled" },
      { UsingStateEvent::automatic, "automatic" }
    };

  auto _find = _mapper.find (_val);
  if (_mapper.end () == _find)
    {
      XULOG_WARNING ("unknown type UsingStateEvent, " << UUU_ICAST_INT (_val));
      return "unknown";
    }

  return _find->second;
}

}}      // namespace libs::events
