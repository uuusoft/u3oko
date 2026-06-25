#pragma once
/**
\file       libs-properties-keys.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_properties_libs
\brief      Текстовые идентификаторы свойств (доступные в пределха всей системы)
*/

namespace libs::properties::consts::keys
{
using key_property_type = std::string;

extern const key_property_type shared_os_property;     //< Идентификатор свойств ОС
extern const key_property_type specific_os_property;   //< Идентификатор свойств ОС специфичных для каждой из них
extern const key_property_type links_property;         //< Идентификатор свойств связей между подсистемами
extern const key_property_type demons_property;        //< Идентификатор свойств интерфейсов различных сервисов (памяти, оптимизации etc)
}   // namespace libs::properties::consts::keys
