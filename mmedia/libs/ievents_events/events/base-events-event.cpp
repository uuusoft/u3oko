/**
\file       base-events-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../ievents-events-includes_int.hpp"
#include "base-events-event.hpp"

namespace libs::ievents_events::events
{
BaseEventsEvent::BaseEventsEvent (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
BaseEventsEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BaseEventsEvent > (this, deep);
}


void
BaseEventsEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
}


void
BaseEventsEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
}


void
BaseEventsEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BaseEventsEvent > (src);
  super::copy_int (src);
}


template< class Archive >
void
BaseEventsEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoTimedEvent", super);

  self_correct ();
}
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::BaseEventsEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents_events::events::BaseEventsEvent);
