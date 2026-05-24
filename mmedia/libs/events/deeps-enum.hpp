#pragma once
/**
\file       deeps-enum.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/

namespace libs::events
{
/// Перечисление различных способов клонирования события
enum class Deeps : std::uint32_t
{
  empty   = 0x00,   //< Клонирование пустого события, у копии совпадает только тип
  full    = 0x01,   //< Глубокое клонирование события, у копии совпадает и тип, и значения полей
  unknown = 0xFF    //< Не определенно для общности
};

const std::string& to_string (const Deeps& val);
}   // namespace libs::events
