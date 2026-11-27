#pragma once
/**
\file       -module-events-includes-int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
*/
#include "../-modules-includes-int.hpp"
#include "sqlite3.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "mmedia/libs/utility/sqlite/sqlite-call-helper-funcs.hpp"
#include "appl/events-module-syn.hpp"
#include "appl/consts/module-events-const-vals.hpp"
#include "appl/impls/ievent-module-impl.hpp"

#if (U3_COMMERCIAL_PART == 1)
#  include "appl/impls/sqlite/sqlite-event-module-impl.hpp"
#endif

#include "appl/impls/test/test-event-module-impl.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG ::libs::ilink::consts::id_events_log
