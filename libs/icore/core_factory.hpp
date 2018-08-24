#pragma once
/**
\file       core_factory.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       22.12.2016.
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      Обяъвление функции выбора и создания реализации ядра.
*/

namespace libs { namespace icore {
/**
  \brief    Функция создания реализации ядра. Пока только одна локальная версия.
  \return   объект, при успехе.
  */
inline ::libs::core::ICore::ptr
create ()
{
  return ::libs::core::ICore::ptr (new ::libs::icore::impl::var1::Core);
}

}}      // namespace libs::icore
