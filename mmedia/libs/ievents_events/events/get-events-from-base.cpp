/**
\file       get-events-from-base.cpp
\author     Erashov Anton erashov2026@proton.me
\date       09.09.2018
\project    u3_ievents_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../ievents-events-includes_int.hpp"
#include "get-events-from-base.hpp"

namespace libs::ievents_events::events
{
GetEventsFromBase::GetEventsFromBase (const Acessor& pha) :
  request_params_ ({ { "id", 0 }, { "sql", "SELECT *" } })
{
  property_name_ = gen_get_mid ();
}

auto
GetEventsFromBase::sync_event_props (const request_params_type& request_params, const database_events_type& events_from_database) -> void
{
  request_params_  = request_params;
  database_events_ = events_from_database;
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
auto
GetEventsFromBase::set_data_graphs (id_graphs_storage_type& data_graphs) -> void
{
  data_graph_ids_.swap (data_graphs);
}


auto
GetEventsFromBase::get_data_graphs () const -> const GetEventsFromBase::id_graphs_storage_type&
{
  return data_graph_ids_;
}


auto
GetEventsFromBase::set_types (hids_storage_type& types) -> void
{
  event_types_.swap (types);
}


auto
GetEventsFromBase::get_types () const -> const GetEventsFromBase::hids_storage_type&
{
  return event_types_;
}
#endif

auto
GetEventsFromBase::set_request (request_params_type& request_params) -> void
{
  request_params_ = request_params;
}


auto
GetEventsFromBase::get_request () const -> const request_params_type&
{
  return request_params_;
}


auto
GetEventsFromBase::set_events (database_events_type& events) -> void
{
  database_events_.swap (events);
}


auto
GetEventsFromBase::get_events () const -> const GetEventsFromBase::database_events_type&
{
  return database_events_;
}


auto
GetEventsFromBase::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< GetEventsFromBase > (this, deep);
}


auto
GetEventsFromBase::load_json_int (const ::boost::json::object& obj) -> void
{
  super::load_json_int (obj);
  // time_period_    = ::boost::json::value_to< time_period_type > (obj.at ("time_period"));
  // data_graph_ids_ = ::boost::json::value_to< id_graphs_storage_type > (obj.at ("data_graph_ids"));
  // event_types_    = ::boost::json::value_to< hids_storage_type > (obj.at ("event_types"));
  request_params_ = ::boost::json::parse (obj.at ("request_params").as_string ());
}


auto
GetEventsFromBase::save_json_int (::boost::json::object& obj) const -> void
{
  super::save_json_int (obj);
  // obj["time_period"]    = ::boost::json::value_from (time_period_);
  // obj["data_graph_ids"] = ::boost::json::value_from (data_graph_ids_);
  // obj["event_types"]    = ::boost::json::value_from (event_types_);
  obj["request_params"] = ::boost::json::serialize (request_params_);
}


auto
GetEventsFromBase::copy_int (const IEvent::craw_ptr src) -> void
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GetEventsFromBase > (src);
  super::copy_int (src);
  // event_types_     = dsrc->event_types_;
  // data_graph_ids_  = dsrc->data_graph_ids_;
  request_params_  = dsrc->request_params_;
  database_events_ = dsrc->database_events_;
}


template< class Archive >
void
GetEventsFromBase::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  U3_XLOG_DBG ("GetEventsFromBase::serialize->")
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("BaseEventsEvent", super);
  // arh& BOOST_SERIALIZATION_NVP (event_types_);
  // arh& BOOST_SERIALIZATION_NVP (data_graph_ids_);
  arh& BOOST_SERIALIZATION_NVP (request_params_);
  arh& BOOST_SERIALIZATION_NVP (database_events_);

  self_correct ();
  U3_XLOG_DBG ("GetEventsFromBase::serialize<-")
}
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::GetEventsFromBase);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents_events::events::GetEventsFromBase);
