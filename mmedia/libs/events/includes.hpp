#pragma once
/**
file        includes.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       10.12.2016
\project    u3_events
\brief      Файл, определяет набор интерфейсов и типов для ядра.
*/
#include "enum-deeps.hpp"
#include "enum-property-usings.hpp"
#include "ievent.hpp"

#include "wrapers/iwrap-base-event.hpp"
#include "wrapers/isync-event.hpp"
#include "wrapers/irequest-event.hpp"
#include "wrapers/ianswer-event.hpp"
#include "wrapers/iseq-event.hpp"

#include "props/details/rect.hpp"

#include "buf/consts/events-buf-consts-vals.hpp"
#include "buf/event-bufs-info.hpp"

#include "io/ievents.hpp"

// EAI-REFACT remove exception
#include "mmedia/libs/iproperties/helpers/cast_events_funcs.hpp"   //  исключение.
#include "helpers/get-base-msg-helper-funcs.hpp"
#include "helpers/wrap-events-helper-funcs.hpp"

#include "events-register_events_in_archives.hpp"
