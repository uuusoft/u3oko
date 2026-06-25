/**
\file       istorage-events-register-events-archives.cpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "istorage-events-register-events-archives.hpp"

namespace libs::istorage_events::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::BaseStorageEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::WrapperStorageEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::MemResourceStorageEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::GetRuntimeInfo > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::GetObjects > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::GetStatisticInfo > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::ReadData > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::WriteData > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::istorage_events::events::UpdateStream > ();
}
}   // namespace libs::istorage_events::events
