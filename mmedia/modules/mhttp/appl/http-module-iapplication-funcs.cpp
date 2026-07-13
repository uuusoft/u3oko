/**
\file       http-module-iapplication-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.08.2018
\project    mhttp
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../module-http-includes_int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "http-module-syn.hpp"
#include "http-module.hpp"

namespace modules::mhttp::appl
{
void
HttpModule::init_appl_data_int ()
{
  // ничего не делаем - данные должны быть инициализрованы один раз в основном модуле (u3oko/u3yduff/etc)
}
}   // namespace modules::mhttp::appl
