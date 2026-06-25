#pragma once
/**
\file       uids2bytes_funcs.hpp
\brief      Некоторые вспомогтальные системыне функции
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2016
\project    u3_helpers_lib
*/

namespace libs::helpers::uids::helpers
{
/// Функция возращает число байт, на пиксель, которое соответствует данному формату
auto get_count_bytes_from_format (const ::libs::helpers::utils::cuuid&) -> std::uint32_t;
auto get_count_bytes_from_format (const libs::helpers::uids::minor::id_val&) -> std::uint32_t;

/// Функция возращает коэффициент масштабирования по вертикали, которое соответствует данному формату. Т.к. ряд форматов хранят пиксели распределенно
auto get_hkoeff_from_format (const ::libs::helpers::utils::cuuid&) -> std::uint32_t;
auto get_hkoeff_from_format (const libs::helpers::uids::minor::id_val&) -> std::uint32_t;

/// Функция возращает читаемое имя для известных форматов в виде guid
auto get_readable_name (const ::libs::helpers::utils::cuuid&) -> const std::string&;
auto get_readable_name (const libs::helpers::uids::minor::id_val&) -> const std::string&;

/// Функция возращает признак сжатости форматов
bool is_raw_format (const ::libs::helpers::utils::cuuid&);
bool is_raw_format (const libs::helpers::uids::minor::id_val&);

auto guid2fourcc (const libs::helpers::utils::cuuid&) -> std::uint32_t;
auto idval2fourcc (const libs::helpers::uids::minor::id_val&) -> std::uint32_t;

auto fourcc2guid (std::uint32_t) -> const libs::helpers::utils::cuuid&;
auto fourcc2idval (std::uint32_t) -> libs::helpers::uids::minor::id_val;
}   // namespace libs::helpers::uids::helpers
