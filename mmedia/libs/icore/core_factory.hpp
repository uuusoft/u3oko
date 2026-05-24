#pragma once
/**
\file       core_factory.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       22.12.2016
\project    u3_icore_lib
*/

namespace libs::icore
{
/// Функция создания реализации ядра. Пока только одна локальная версия
/// \return   объект, при успехе
inline ::libs::core::ICore::ptr
create ()
{
  return ::libs::core::ICore::ptr (new ::libs::icore::impl::var1::Core);
}
}   // namespace libs::icore
