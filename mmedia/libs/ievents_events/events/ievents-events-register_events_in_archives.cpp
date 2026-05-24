/**
\file       ievents-events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents_events::events::BaseEventsEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents_events::events::WrapperEventsEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents_events::events::AddEvent2Base);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents_events::events::GetEventsFromBase);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents_events::events::UpdateListener);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ievents_events::events::GetDataGraphsFromEventBase);
}
}   // namespace libs::ievents_events::events
