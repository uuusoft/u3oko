#pragma once
/**
\file       log-vals-enum.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::modules::log
{
/// Фактически поле только для чтения без синхронизации (для скорости), которое содержит в себе уровень логирования для каждого модуля системы
/// Но thread sanitizer считает, поэтому добавлена сихронизация
/// EAI-REFACT-THREAD-SANITIZER
extern std::atomic< LogLevels > g_log_level;

/// Тип для перечисления различных полей для модуля логирования
enum class LogVals : std::uint32_t
{
  max_cache_events              = 0x00,   //< Максимальное количество кешируемых сообщений в ожидании записи на носитель
  ms_max_period_flush_events    = 0x01,   //< Максимальный период кеширования сообщений в ожидании записи на носитель
  max_size_one_log_file_byte    = 0x02,   //< Максимальный размер одного файла логирования в байтах
  enable_store_call_place       = 0x03,   //< Флаг, контролирует фиксацию в файле место вызова (файл/функция/строка) функции логирования
  enable_log_events             = 0x04,   //< Флаг, подписаться на события и логировать их
  log_level                     = 0x05,   //< Уровень логирования из типа LogLevels
  enable_suppress_duplicate_msg = 0x06,   //< Флаг, подавлять дубликаты сообщений
  no_val                        = 0x1E,   //< Не определено, для общности Используется как сигнал отсутствия поля
  max_val                       = 0x1F    //< Граница значений данного типа для формирования статических массивов, проверки значения etc
};

const std::string& val2str (const LogVals& val);
LogVals            str2val (const std::string& str);

inline constexpr std::uint32_t
                 enum_to_raw (const LogVals& val)
{
  return U3_CAST_UINT32_FORCE (val);
}
}   // namespace libs::events_base::props::modules::log
