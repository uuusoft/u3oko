/**
\file       property-log-module-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../includes_int.hpp"
#include "property-log-module-event.hpp"

namespace libs::ievents::props::modules::log::consts
{
const PropertyLogModuleEvent::bounds_type bounds_max_cache_events (0, 16 * 1024);                    //<
const PropertyLogModuleEvent::bounds_type bounds_ms_max_period_flush_events (0, 15 * 60 * 1000);     //<
const PropertyLogModuleEvent::bounds_type bounds_max_size_one_log_file_byte (0, 10 * 1024 * 1024);   //<
}   // namespace libs::ievents::props::modules::log::consts


namespace libs::ievents::props::modules::log
{
PropertyLogModuleEvent::PropertyLogModuleEvent (const Acessor& ph)
{
  property_name_ = gen_get_mid ();

  vals_[LogVals::max_cache_events]              = 0;
  vals_[LogVals::ms_max_period_flush_events]    = 60 * 1000;
  vals_[LogVals::max_size_one_log_file_byte]    = 1024 * 1024;
  vals_[LogVals::enable_store_call_place]       = 0;
  vals_[LogVals::enable_log_events]             = 0;
  vals_[LogVals::enable_suppress_duplicate_msg] = 1;
  vals_[LogVals::log_level]                     = static_cast< std::uint32_t > (libs::ievents::props::modules::log::LogLevels::info);
}


PropertyLogModuleEvent::~PropertyLogModuleEvent ()
{
}


PropertyLogModuleEvent::value_type
PropertyLogModuleEvent::get_val (const LogVals& key) const
{
  return vals_[key];
}


void
PropertyLogModuleEvent::set_val (const LogVals& key, value_type val)
{
  vals_[key] = val;
}


::libs::events::IEvent::ptr
PropertyLogModuleEvent::clone_int (const ::libs::events::Deeps& deep) const
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
    vals_[val] = ::libs::helpers::json::get_uint32 (obj.at (val2str (val)));
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
    val             = ::libs::helpers::utils::ret_check_bound< PropertyLogModuleEvent::value_type > (val, id.second->first, id.second->second);
    vals_[id.first] = val;
  }
}


void
PropertyLogModuleEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (PropertyLogModuleEvent);
  super::copy_int (src);
  vals_ = dsrc->vals_;
}


template< class Archive >
void
PropertyLogModuleEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (vals_);
  self_correct ();
}
}   // namespace libs::ievents::props::modules::log

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::modules::log::PropertyLogModuleEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::modules::log::PropertyLogModuleEvent);
