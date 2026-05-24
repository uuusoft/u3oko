/**
\file       generics-devents-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.07.2017
\project    u3_devents_dlls
\brief      Модуль для преобразования идентификатора в нативный объект "событие системы"
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "generics-devents-includes_int.hpp"
#include "impl/events-impl.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::events::io::IEvents::raw_ptr
create_impl_vdd_devents ()
{
  static ::dlls::devents::impl::EventsImpl ret;
  return &ret;
}
