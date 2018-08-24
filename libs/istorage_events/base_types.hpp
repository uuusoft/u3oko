#pragma once
/**
\file       base_types.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events {
//  ext types
using path_id_type   = std::string;                        //< Тип идентификатора пути.
using stream_id_type = ::libs::helpers::utils::cuuid;      //< Тип идентификатора потока. Случайное значение.

}}      // namespace libs::istorage_events
