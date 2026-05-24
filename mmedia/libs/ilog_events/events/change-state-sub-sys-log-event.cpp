/**
\file       change-state-sub-sys-log-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "change-state-sub-sys-log-event.hpp"

namespace libs::ilog_events::events
{
ChangDShowRunsSubSysLogEvent::ChangDShowRunsSubSysLogEvent (const Acessor&) :
  InfoLogEvent (
    InfoLogEvent::Acessor (0),
    AppllPartLogInfo (
      ::libs::ievents::props::modules::log::LogLevels::info,
      "x1x",
      ::libs::helpers::log::get_module_version ()),
    "x2x"),
  start_ (true)
{
  property_name_ = gen_get_mid ();
}


ChangDShowRunsSubSysLogEvent::ChangDShowRunsSubSysLogEvent (
  const Acessor&,
  const AppllPartLogInfo& appl,
  bool                    start) :
  InfoLogEvent (InfoLogEvent::Acessor (0), appl, "x5x"),
  start_ (start)
{
  property_name_ = gen_get_mid ();
}


std::string
ChangDShowRunsSubSysLogEvent::text (const LogTexts& type) const
{
  switch (type)
  {
  case LogTexts::subsys:
    return appl_.subsys_;
  case LogTexts::text:
    return std::string (start_ ? "start subsystem" : "stop subsystem") + " " + appl_.version_;
  case LogTexts::function:
    return appl_.func_;
  case LogTexts::file:
    return appl_.file_;
  case LogTexts::line:
    return std::to_string (appl_.line_);
  case LogTexts::level:
    return to_string (appl_.msg_state_);
  case LogTexts::unknown:
    return "tlt_unknown";
  }
  return "???tlt???";
}


bool
ChangDShowRunsSubSysLogEvent::is_start () const
{
  return start_;
}


void
ChangDShowRunsSubSysLogEvent::set_start (bool val)
{
  start_ = val;
}


::libs::events::IEvent::ptr
ChangDShowRunsSubSysLogEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ChangDShowRunsSubSysLogEvent > (this, deep);
}


void
ChangDShowRunsSubSysLogEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (ChangDShowRunsSubSysLogEvent);
  super::copy_int (src);
  start_ = dsrc->start_;
}


template< class Archive >
void
ChangDShowRunsSubSysLogEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoilog_eventsoeventsoInfoLogEvent", super);
  ar& BOOST_SERIALIZATION_NVP (start_);

  self_correct ();
}
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent);
