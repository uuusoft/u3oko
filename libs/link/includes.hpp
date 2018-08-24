#pragma once
/**
file        includes.hpp
\brief      Файл, определяет набор интерфейсов и типов для ядра.
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       10.12.2016.
\copyright  www.uuusoft.com
\project    uuu_link
\brief      Внешний интерфейс включения модуля.
*/
#include "vals.hpp"
#include "vals_size.hpp"
#include "vals_text.hpp"

#include "details/type-link-modules.hpp"
#include "details/type-run-code.hpp"
#include "details/ETypeSide.hpp"
#include "details/ETypeActivity.hpp"
#include "details/type-sync-call.hpp"
#include "details/type-request-call.hpp"
#include "details/ESeqCall.hpp"

#include "mem/iblock-mem.hpp"
#include "mem/ihandler-mem.hpp"
#include "mem/imem.hpp"

#include "syn_types.hpp"
#include "create-info.hpp"
#include "state-process-event.hpp"
#include "type-destroy-link.hpp"
#include "ilink.hpp"
#include "ilink-creator.hpp"

#include "appl/init-application.hpp"
#include "appl/iapplication.hpp"
#include "appl/iapplication-proxy.hpp"
