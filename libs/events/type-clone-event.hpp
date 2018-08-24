//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-clone-event.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/

namespace libs { namespace events {
/**
  \brief  Перечисление различных способов клонирования события.
  */
enum struct TypeCloneEvent
{
  empty = 0,      //< Клонирование пустого события, у копии совпадает только тип.
  full  = 1       //< Глубокое клонирование события, у коппи совпадает и тип, и значения полей.
};

}}      // namespace libs::events
