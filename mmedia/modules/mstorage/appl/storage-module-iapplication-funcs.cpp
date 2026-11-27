/**
\file       storage-module-iapplication-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.07.2018
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../-module-storage-includes-int.hpp"
#include "storage-module.hpp"

namespace modules::mstorage::appl
{
void
StorageModule::init_appl_data_int ()
{
  // ничего не делаем - данные должны быть инициализрованы один раз в основном модуле (u3oko/u3yduff/etc)
}
}   // namespace modules::mstorage::appl
