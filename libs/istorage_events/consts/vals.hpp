#pragma once
/**
\file       vals.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/

namespace libs { namespace istorage_events { namespace consts {

const stream_id_type empty_stream_id (::boost::uuids::nil_uuid ());      //< Значение пустого (не инициализированного) идентификатора потока.
const std::string    empty_object_id = "";                               //< Значение пустого идентификатора объекта в потоке.

}}}      // namespace libs::istorage_events::consts
