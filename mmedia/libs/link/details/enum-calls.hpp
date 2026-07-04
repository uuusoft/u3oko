#pragma once
/**
\file       enum-calls.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_link
*/

namespace libs::link::details
{
/// Перечисление различных причин предназначения события
enum class Calls : std::uint32_t
{
  set      = 0x00,   //< По умолчанию. Например установка данных данного типа события
  request  = 0x01,   //< Запрос данных данного типа события
  answer   = 0x02,   //< Ответ с данными данного типа события
  generate = 0x03,   //< Запрос на генерацию события с пустыми данными. Например для последующий генерации актуализированной xml схемы
  unknown  = 0xFF    //< Не определенно для общности
};

auto to_string (const Calls& req) -> const std::string&;
auto to_request (const std::string& str) -> Calls;
}   // namespace libs::link::details
