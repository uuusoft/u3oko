/**
\file       events-module-iapplication-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    mevents
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-events-includes_int.hpp"
#include "consts/module-events-const-vals.hpp"
#include "events-module-syn.hpp"
#include "events-module.hpp"

namespace modules::mevents::appl
{
void
EventsModule::init_appl_data_int ()
{
  // ничего не делаем - данные должны быть инициализрованы один раз в основном модуле (u3oko/u3yduff/etc)
}
}   // namespace modules::mevents::appl
