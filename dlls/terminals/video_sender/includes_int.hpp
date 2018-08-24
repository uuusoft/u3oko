//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes_int.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      Внутренний интерфейс включения данного модуля.
*/
#include "../../includes_int.hpp"
#include "mmedia/libs/igui_events/includes.hpp"
#include "mmedia/libs/istorage_events/includes.hpp"
#include "mmedia/libs/ihttp_events/includes.hpp"
#include "mmedia/modules/uuu_gui/io/includes.hpp"
#include "mmedia/modules/uuu_log/includes.hpp"
#include "mmedia/libs/ilink/includes.hpp"

#include "syn_types.hpp"
#include "consts/vals.hpp"
#include "info-filter.hpp"
#include "iimpl-sender.hpp"
#include "impl2http/impl2http.hpp"
#include "impl2storage/syn.hpp"
#include "impl2storage/impl2storage.hpp"
#include "impl2gui/impl2gui.hpp"

#undef UUU_LOG_TAG
#define UUU_LOG_TAG "uuu_video_sender"
