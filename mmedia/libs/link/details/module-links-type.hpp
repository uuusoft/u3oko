#pragma once
/**
\file       module-links-type.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_link
*/

namespace libs::link::details
{
/// Перечисление различных соединений между подсистемами
enum class ModuleLinks : std::uint16_t
{
  appl        = 0x00,   //<
  gui         = 0x01,   //< Соединение между основном приложением и интерфейсом
  http        = 0x02,   //< Соединение между приложением и http сервером
  mdata       = 0x03,   //< Соединение между основным приложением и модулем обработки данных
  log         = 0x04,   //< Соединение между логером и приложением
  storage     = 0x05,   //< Соединение между подсистемой хранения данных и приложением
  rtp         = 0x06,   //< Соединение между подсистемой хранения данных и приложением
  integration = 0x07,   //< Соединение между подсистемой хранения данных и приложением
  events      = 0x08,   //< Соединение между подсистемой событий и приложением
  users       = 0x09,   //<
  network     = 0x0A,   //<
  assistent   = 0x0B,   //<
  ai          = 0x0C,   //<
  test        = 0x0D,   //<
  unknown     = 0xFF    //< Не определенно для общности
};

const std::string& to_string (const ModuleLinks& val);
}   // namespace libs::link::details
