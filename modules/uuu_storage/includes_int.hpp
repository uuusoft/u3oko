//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       includes_int.hpp
\date       23.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      Внутренний интерфейс включения данного модуля.
*/
#include "../includes_int.hpp"
#include "includes.hpp"

#include "appl/syn_types.hpp"
#include "appl/consts/vals.hpp"
#include "appl/impl/state-impls-type.hpp"
#include "appl/impl/id-storage-chunk.hpp"
#include "appl/impl/istorage-impl.hpp"
#include "appl/impl/iindexer-impl.hpp"
#include "appl/impl/indexer/test/vals.hpp"
#include "appl/impl/indexer/test/state-record.hpp"
#include "appl/impl/indexer/test/state-stream.hpp"
#include "appl/impl/indexer/test/state-object.hpp"
#include "appl/impl/indexer/test/state-test-indexer.hpp"
#include "appl/impl/indexer/test/test-indexer-impl.hpp"
#include "appl/impl/storage/test/consts/vals.hpp"
#include "appl/impl/storage/test/index-data-file-state.hpp"
#include "appl/impl/storage/test/stored-info-seance.hpp"
#include "appl/impl/storage/test/runtime-info-seance.hpp"
#include "appl/impl/storage/test/test-storage-impl.hpp"
#include "appl/impl/storage/test/helpers/save2file-functs.hpp"
#include "appl/storage-module.hpp"
#include "appl/factory-impl-functs.hpp"

#undef UUU_LOG_TAG
#define UUU_LOG_TAG ::libs::ilink::consts::id_storage
