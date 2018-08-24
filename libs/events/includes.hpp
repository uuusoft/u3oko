#pragma once
/**
file        includes.hpp
\brief      Файл, определяет набор интерфейсов и типов для ядра.
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       10.12.2016.
\copyright  www.uuusoft.com
\project    uuu_events
\brief      Внешний интерфейс включения модуля.
*/
#include "type-clone-event.hpp"
#include "using-state-event.hpp"
#include "ievent.hpp"

#include "wrapers/iwrap-base-event.hpp"
#include "wrapers/isync-event.hpp"
#include "wrapers/irequest-event.hpp"
#include "wrapers/ianswer-event.hpp"
#include "wrapers/iseq-event.hpp"

#include "props/details/rect.hpp"

#include "buff-event-info.hpp"

#include "serialize_type_to_archive_define.hpp"
#include "make_fake_objs_this_type_defines.hpp"

#include "mmedia/libs/iproperties/helpers/cast_events_functs.hpp"      //  исключение.
#include "helpers/get_base_msg_funct.hpp"
#include "helpers/wrap_events_functs.hpp"
#include "helpers/convert_event2string_funct.hpp"

#include "io/ievents.hpp"
#include "io/ievents-proxy.hpp"

#include "register_events_in_archives.hpp"
