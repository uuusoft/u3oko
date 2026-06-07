/**
\file       get-events-from-base.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       09.09.2018
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../ievents-events-includes_int.hpp"
#include "get-events-from-base.hpp"

namespace libs::ievents_events::events
{
GetEventsFromBase::GetEventsFromBase (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


void
GetEventsFromBase::sync_event_props (
  const time_period_type&       time_period,
  const id_graphs_storage_type& data_graph_ids,
  const hids_storage_type&      event_types,
  const events_res_type&        events_from_database,
  const std::string&            sql_request)
{
  time_period_          = time_period;
  data_graph_ids_       = data_graph_ids;
  event_types_          = event_types;
  events_from_database_ = events_from_database;
  sql_request_          = sql_request;
}


void
GetEventsFromBase::set_data_graphs (id_graphs_storage_type& data_graphs)
{
  data_graph_ids_.swap (data_graphs);
}


const GetEventsFromBase::id_graphs_storage_type&
GetEventsFromBase::get_data_graphs () const
{
  return data_graph_ids_;
}


void
GetEventsFromBase::set_events (events_res_type& events)
{
  events_from_database_.swap (events);
}


const GetEventsFromBase::events_res_type&
GetEventsFromBase::get_events () const
{
  return events_from_database_;
}


void
GetEventsFromBase::set_types (hids_storage_type& types)
{
  event_types_.swap (types);
}


const GetEventsFromBase::hids_storage_type&
GetEventsFromBase::get_types () const
{
  return event_types_;
}


void
GetEventsFromBase::set_request (std::string& sql_request)
{
  sql_request_ = sql_request;
}


const std::string&
GetEventsFromBase::get_request () const
{
  return sql_request_;
}


::libs::events::IEvent::ptr
GetEventsFromBase::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< GetEventsFromBase > (this, deep);
}


void
GetEventsFromBase::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  time_period_    = ::boost::json::value_to< time_period_type > (obj.at ("time_period"));
  data_graph_ids_ = ::boost::json::value_to< id_graphs_storage_type > (obj.at ("data_graph_ids"));
  event_types_    = ::boost::json::value_to< hids_storage_type > (obj.at ("event_types"));
}


void
GetEventsFromBase::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["time_period"]    = ::boost::json::value_from (time_period_);
  obj["data_graph_ids"] = ::boost::json::value_from (data_graph_ids_);
  obj["event_types"]    = ::boost::json::value_from (event_types_);

#ifdef U3_FAKE_DISABLE
  events_res_type events_from_database_;   //<
#endif
}


void
GetEventsFromBase::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GetEventsFromBase > (src);
  super::copy_int (src);

  events_from_database_ = dsrc->events_from_database_;
  event_types_          = dsrc->event_types_;
  data_graph_ids_       = dsrc->data_graph_ids_;
}


template< class Archive >
void
GetEventsFromBase::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("BaseEventsEvent", super);
  arh& BOOST_SERIALIZATION_NVP (events_from_database_);
  arh& BOOST_SERIALIZATION_NVP (event_types_);
  arh& BOOST_SERIALIZATION_NVP (data_graph_ids_);

  self_correct ();
}
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::GetEventsFromBase);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents_events::events::GetEventsFromBase);
