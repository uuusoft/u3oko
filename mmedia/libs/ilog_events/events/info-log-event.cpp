/**
\file       info-log-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "info-log-event.hpp"

namespace libs::ilog_events::events
{
InfoLogEvent::InfoLogEvent (
  const Acessor&,
  const AppllPartLogInfo& appl,
  const std::string&      info) :

  info_ (info),
  appl_ (appl)
{
  time_          = boost::posix_time::microsec_clock::universal_time ();
  property_name_ = gen_get_mid ();
}


const AppllPartLogInfo&
InfoLogEvent::get_appl_info () const
{
  return appl_;
}


void
InfoLogEvent::change_appl_info (const AppllPartLogInfo& appl, const std::string& info)
{
  info_ = info;
  appl_ = appl;
}


std::string
InfoLogEvent::text (const LogTexts& type) const
{
  switch (type)
  {
  case LogTexts::subsys:
    return appl_.subsys_;
  case LogTexts::text:
    return info_;
  case LogTexts::function:
    return appl_.func_;
  case LogTexts::file:
    return appl_.file_;
  case LogTexts::line:
    return std::to_string (appl_.line_);
  case LogTexts::level:
    return to_string (appl_.msg_state_);
  case LogTexts::unknown:
    U3_ASSERT_NT (0, "???");
    return "?od";
  }
  return "?od";
}


void
InfoLogEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
InfoLogEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


::libs::events::IEvent::ptr
InfoLogEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< InfoLogEvent > (this, deep);
}


void
InfoLogEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< InfoLogEvent > (src);
  super::copy_int (src);

  appl_ = dsrc->appl_;
  info_ = dsrc->info_;
  time_ = dsrc->time_;
}


template< class Archive >
void
InfoLogEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoilog_eventsoeventsoBaseLogEvent", super);
  arh& BOOST_SERIALIZATION_NVP (appl_);
  arh& BOOST_SERIALIZATION_NVP (info_);
  arh& BOOST_SERIALIZATION_NVP (time_);

  self_correct ();
}
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::InfoLogEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::events::InfoLogEvent);
