#pragma once
/**
\file       module-events-includes_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "../modules-includes_int.hpp"
#include "sqlite3.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "mmedia/libs/helpers/sqlite/sqlite-call-helper-funcs.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG ::libs::ilink::consts::id_events_log
