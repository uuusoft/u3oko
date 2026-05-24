#pragma once
/**
\file       module-storage-includes_int.hpp
\date       23.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_module_storage
*/
#include "../modules-includes_int.hpp"
#include "module-storage-includes.hpp"

#ifndef U3_DBG_EXTERNAL_LIB_SKIP_SQLITE
#  include "sqlite3.h"
#endif

#include "mmedia/libs/helpers/sqlite/sqlite-call-helper-funcs.hpp"

#include "appl/storage-module-syn.hpp"
#include "appl/consts/storage-module-const-vals.hpp"
#include "appl/impl/impls-runs-enum.hpp"
#include "appl/impl/id-storage-chunk.hpp"
#include "appl/impl/istorage-impl.hpp"
#include "appl/impl/iindexer-impl.hpp"

#include "appl/impl/indexer/test/test-indexer-vals.hpp"
#include "appl/impl/indexer/test/state-record.hpp"
#include "appl/impl/indexer/test/state-stream.hpp"
#include "appl/impl/indexer/test/state-object.hpp"
#include "appl/impl/indexer/test/state-test-indexer.hpp"
#include "appl/impl/indexer/test/test-indexer-impl.hpp"

#include "appl/impl/indexer/sqlite/module-storage-impl-indexer-const-vals.hpp"
#include "appl/impl/indexer/sqlite/state-record.hpp"
#include "appl/impl/indexer/sqlite/state-stream.hpp"
#include "appl/impl/indexer/sqlite/state-object.hpp"
#include "appl/impl/indexer/sqlite/state-sqlite-indexer.hpp"
#include "appl/impl/indexer/sqlite/sqlite-indexer-impl.hpp"

#include "appl/impl/storage/test/consts/module-storage-impl-storage-const-vals.hpp"
#include "appl/impl/storage/test/index-data-file-state.hpp"
#include "appl/impl/storage/test/stored-info-seance.hpp"
#include "appl/impl/storage/test/runtime-info-seance.hpp"
#include "appl/impl/storage/test/test-storage-impl.hpp"
#include "appl/impl/storage/test/helpers/save2file-funcs.hpp"

#include "appl/storage-module.hpp"
#include "appl/storage-module-factory-impl-funcs.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG ::libs::ilink::consts::id_storage_log
