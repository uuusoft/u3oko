#pragma once
/**
\file       includes.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.05.2017

\project    u3_core_lib
*/
#include "utils/color.hpp"
#include "utils/ipos.hpp"
#include "utils/isize.hpp"
#include "utils/irect.hpp"

#include "utils/helpers/pos_funcs.hpp"
#include "utils/helpers/size_funcs.hpp"
#include "utils/helpers/rect_funcs.hpp"
#include "utils/helpers/color_funcs.hpp"

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
#include "events/video-buf-event.hpp"

#include "events/igui-events-register_events_in_archives.hpp"
