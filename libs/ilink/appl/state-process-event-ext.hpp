//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       state-process-event-ext.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      Файл объявления типа хранения состония обработки события внутри основного модуля.
*/

namespace libs { namespace ilink { namespace appl {
/**
\brief  Структура для расширения базового типа необходимим свойствами  для хранения состояния обработки события.
*/
struct StateProcessEventExt : public ::libs::link::StateProcessEvent
{
  StateProcessEventExt ()
  {}

  ~StateProcessEventExt ()
  {}

  void
  reset ()
  {
    super::reset ();
    source_.reset ();
    dest_.reset ();
    return;
  }

  ILink::ptr source_;      //< Источник события. Используется для завершения транзакции.
  ILink::ptr dest_;        //< Получатель события. Используется для его обработки и формирования результат.


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::link::StateProcessEvent);
};

}}}      // namespace libs::ilink::appl
