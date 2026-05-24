/**
\file       get-data-graphs-from-event-base.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       05.06.2022
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../ievents-events-includes_int.hpp"
#include "get-data-graphs-from-event-base.hpp"

namespace libs::ievents_events::events
{
GetDataGraphsFromEventBase::GetDataGraphsFromEventBase (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


GetDataGraphsFromEventBase::~GetDataGraphsFromEventBase ()
{
}


void
GetDataGraphsFromEventBase::set_data_graphs (id_graphs_storage_type&& data_graphs)
{
  data_graph_ids_ = data_graphs;
}


const GetDataGraphsFromEventBase::id_graphs_storage_type&
GetDataGraphsFromEventBase::get_data_graphs () const
{
  return data_graph_ids_;
}


::libs::events::IEvent::ptr
GetDataGraphsFromEventBase::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< GetDataGraphsFromEventBase > (this, deep);
}


void
GetDataGraphsFromEventBase::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "???");
}


void
GetDataGraphsFromEventBase::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["data_graph_ids"] = ::boost::json::value_from (data_graph_ids_);
}


void
GetDataGraphsFromEventBase::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (GetDataGraphsFromEventBase);
  super::copy_int (src);
  data_graph_ids_ = dsrc->data_graph_ids_;
}


template< class Archive >
void
GetDataGraphsFromEventBase::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("BaseEventsEvent", super);
  ar& BOOST_SERIALIZATION_NVP (data_graph_ids_);

  self_correct ();
}
}   // namespace libs::ievents_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents_events::events::GetDataGraphsFromEventBase);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents_events::events::GetDataGraphsFromEventBase);
