#pragma once
/**
\file       action-for-process-log.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       09.09.2018
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/

namespace libs { namespace ilog_events { namespace events {
/**
\brief  Перечисление различных действий, который можно произвести над списком сессий логирования
*/
enum struct ActionForProcessLog
{
  get_raw_log = 0      //< Получить указанный список сессий логирования. Гарантируется упорядоченность по времени списка логирования, т.е. последний элемент это текущая сессия логирования.
  //get_zip_sessions      = 1 //< Получить сжатый в архив указанный список сессий логирования. Гарантируется упорядоченность по времени списка логирования, т.е. последний элемент это текущая сессия логирования.
};
/**
\brief  
*/
inline std::string
to_str (const ActionForProcessLog& _act)
{
  switch (_act)
    {
    case ActionForProcessLog::get_raw_log:
      return "get raw log";
    }
  XULOG_WARNING ("unknown type ActionForProcessLog, " << UUU_ICAST_INT (_act));
  return "unknown type";
}

}}}      // namespace libs::ilog_events::events
