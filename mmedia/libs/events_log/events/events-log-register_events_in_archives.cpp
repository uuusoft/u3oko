/**
\file       events-log-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "events-log-register_events_in_archives.hpp"

namespace libs::events_log::events
{
void
register_events_in_archives ()
{
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_log::events::BaseLogEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_log::events::ChangeStateSubSysLogEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_log::events::ExceptLogEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_log::events::InfoLogEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_log::events::ProcessListLogsEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_log::events::ProcessLogEvent > ();
  ::libs::iproperties::helpers::make_stub_obj< ::libs::events_log::events::WrapperLogEvent > ();
}
}   // namespace libs::events_log::events
