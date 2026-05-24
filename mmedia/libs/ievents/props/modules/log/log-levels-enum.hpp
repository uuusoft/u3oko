#pragma once
/**
\file       log-levels-enum.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       22.02.2022
\project    u3_ilog_events
*/

namespace libs::ievents::props::modules::log
{
/// Тип сообщения о логировании события
enum class LogLevels : std::uint32_t
{
  disable       = 0x00,   //<  Специальный уровень для отключения всех сообщений
  debug         = 0x01,   //<  Временные сообщение в процессе разработки для отладки
  develop       = 0x02,   //<  Сообщение в процессе разработки для отладки
  exception     = 0x03,   //<  Сообщение о исключении
  invalid_state = 0x04,   //<  Сообщение о внештатной ситуации
  error         = 0x05,   //<  Сообщение об устранимой ошибке
  warning       = 0x06,   //<  Сообщение о предупреждении
  mark          = 0x07,   //<  Информационное сообщение - отметка о существенном событии, значение по умолчанию
  info          = 0x08,   //<  Информационное сообщение
  timing        = 0x09,   //<  Специальный уровень для трассировки задержек рабочих потоков
  data          = 0x0A,   //<  Специальный уровень для трассировки прохождения данных в графе обработки
  unknown       = 0xFF    //<  Не определенно для общности
};

LogLevels          from_raw_val (std::uint32_t val);
const std::string& to_string (const LogLevels& val);
}   // namespace libs::ievents::props::modules::log
