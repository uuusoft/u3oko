/**
\file       http-module-iapplication-funcs.cpp
\author     Erashov Anton erashov2026@proton.me
\date       23.08.2018
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "-http-module-includes-int.hpp"
#include "mmedia/dlls/terminals/video_sender/consts/video-sender-const-vals.hpp"
#include "-http-module-syn.hpp"
#include "http-module.hpp"

namespace modules::mhttp::appl
{
void
HttpModule::init_appl_data_int ()
{
  // ничего не делаем - данные должны быть инициализрованы один раз в основном модуле (u3oko/u3yduff/etc)
}
}   // namespace modules::mhttp::appl
