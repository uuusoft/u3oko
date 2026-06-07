#pragma once
/**
\file       video-sender-includes_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_video_sender_dll
*/
#include "../../dlls-includes_int.hpp"
#include "mmedia/libs/igui_events/includes.hpp"
#include "mmedia/libs/istorage_events/istorage-events-includes.hpp"
#include "mmedia/libs/ihttp_events/includes.hpp"
#include "mmedia/modules/mgui/io/includes.hpp"
#include "mmedia/modules/mlog/module-log-includes.hpp"
#include "mmedia/libs/ilink/libs-ilink-includes.hpp"

#include "video-sender-syn.hpp"
#include "consts/video-sender-const-vals.hpp"
#include "video-sender-info-filter.hpp"
#include "iimpl-sender.hpp"
#include "impl2http/impl2http.hpp"
#include "impl2storage/impl2storage-syn.hpp"
#include "impl2storage/impl2storage.hpp"
#include "impl2gui/impl2gui.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG "u3videosender          "
