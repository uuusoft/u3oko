/**
\file       ilog-events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "ilog-events-register_events_in_archives.hpp"

namespace libs::ilog_events::events
{
struct RegisterHelper {
  void
  process () const
  {
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ilog_events::events::BaseLogEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ilog_events::events::ExceptLogEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ilog_events::events::InfoLogEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ilog_events::events::ProcessListLogsEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ilog_events::events::ProcessLogEvent > ();
    ::libs::iproperties::helpers::make_fake_obj_this_event_type< ::libs::ilog_events::events::WrapperLogEvent > ();
  }
};


void
register_events_in_archives ()
{
  static const RegisterHelper helper;
  helper.process ();
}
}   // namespace libs::ilog_events::events
