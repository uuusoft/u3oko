/**
\file       log-module-iapplication-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../-module-log-includes-int.hpp"
#include "log-module.hpp"

namespace modules::mlog::appl
{
void
LogModule::init_appl_data_int ()
{
  // ничего не делаем - данные должны быть инициализрованы один раз в основном модуле (u3oko/u3yduff/etc)
}
}   // namespace modules::mlog::appl
