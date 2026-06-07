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
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::imdata_events::events::BaseDataEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::imdata_events::events::GetNodesDataEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::imdata_events::events::ChangeGraphsDataEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::imdata_events::events::ListDevicesDataEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::imdata_events::events::ListXmlFilesDataEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::imdata_events::events::BaseNodesDataEvent > ();
  ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::imdata_events::events::ChangeNodeDataEvent > ();
}
}   // namespace libs::imdata_events::events
