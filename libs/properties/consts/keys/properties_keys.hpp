#pragma once
/**
\file       properties_keys.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_properties
\brief      Текстовые идентификаторы свойств (доступные в пределха всей системы).
*/

namespace libs { namespace properties { namespace consts { namespace keys {

using key_property_type = std::string;

const key_property_type shared_os_property   = "shared_os_property";        //< Идентификатор свойств ОС
const key_property_type specific_os_property = "specific_os_property";      //< Идентификатор свойств ОС специфичных для каждой из них.
const key_property_type links_property       = "links_property";            //< Идентификатор свойств связей между подсистемами.
const key_property_type demons_property      = "demons_property";           //< Идентификатор свойств интерфейсов различных сервисов (памяти, оптимизации и т.п.).

}}}}      // namespace libs::properties::consts::keys
