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

#include "details/link-modules-type.hpp"
#include "details/run-code-type.hpp"
#include "details/sync-call-type.hpp"
#include "details/request-call-type.hpp"

#include "mem/iblock-mem.hpp"
#include "mem/ihandler-mem.hpp"
#include "mem/imem.hpp"

#include "syns.hpp"
#include "create-info.hpp"
#include "state-process-event.hpp"
#include "destroy-link-type.hpp"
#include "ilink.hpp"
#include "ilink-creator.hpp"

#include "appl/init-application.hpp"
#include "appl/iapplication.hpp"
#include "appl/iapplication-proxy.hpp"
