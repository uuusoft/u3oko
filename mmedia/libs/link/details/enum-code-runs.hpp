#pragma once
/**
\file       enum-code-runs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.11.2016
\project    u3_link
*/

namespace libs::link::details
{
/// Перечисление различных варинтов запуска кода
enum class CodeRuns : std::uint32_t
{
  usual   = 0x00,   //< По умолчанию
  dll     = 0x01,   //< Запускать в том же процессе как dll/so
  appl    = 0x02,   //< Запускать в другом процессе
  unknown = 0xFF    //< Не определенно для общности
};

const std::string& to_string (const CodeRuns& val);
}   // namespace libs::link::details
