#pragma once
/**
file        libs-link-includes.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       10.12.2016
\project    u3_link
\brief      Файл, определяет набор интерфейсов и типов для ядра
*/
#include "consts/libs-link-time-vals.hpp"
#include "consts/libs-link-size-vals.hpp"
#include "consts/libs-link-text-vals.hpp"

#include "details/enum-module-links.hpp"
#include "details/enum-code-runs.hpp"
#include "details/enum-call-syncs.hpp"
#include "details/enum-calls.hpp"

#include "mem/iblock-fake-mem.hpp"
#include "mem/ihandler-mem.hpp"
#include "mem/imem.hpp"

#include "libs-link-syns.hpp"
#include "create-info.hpp"
#include "state-process-event.hpp"
#include "destroy-link-type.hpp"
#include "ilink.hpp"
#include "ilink-creator.hpp"

#include "appl/init-application.hpp"
#include "appl/iapplication.hpp"
#include "appl/iapplication-proxy.hpp"
