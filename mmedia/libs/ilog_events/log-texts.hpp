#pragma once
/**
\file       log-texts.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    uuu_ilog_events
*/

namespace libs::ilog_events
{
/// Тип для идентификации части текста в сообщении логирования
enum class LogTexts : std::uint32_t
{
  subsys   = 0x00,   //< Подсистема, которая сгенерировала сообещение
  text     = 0x01,   //< Текст сообщения (информационная часть)
  function = 0x02,   //< Функция подсистемы, которая сгенерировала сообщение
  file     = 0x03,   //< Функция подсистемы, которая сгенерировала сообщение
  line     = 0x04,   //< Строка в функции
  level    = 0x05,   //< Уровень сообщения ::libs::ievents::props::modules::log::LogLevels
  unknown  = 0xFF    //< Не определенно для общности
};
}   // namespace libs::ilog_events
