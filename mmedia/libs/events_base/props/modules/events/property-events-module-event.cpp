/**
\file       property-events-module-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../events-base-includes_int.hpp"
#include "property-events-module-event.hpp"

namespace libs::events_base::props::modules::events
{
PropertyEventsModuleEvent::PropertyEventsModuleEvent (const Acessor& pha)
{
  vals_[EventsVals::max_count_events]  = 0;
  vals_[EventsVals::max_size_database] = 512;
}


auto
PropertyEventsModuleEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return PropertyEventsModuleEvent::gen_get_mid ();
}


auto
PropertyEventsModuleEvent::get_val (const EventsVals& key) const -> PropertyEventsModuleEvent::value_type
{
  return vals_[key];
}


void
PropertyEventsModuleEvent::set_val (const EventsVals& key, value_type val)
{
  vals_[key] = val;
}


auto
PropertyEventsModuleEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< PropertyEventsModuleEvent > (this, deep);
}


void
PropertyEventsModuleEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "PropertyEventsModuleEvent::load_json_int:: wtf???");
}


void
PropertyEventsModuleEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "PropertyEventsModuleEvent::save_json_int:: wtf???");
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
void
PropertyEventsModuleEvent::correct ()
{
  static const std::pair< EventsVals, const PropertyEventsModuleEvent::bounds_type* > ids[] = {
    { EventsVals::max_cache_events, &consts::bounds_max_cache_events },
    { EventsVals::ms_max_period_flush_events, &consts::bounds_ms_max_period_flush_events },
    { EventsVals::max_size_one_log_file_byte, &consts::bounds_max_size_one_log_file_byte }
  };

  for (const auto& id : ids)
  {
    auto val = vals_.get (id.first);
    val      = ::libs::utility::utils::ret_check_bound< PropertyEventsModuleEvent::value_type > (val, id.second->first, id.second->second);
    vals_.set (id.first, val);
  }
}
#endif

void
PropertyEventsModuleEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< PropertyEventsModuleEvent > (src);
  super::copy_int (src);
  vals_ = dsrc->vals_;
}


template< class Archive >
void
PropertyEventsModuleEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (vals_);
  self_correct ();
}
}   // namespace libs::events_base::props::modules::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::modules::events::PropertyEventsModuleEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::modules::events::PropertyEventsModuleEvent);
