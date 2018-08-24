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
enum struct TypeRequestCall
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
to_str (const TypeRequestCall& _req)
{
  switch (_req)
    {
    case TypeRequestCall::set:
      return "set";
    case TypeRequestCall::request:
      return "request";
    case TypeRequestCall::answer:
      return "answer";
    case TypeRequestCall::generate:
      return "generate";
    default:
      UASSERT_SIGNAL ("unknown TypeRequestCall");
      break;
    }

  return "request";
}
/**
  \brief      Функция для преобразования строки в запрос.
  \param[in]  _str  строка.
  \return     запрос.
  */
inline const TypeRequestCall
to_request (const std::string& _str)
{
  if ("set" == _str)
    {
      return TypeRequestCall::set;
    }
  if ("request" == _str)
    {
      return TypeRequestCall::request;
    }
  if ("answer" == _str)
    {
      return TypeRequestCall::answer;
    }
  if ("generate" == _str)
    {
      return TypeRequestCall::generate;
    }

  UASSERT_SIGNAL ("unknow str TypeRequestCall");
  return TypeRequestCall::request;
}

}}}      // namespace libs::link::details
