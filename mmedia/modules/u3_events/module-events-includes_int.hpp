#pragma once
/**
\file       module-events-includes_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_module_events
*/
#include "../modules-includes_int.hpp"

#ifndef U3_DBG_EXTERNAL_LIB_SKIP_SQLITE
#  include "sqlite3.h"
#  include "mmedia/libs/helpers/sqlite/sqlite-call-helper-funcs.hpp"
#endif

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG ::libs::ilink::consts::id_events_log
