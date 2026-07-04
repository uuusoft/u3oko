/**
\file       events-storage-register-events-archives.cpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-storage-includes_int.hpp"
#include "events-storage-register-events-archives.hpp"

namespace libs::events_storage::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::BaseStorageEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::WrapperStorageEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::MemResourceStorageEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::GetRuntimeInfo > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::GetObjects > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::GetStatisticInfo > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::ReadData > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::WriteData > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_storage::events::UpdateStream > ();
}
}   // namespace libs::events_storage::events
