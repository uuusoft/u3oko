/**
\file       events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "events-register_events_in_archives.hpp"

namespace libs::events
{
void
register_events_in_archives ()
{
  // U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::events::IEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::events::IAnswerEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::events::IRequestEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::events::ISeqEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::events::ISyncEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::events::IWrapBaseEvent);
}
}   // namespace libs::events
