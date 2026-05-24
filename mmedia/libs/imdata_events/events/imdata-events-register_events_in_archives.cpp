/**
\file       imdata-events-events2archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "imdata-events-register_events_in_archives.hpp"

namespace libs::imdata_events::events
{
void
register_events_in_archives ()
{
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::BaseDataEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::GetNodesDataEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::ChangeGraphsDataEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::ListDevicesDataEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::ListXmlFilesDataEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::BaseNodesDataEvent);
  U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::imdata_events::events::ChangeNodeDataEvent);
}
}   // namespace libs::imdata_events::events
