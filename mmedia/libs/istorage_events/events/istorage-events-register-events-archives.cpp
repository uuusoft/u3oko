/**
\file       istorage-events-register-events-archives.cpp
\date       21.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::BaseStorageEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::WrapperStorageEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::MemResourceStorageEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::GetRuntimeInfo);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::GetObjects);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::GetStatisticInfo);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::ReadData);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::WriteData);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::istorage_events::events::UpdateStream);
}
}   // namespace libs::istorage_events::events
