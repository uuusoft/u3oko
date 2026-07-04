/**
\file       events-media-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "events-media-register_events_in_archives.hpp"

namespace libs::events_media::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_media::events::BaseDataEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_media::events::GetNodesDataEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_media::events::ChangeGraphsDataEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_media::events::ListDevicesDataEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_media::events::ListXmlFilesDataEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_media::events::BaseNodesDataEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_media::events::ChangeNodeDataEvent > ();
}
}   // namespace libs::events_media::events
