/**
\file       events-msg-register-events-archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-msg-includes_int.hpp"
#include "events-msg-register_events_in_archives.hpp"

namespace libs::events_msg::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_msg::events::BaseEventsMsg > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_msg::events::WrapperEventsEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_msg::events::AddEvent2EventsMsg > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_msg::events::GetEventsFromBase > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_msg::events::UpdateListenerEventsMsg > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_msg::events::GetDataGraphsEventsMsg > ();
}
}   // namespace libs::events_msg::events
