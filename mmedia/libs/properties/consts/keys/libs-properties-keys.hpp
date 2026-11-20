#pragma once
/**
\file       libs-properties-keys.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\brief      Текстовые идентификаторы свойств (доступные в пределха всей системы)
*/

namespace libs::properties::consts::keys
{
using key_property_type            = std::string_view;
using persistent_key_property_type = std::string;

inline constexpr std::string_view shared_os_property   = "shared_os_property";     //< Идентификатор свойств ОС
inline constexpr std::string_view specific_os_property = "specific_os_property";   //< Идентификатор свойств ОС специфичных для каждой из них
inline constexpr std::string_view links_property       = "links_property";         //< Идентификатор свойств связей между подсистемами
inline constexpr std::string_view demons_property      = "demons_property";        //< Идентификатор свойств интерфейсов различных сервисов (памяти, оптимизации etc)
}   // namespace libs::properties::consts::keys
