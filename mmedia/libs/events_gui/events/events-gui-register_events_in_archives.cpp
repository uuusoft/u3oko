/**
\file       events-gui-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_gui
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "events-gui-register_events_in_archives.hpp"

namespace libs::events_gui::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_gui::events::BaseGUIEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_gui::events::CommandCodeEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_gui::events::ExitApplEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_gui::events::MouseButtonDownEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_gui::events::MouseButtonUpEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_gui::events::SizeChangedEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_gui::events::UpdateDrawEvent > ();
}
}   // namespace libs::events_gui::events
