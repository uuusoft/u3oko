/**
\file       storage-module-iapplication-funcs.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.07.2018
\project    u3_module_storage
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../module-storage-includes_int.hpp"
#include "storage-module.hpp"

namespace modules::uuu_storage::appl
{
void
StorageModule::init_appl_data_int ()
{
  // ничего не делаем - данные должны быть инициализрованы один раз в основном модуле (u3oko/u3yduff/etc)
}
}   // namespace modules::uuu_storage::appl
