/**
\file       ievents-events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../ievents-events-includes_int.hpp"
#include "ievents-events-register_events_in_archives.hpp"

namespace libs::ievents_events::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents_events::events::BaseEventsEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents_events::events::WrapperEventsEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents_events::events::AddEvent2Base > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents_events::events::GetEventsFromBase > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents_events::events::UpdateListener > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ievents_events::events::GetDataGraphsFromEventBase > ();
}
}   // namespace libs::ievents_events::events
