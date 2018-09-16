#pragma once
/**
\file       request-call-type.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_link
\brief      empty brief
*/

namespace libs { namespace link { namespace details {
/**
\brief  Перечисление различных варинтов запуска кода.
*/
enum struct RunCodeType
{
  usual = 0,      //< По умолчанию.
  dll   = 1,      //< Запускать в том же процессе как dll/so.
  appl  = 2       //< Запускать в другом процессе.
};
/**
\brief  ???
*/
inline std::string
to_str (const RunCodeType& _val)
{
  switch (_val)
    {
    case RunCodeType::usual:
      return "usual";
    case RunCodeType::dll:
      return "dll";
    case RunCodeType::appl:
      return "appl";
    }
  XULOG_WARNING( "unknown type RunCodeType, " << UUU_ICAST_INT(_val) );
  return "unknown";
}

}}}      // namespace libs::link::details
