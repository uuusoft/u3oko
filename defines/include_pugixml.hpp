//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       include_pugixml.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
*/
#include "sdks/pugixml/src/pugixml.hpp"

namespace base_functs { namespace xml {
//  syn
using node = pugi::xml_node;
using itn  = pugi::xml_named_node_iterator;
using ritn = pugi::xml_object_range<base_functs::xml::itn>;

}}      // namespace base_functs::xml
