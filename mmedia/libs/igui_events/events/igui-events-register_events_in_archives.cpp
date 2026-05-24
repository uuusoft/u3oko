/**
\file       igui-events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    uuu_igui_evenets
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "igui-events-register_events_in_archives.hpp"

namespace libs::igui_events::events
{
void
register_events_in_archives ()
{
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::BaseGUIEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::CommandCodeEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::ExitApplEvent);
  // U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE( ::libs::igui_events::events::MemBlockEvent );
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::MouseButtonDownEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::MouseButtonUpEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::SizeChangedEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::igui_events::events::UpdateDrawEvent);
  // U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE( ::libs::igui_events::events::VideoBufEvent );
}
}   // namespace libs::igui_events::events
