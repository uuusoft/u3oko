/**
\file       wrapper-events-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../ievents-events-includes_int.hpp"
#include "wrapper-events-event.hpp"

namespace libs::ievents_events::events
{
WrapperEventsEvent::WrapperEventsEvent (const Acessor& pha, ::libs::events::IEvent::ptr msg) :
  int_ (msg)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
WrapperEventsEvent::get_msg () const
{
  return int_;
}


void
WrapperEventsEvent::set_msg (::libs::events::IEvent::ptr& msg)
{
  int_ = msg;
}


::libs::events::IEvent::ptr
WrapperEventsEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< WrapperEventsEvent > (this, deep);
}


void
WrapperEventsEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
}


void
WrapperEventsEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
}


void
WrapperEventsEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< WrapperEventsEvent > (src);
  super::copy_int (src);
  int_ = dsrc->int_;
}


template< class Archive >
void
WrapperEventsEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoTimedEvent", super);
  arh& BOOST_SERIALIZATION_NVP (int_);

  self_correct ();
}
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::WrapperEventsEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents_events::events::WrapperEventsEvent);
