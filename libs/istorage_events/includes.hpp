#pragma once
/**
\file       includes.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       22.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      Внешний интерфейс включения модуля.
*/
#include "base_types.hpp"
#include "consts/vals.hpp"
#include "type-object-id.hpp"
#include "type-update-stream.hpp"
#include "type-direction-stream.hpp"
#include "type-time-stream.hpp"
#include "time-stream.hpp"
#include "type-action-stream.hpp"

#include "events/base-storage-event.hpp"
#include "events/wrapper-storage-event.hpp"
#include "events/mem-resource-storage-event.hpp"
#include "events/get-runtime-info.hpp"
#include "events/get-objects.hpp"
#include "events/update-stream.hpp"
#include "events/read-data.hpp"
#include "events/write-data.hpp"
#include "events/get-statistic-info.hpp"

#include "events/register_events_in_archives.hpp"
