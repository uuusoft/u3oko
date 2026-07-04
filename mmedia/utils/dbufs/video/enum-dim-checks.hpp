#pragma once
/**
\file       enum-dim-checks.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_dbufs
*/

namespace utils::dbufs::video
{
/// Перечисление различных режимов проверок при использовании буфера с данными
enum class DimChecks : std::uint32_t
{
  disable = 0x00,   //< Отключить автоматическую проверку границ
  enable  = 0x01,   //< Включить автоматическую проверку границ буфера
  unknown = 0xFF    //< Не определенно для общности
};
}   // namespace utils::dbufs::video
