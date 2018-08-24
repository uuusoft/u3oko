//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       type-sync-call.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_link
\brief      Объявление типа (с точки зрения синхронизации) посылки сообщения.
*/

namespace libs { namespace link { namespace details {
/**
  \brief  Перечисление различных способов синхронизации при передачи сообщения через связь.
  */
enum struct TypeSyncCall
{
  async = 0,      //< Асинхронный способ передачи сообщения.
  sync  = 1       //< Cинхронный способ передачи сообщения.
};


inline std::string
to_str (const TypeSyncCall& _val)
{
  switch (_val)
    {
    case TypeSyncCall::async:
      return "async";
    case TypeSyncCall::sync:
      return "sync";
    }
  return "unknown";
}

}}}      // namespace libs::link::details
