#pragma once
/**
\file       type-path.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_iproperties
\brief      Объявление различных типов путей в приложении.
*/

namespace libs { namespace iproperties { namespace appl_paths {
/**
  \brief  Тип для путей к различным категориям данных.
  */
enum struct TypePath
{
  generic_appl    = 0,       //< Общий путь к системе. xx
  logs            = 1,       //< Путь к логам системы. RW
  main_exe        = 2,       //< Путь к основному испоняемому файлу системы. R
  bins            = 3,       //< Пусть к дополнительнымому (расширениям) коду системы. R
  appl_xml        = 4,       //< Путь к основному файлу конфигурации системы. R
  data_xml        = 5,       //< Путь к файлу конфигурации данных системы. R
  gui_xml         = 6,       //< Путь к конфигурационнму файлу интерфейса системы. R
  images          = 7,       //< Путь к ресурсам изображени системы. R
  media           = 8,       //< Путь к медиа ресурсам системы. R
  web             = 9,       //< Путь к web ресурсам системы. R
  work            = 10,      //< Путь к рабочему каталогу системы. RW
  temp            = 11,      //< Путь к временному каталогу данного сеанса работы. RW
  default_storage = 12,      //< Путь к каталогу по умолчанию для данных хранилища. RW
  debug_test      = 13       //< Для отладки.
};

inline std::string
to_str (const TypePath& _val)
{
  switch (_val)
    {
    case TypePath::generic_appl:
      return "generic_appl";
    case TypePath::main_exe:
      return "main_exe";
    case TypePath::bins:
      return "bins";
    case TypePath::logs:
      return "logs";
    case TypePath::images:
      return "images";
    case TypePath::media:
      return "media";
    case TypePath::data_xml:
      return "data_xml";
    case TypePath::gui_xml:
      return "gui_xml";
    case TypePath::appl_xml:
      return "appl_xml";
    case TypePath::web:
      return "web";
    case TypePath::temp:
      return "temp";
    case TypePath::work:
      return "work";
    case TypePath::default_storage:
      return "default_storage";
    }

  XULOG_ERROR ("unknown val TypePath, " << UUU_ICAST_INT (_val));
  return "";
}

}}}      // namespace libs::iproperties::appl_paths
