//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes_int.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_core
\brief      Внутренний интерфейс включения данного модуля.
*/
#include "mmedia/libs/events/includes.hpp"      //for events
#include "mmedia/libs/link/includes.hpp"
#include "mmedia/libs/core/includes.hpp"
#include "mmedia/libs/ievents/includes.hpp"
#include "mmedia/modules/uuu_gui/gui_defines.hpp"
#include "includes.hpp"

#undef UUU_LOG_TAG
#define UUU_LOG_TAG "uuu_gui_events"
