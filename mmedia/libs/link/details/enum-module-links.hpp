#pragma once
/**
\file       enum-module-links.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_link
*/

namespace libs::link::details
{
/// Перечисление различных точек соединений
enum class ModuleLinks : std::uint16_t
{
  appl        = 0x00,   //<
  gui         = 0x01,   //< графический интерфейс
  http        = 0x02,   //< http сервер
  mdata       = 0x03,   //< модуль обработки данных
  log         = 0x04,   //< логер
  storage     = 0x05,   //< подсистема хранения данных
  rtp         = 0x06,   //<
  integration = 0x07,   //<
  events      = 0x08,   //< подсистема событий
  users       = 0x09,   //< подсистема аутентификации
  network     = 0x0A,   //< подсистема сетевая
  assistent   = 0x0B,   //< подсистема ассисента
  ai          = 0x0C,   //< подсистема ИИ
  test        = 0x0D,   //< для теста
  unknown     = 0xFF    //< Не определенно для общности
};

const std::string& to_string (const ModuleLinks& val);
}   // namespace libs::link::details
