#pragma once
/**
\file       paths-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_iproperties_lib
*/

namespace libs::iproperties::appl_paths
{
/// Тип для путей к различным категориям данных
enum class Paths : std::uint32_t
{
  generic_appl             = 0x00,   //< Общий путь к системе XX
  logs                     = 0x01,   //< Путь к логам системы RW
  main_appl                = 0x02,   //< Путь к основному испоняемому файлу системы R
  bins                     = 0x03,   //< Пусть к дополнительномому (расширениям) коду системы R
  emulate_bins             = 0x04,   //< Пусть к библиотекам (или их сурогатам) системы. Используется только для поиска библиотек, а не загрузки R
  templates                = 0x05,   //< Путь к шаблонам для генерации конфигурации системы R
  templates_appl_module    = 0x06,   //< Путь к основному файлу конфигурации системы R
  templates_data_module    = 0x07,   //< Путь к файлу конфигурации данных системы R
  templates_gui_module     = 0x08,   //< Путь к конфигурационным файлам GUI подсистемы R
  templates_event_module   = 0x09,   //< Путь к конфигурационным файлам подсистемы событий R
  templates_storage_module = 0x0A,   //< Путь к конфигурационным файлам подсистемы хранения данных R
  templates_http_module    = 0x0B,   //< Путь к конфигурационным файлам подсистемы https сервера R
  active_configs           = 0x0C,   //< Путь к актуальной конфигурации системы, сгенерированной по шаблонам RW
  active_appl_module       = 0x0D,   //< Путь к актуальной конфигурации подсистемы приложения, сгенерированной по шаблонам RW
  active_data_module       = 0x0E,   //< Путь к актуальной конфигурации подсистемы обработки данных, сгенерированной по шаблонам RW
  active_event_module      = 0x0F,   //< Путь к актуальной конфигурации подсистемы событий, сгенерированной по шаблонам RW
  active_storage_module    = 0x10,   //< Путь к актуальной конфигурации подсистемы хранения данных, сгенерированной по шаблонам RW
  temp                     = 0x11,   //< Путь к временному каталогу данного сеанса работы RW
  debug_test               = 0x20,   //< Для отладки XX
  unknown                  = 0xFF    //< Не определенно для общности XX
};

const std::string& to_string (const Paths& val);
}   // namespace libs::iproperties::appl_paths
