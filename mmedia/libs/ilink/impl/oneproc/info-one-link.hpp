#pragma once
/**
\file       info-one-link.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/

namespace libs::ilink::impl::oneproc
{
/// Структура для группировки данных для одного двухсторннего канала передачи данных
/// Как между процессами, так и внутри одного
struct InfoOneLink {
  /// Конструктор по умолчанию
  InfoOneLink () = default;

  LinkImplOneProcInt::ptr       impl_;     //< Настоящая реализация канала передачи, которая разделяется между всеми сторонами данного канала
  ::libs::link::ILink::weak_ptr server_;   //< Активные стороны данного канала. У каждого канала передачи, есть две стороны, сервер и клиенты
  ::libs::link::ILink::weak_ptr client_;   //< Активные стороны данного канала. У каждого канала передачи, есть две стороны, сервер и клиенты
};
}   // namespace libs::ilink::impl::oneproc
