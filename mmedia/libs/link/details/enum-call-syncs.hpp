#pragma once
/**
\file       enum-call-syncs.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_link
\brief      Объявление типа (с точки зрения синхронизации) посылки сообщения
*/

namespace libs::link::details
{
/// Перечисление различных способов синхронизации при передачи сообщения через связь
enum class CallSyncs : std::uint32_t
{
  async   = 0x00,   //< Асинхронный способ передачи сообщения
  sync    = 0x01,   //< Cинхронный способ передачи сообщения
  unknown = 0xFF    //< Не определенно для общности
};

const std::string& to_string (const CallSyncs& val);
}   // namespace libs::link::details
