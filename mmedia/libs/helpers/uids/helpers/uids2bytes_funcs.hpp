#pragma once
/**
\file       uids2bytes_funcs.hpp
\brief      Некоторые вспомогтальные системыне функции
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2016
\project    u3_helpers_lib
*/

namespace libs::helpers::uids::helpers
{
/// Функция возращает число байт, на пиксель, которое соответствует данному формату
std::uint32_t get_count_bytes_from_format (const ::libs::helpers::utils::cuuid&);
std::uint32_t get_count_bytes_from_format (const libs::helpers::uids::minor::id_val&);

/// Функция возращает коэффициент масштабирования по вертикали, которое соответствует данному формату. Т.к. ряд форматов хранят пиксели распределенно
std::uint32_t get_hkoeff_from_format (const ::libs::helpers::utils::cuuid& format);
std::uint32_t get_hkoeff_from_format (const libs::helpers::uids::minor::id_val& format);

/// Функция возращает читаемое имя для известных форматов в виде guid
const std::string& get_readable_name (const ::libs::helpers::utils::cuuid& format);
const std::string& get_readable_name (const libs::helpers::uids::minor::id_val& format);

/// Функция возращает признак сжатости форматов
bool is_raw_format (const ::libs::helpers::utils::cuuid& format);
bool is_raw_format (const libs::helpers::uids::minor::id_val& format);

std::uint32_t guid2fourcc (const libs::helpers::utils::cuuid& guid);
std::uint32_t idval2fourcc (const libs::helpers::uids::minor::id_val& par);

const libs::helpers::utils::cuuid& fourcc2guid (std::uint32_t par);
libs::helpers::uids::minor::id_val fourcc2idval (std::uint32_t par);
}   // namespace libs::helpers::uids::helpers
