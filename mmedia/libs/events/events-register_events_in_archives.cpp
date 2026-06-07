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
  // libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::events::IEvent > ();
  libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::events::IAnswerEvent > ();
  libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::events::IRequestEvent > ();
  libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::events::ISeqEvent > ();
  libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::events::ISyncEvent > ();
  libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::events::IWrapBaseEvent > ();
}
}   // namespace libs::events
