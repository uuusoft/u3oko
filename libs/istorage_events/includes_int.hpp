//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes_int.hpp
\date       21.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      Внутренний интерфейс включения данного модуля.
*/
#include "mmedia/libs/events/includes.hpp"      //for events
#include "mmedia/libs/link/includes.hpp"
#include "mmedia/libs/core/includes.hpp"
#include "mmedia/libs/ievents/includes.hpp"

#include "includes.hpp"

#undef UUU_LOG_TAG
#define UUU_LOG_TAG "uuu_http_events"
