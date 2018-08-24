#pragma once
/**
\file       includes.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.05.2017
\copyright  www.uuusoft.com
\project    uuu_core
\brief      Внешний интерфейс включения модуля.
*/
#include "utils/color.hpp"
#include "utils/ipos.hpp"
#include "utils/isize.hpp"
#include "utils/irect.hpp"

#include "utils/helpers/pos_functs.hpp"
#include "utils/helpers/size_functs.hpp"
#include "utils/helpers/rect_functs.hpp"
#include "utils/helpers/color_functs.hpp"

#include "utils/impl/info.hpp"
#include "utils/impl/pos.hpp"
#include "utils/impl/size.hpp"
#include "utils/impl/rect.hpp"

#include "events/type-events.hpp"
#include "events/type-mouse-button.hpp"

#include "events/base-gui-event.hpp"
#include "events/update-draw-event.hpp"
#include "events/size-changed-event.hpp"
#include "events/command-code-event.hpp"
#include "events/mouse-button-down-event.hpp"
#include "events/mouse-button-up-event.hpp"
#include "events/exit-appl-event.hpp"
#include "events/mem-block-event.hpp"
#include "events/video-buff-event.hpp"

#include "events/register_events_in_archives.hpp"
