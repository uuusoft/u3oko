/**
\file       igui-events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_igui_events
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
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::igui_events::events::BaseGUIEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::igui_events::events::CommandCodeEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::igui_events::events::ExitApplEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::igui_events::events::MouseButtonDownEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::igui_events::events::MouseButtonUpEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::igui_events::events::SizeChangedEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::igui_events::events::UpdateDrawEvent > ();
}
}   // namespace libs::igui_events::events
