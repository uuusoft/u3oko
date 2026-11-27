/**
\file       generics-devents-main.cpp
\author     Erashov Anton erashov2026@proton.me
\date       21.07.2017
\brief      Модуль для преобразования идентификатора в нативный объект "событие системы"
*/
#include "-devents-includes-int.hpp"
#include "impl/events-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto
create_impl_vdd_devents () -> ::libs::events::io::IEvents::raw_ptr
{
  static ::utils::devents::impl::EventsImpl ret;
  return &ret;
}
