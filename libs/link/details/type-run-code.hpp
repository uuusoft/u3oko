#pragma once
/**
\file       type-run-code.hpp
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
enum struct TypeRunCode
{
  usual = 0,      //< По умолчанию.
  dll   = 1,      //< Запускать в том же процессе как dll/so.
  appl  = 2       //< Запускать в другом процессе.
};


inline std::string
to_str (const TypeRunCode& _val)
{
  switch (_val)
    {
    case TypeRunCode::usual:
      return "usual";
    case TypeRunCode::dll:
      return "dll";
    case TypeRunCode::appl:
      return "appl";
    }
  return "unknown";
}

}}}      // namespace libs::link::details
