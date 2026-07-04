/**
\file       property-log-module-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../events-base-includes_int.hpp"
#include "property-log-module-event.hpp"

namespace libs::events_base::props::modules::log::consts
{
const PropertyLogModuleEvent::bounds_type bounds_max_cache_events (0, 16 * 1024);                    //<
const PropertyLogModuleEvent::bounds_type bounds_ms_max_period_flush_events (0, 15 * 60 * 1000);     //<
const PropertyLogModuleEvent::bounds_type bounds_max_size_one_log_file_byte (0, 10 * 1024 * 1024);   //<
}   // namespace libs::events_base::props::modules::log::consts


namespace libs::events_base::props::modules::log
{
PropertyLogModuleEvent::PropertyLogModuleEvent (const Acessor& pha)
{
  vals_[LogVals::max_cache_events]              = 0;
  vals_[LogVals::ms_max_period_flush_events]    = 60 * 1000;
  vals_[LogVals::max_size_one_log_file_byte]    = 1024 * 1024;
  vals_[LogVals::enable_store_call_place]       = 0;
  vals_[LogVals::enable_log_events]             = 0;
  vals_[LogVals::enable_suppress_duplicate_msg] = 1;
  vals_[LogVals::log_level]                     = static_cast< std::uint32_t > (libs::events_base::props::modules::log::LogLevels::info);
}


auto
PropertyLogModuleEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return PropertyLogModuleEvent::gen_get_mid ();
}


auto
PropertyLogModuleEvent::get_val (const LogVals& key) const -> PropertyLogModuleEvent::value_type
{
  return vals_[key];
}


void
PropertyLogModuleEvent::set_val (const LogVals& key, value_type val)
{
  vals_[key] = val;
}


auto
PropertyLogModuleEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< PropertyLogModuleEvent > (this, deep);
}


static const LogVals g_json_vals[] = {
  LogVals::enable_log_events,
  LogVals::max_cache_events,
  LogVals::ms_max_period_flush_events,
  LogVals::max_size_one_log_file_byte,
  LogVals::enable_store_call_place,
  LogVals::enable_log_events,
  LogVals::log_level,
  LogVals::enable_suppress_duplicate_msg
};

void
PropertyLogModuleEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  for (const auto& val : g_json_vals)
  {
    vals_[val] = ::libs::utility::json::get_uint32 (obj.at (val2str (val)));
  }
}


void
PropertyLogModuleEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  for (const auto& val : g_json_vals)
  {
    obj[val2str (val)] = U3_CAST_UINT32 (vals_[val]);
  }
}


void
PropertyLogModuleEvent::correct ()
{
  static const std::pair< LogVals, const PropertyLogModuleEvent::bounds_type* > ids[] = {
    { LogVals::max_cache_events, &consts::bounds_max_cache_events },
    { LogVals::ms_max_period_flush_events, &consts::bounds_ms_max_period_flush_events },
    { LogVals::max_size_one_log_file_byte, &consts::bounds_max_size_one_log_file_byte }
  };

  for (const auto& id : ids)
  {
    auto val        = vals_[id.first];
    val             = ::libs::utility::utils::ret_check_bound< PropertyLogModuleEvent::value_type > (val, id.second->first, id.second->second);
    vals_[id.first] = val;
  }
}


void
PropertyLogModuleEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< PropertyLogModuleEvent > (src);
  super::copy_int (src);
  vals_ = dsrc->vals_;
}


template< class Archive >
void
PropertyLogModuleEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (vals_);
  self_correct ();
}
}   // namespace libs::events_base::props::modules::log

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::modules::log::PropertyLogModuleEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::modules::log::PropertyLogModuleEvent);
