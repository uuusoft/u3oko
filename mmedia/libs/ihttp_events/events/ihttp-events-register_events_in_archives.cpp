/**
\file       ihttp-events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ihttp_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "ihttp-events-register_events_in_archives.hpp"

namespace libs::ihttp_events::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ihttp_events::events::BaseHttpEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ihttp_events::events::WrapperHttpEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ihttp_events::events::MemResourceHttpEvent > ();
}
}   // namespace libs::ihttp_events::events
