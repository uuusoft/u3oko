#pragma once
/**
\file       type-log-status.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/
//old shit
namespace libs { namespace ilog_events {

#if 0
  /**
  \brief  Тип сообщения о логировании события.
  */
  enum struct EType
  {    
    usual                 = 0,  //< По умолчанию, не определенно.    
    info                  = 1,  //<Информационное сообщение.    
    change_state_subsys   = 2,  //<Сообщение о изменение состояния работы подсистемы логирования.    
    exception             = 3,  //<Сообщение о исключении.    
    invalid_state         = 4 //<Сообщение о внештатной ситуации.
  };
#endif

}}      // namespace libs::ilog_events
