#pragma once
/**
\file       link-modules-type.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace details {
/**
\brief  Перечисление различных соединений между подсистемами.
*/
enum struct LinkModulesType
{
  gui         = 0,      //< Соединение между основном приложением и интерфейсом.
  http        = 1,      //< Соединение между приложением и http сервером.
  mdata       = 2,      //< Соединение между основным приложением и модулем обработки данных.
  log         = 3,      //< Соединение между логером и приложением.
  storage     = 4,      //< Соединение между подсистемой хранения данных и приложением.
  rtp         = 5,      //< Соединение между подсистемой хранения данных и приложением.
  integration = 6,      //< Соединение между подсистемой хранения данных и приложением.
  events      = 7       //< Соединение между подсистемой событий и приложением.
};
/**
\brief  ???
*/
inline std::string
to_str (const LinkModulesType& _val)
{
  switch (_val)
    {
    case LinkModulesType::gui:
      return "gui";
    case LinkModulesType::http:
      return "http";
    case LinkModulesType::mdata:
      return "mdata";
    case LinkModulesType::log:
      return "log";
    case LinkModulesType::storage:
      return "storage";
    case LinkModulesType::rtp:
      return "rtp";
    case LinkModulesType::integration:
      return "integration";
    case LinkModulesType::events:
      return "events";
    }
  XULOG_WARNING("unknown type LinkModulesType, " << UUU_ICAST_INT(_val));
  return std::string ("unknown /") + ::to_str (UUU_ICAST_INT (_val)) + "/";
}

}}}      // namespace libs::link::details
