/**
\file       ilog-events-register_events_in_archives.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    uuu_ilog_events
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
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ilog_events::events::BaseLogEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ilog_events::events::ExceptLogEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ilog_events::events::InfoLogEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ilog_events::events::ProcessListLogsEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ilog_events::events::ProcessLogEvent);
    U3_MAKE_FAKE_EVENT_OBJ_THIS_TYPE (::libs::ilog_events::events::WrapperLogEvent);
  }
};


void
register_events_in_archives ()
{
  static const RegisterHelper helper;
  helper.process ();
}
}   // namespace libs::ilog_events::events
