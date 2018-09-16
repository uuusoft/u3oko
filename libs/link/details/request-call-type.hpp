//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-request-call.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace details {
/**
\brief  Перечисление различных причин предназначения события.
*/
enum struct RequestCallType
{
  set      = 0,      //< По умолчанию. Например установка данных данного типа события.
  request  = 1,      //< Запрос данных данного типа события.
  answer   = 2,      //< Ответ с данными данного типа события.
  generate = 3       //< Запрос на генерацию события с пустыми данными. Например для последующий генерации актуализированной xml схемы.
};
/**
\brief      Функция для преобразования запроса в строку.
\param[in]  _req  запрос.
\return     строка запроса.
*/
inline std::string
to_str (const RequestCallType& _req)
{
  switch (_req)
    {
    case RequestCallType::set:
      return "set";
    case RequestCallType::request:
      return "request";
    case RequestCallType::answer:
      return "answer";
    case RequestCallType::generate:
      return "generate";
    default:
      XULOG_WARNING( "unknown type RequestCallType, " << UUU_ICAST_INT(_req) );
      break;
    }
  return "request";
}
/**
\brief      Функция для преобразования строки в запрос.
\param[in]  _str  строка.
  \return     запрос.
*/
inline const RequestCallType
to_request (const std::string& _str)
{
  if ("set" == _str)
    {
      return RequestCallType::set;
    }
  if ("request" == _str)
    {
      return RequestCallType::request;
    }
  if ("answer" == _str)
    {
      return RequestCallType::answer;
    }
  if ("generate" == _str)
    {
      return RequestCallType::generate;
    }
  XULOG_WARNING( "unknown text RequestCallType, " << _str );
  return RequestCallType::request;
}

}}}      // namespace libs::link::details
