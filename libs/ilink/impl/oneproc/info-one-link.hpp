//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       info-one-link.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace impl { namespace oneproc {
/**
\brief  Структура для группировки данных для одного двухсторннего канала передачи данных.
        Как между процессами, так и внутри одного.
*/
struct InfoOneLink
{
  /// Конструктор по умолчанию.
  InfoOneLink ()
  {}

  LinkImplOneProcInt::ptr       impl_;        //< Настоящая реализация канала передачи, которая разделяется между всеми сторонами данного канала.
  ::libs::link::ILink::weak_ptr server_;      //< Активные стороны данного канала. У каждого канала передачи, есть две стороны, сервер и клиенты.
  ::libs::link::ILink::weak_ptr client_;      //< Активные стороны данного канала. У каждого канала передачи, есть две стороны, сервер и клиенты.
};

}}}}      // namespace libs::ilink::impl::oneproc
