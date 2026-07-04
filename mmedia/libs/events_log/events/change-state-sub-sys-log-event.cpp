/**
\file       change-state-sub-sys-log-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "change-state-sub-sys-log-event.hpp"

namespace libs::events_log::events
{
ChangeStateSubSysLogEvent::ChangeStateSubSysLogEvent (const Acessor&) :
  InfoLogEvent (
    InfoLogEvent::Acessor (0),
    AppllPartLogInfo (
      ::libs::events_base::props::modules::log::LogLevels::info,
      "x1x",
      ::libs::utility::log::get_module_version ()),
    "x2x"),
  start_ (true)
{
}


ChangeStateSubSysLogEvent::ChangeStateSubSysLogEvent (
  const Acessor&,
  const AppllPartLogInfo& appl,
  bool                    start) :
  InfoLogEvent (InfoLogEvent::Acessor (0), appl, "x5x"),
  start_ (start)
{
}


auto
ChangeStateSubSysLogEvent::text (const LogTexts& type) const -> std::string
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


auto
ChangeStateSubSysLogEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ChangeStateSubSysLogEvent::gen_get_mid ();
}


auto
ChangeStateSubSysLogEvent::is_start () const -> bool
{
  return start_;
}


void
ChangeStateSubSysLogEvent::set_start (bool val)
{
  start_ = val;
}


auto
ChangeStateSubSysLogEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ChangeStateSubSysLogEvent > (this, deep);
}


void
ChangeStateSubSysLogEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ChangeStateSubSysLogEvent > (src);
  super::copy_int (src);
  start_ = dsrc->start_;
}


template< class Archive >
void
ChangeStateSubSysLogEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_logoeventsoInfoLogEvent", super);
  arh& BOOST_SERIALIZATION_NVP (start_);

  self_correct ();
}
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_log::events::ChangeStateSubSysLogEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_log::events::ChangeStateSubSysLogEvent);
