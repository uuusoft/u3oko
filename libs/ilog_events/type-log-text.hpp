#pragma once
/**
\file       type-log-text.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/

namespace libs { namespace ilog_events {
/**
\brief  Тип для идентификации части текста в сообщении логирования.
*/
enum struct TypeLogText
{
  subsys   = 0,      //< Подсистема, которая сгенерировала сообещение.
  text     = 1,      //< Текст сообщения (информационная часть).
  function = 2,      //< Функция подсистемы, которая сгенерировала сообщение.
  line     = 3       //< Строка в функции.
};

}}      // namespace libs::ilog_events
