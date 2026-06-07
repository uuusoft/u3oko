#pragma once
/**
\file       enum-property-usings.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    mevents
\brief      Объявление состояний "использование" свойства
*/

namespace libs::events
{
/// Перечисление различных состояний, в которых может находится свойство
enum class PropertyUsings : std::uint32_t
{
  disabled  = 0x00,   //< Свойство отключено
  enabled   = 0x01,   //< Свойство включено
  automatic = 0x02,   //< Свойство используется автоматически
  unknown   = 0xFF    //< Не определенно для общности
};

const std::string& to_string (const PropertyUsings& val);
}   // namespace libs::events
