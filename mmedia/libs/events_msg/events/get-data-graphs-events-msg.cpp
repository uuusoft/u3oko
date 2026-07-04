/**
\file       get-data-graphs-events-msg.cpp
\author     Erashov Anton erashov2026@proton.me
\date       05.06.2022
\project    u3_events_base_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-msg-includes_int.hpp"
#include "get-data-graphs-events-msg.hpp"

namespace libs::events_msg::events
{
GetDataGraphsEventsMsg::GetDataGraphsEventsMsg (const Acessor& pha)
{
}


GetDataGraphsEventsMsg::~GetDataGraphsEventsMsg () = default;


auto
GetDataGraphsEventsMsg::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return GetDataGraphsEventsMsg::gen_get_mid ();
}


void
GetDataGraphsEventsMsg::set_data_graphs (id_graphs_storage_type&& data_graphs)
{
  data_graph_ids_ = data_graphs;
}


auto
GetDataGraphsEventsMsg::get_data_graphs () const -> const GetDataGraphsEventsMsg::id_graphs_storage_type&
{
  return data_graph_ids_;
}


auto
GetDataGraphsEventsMsg::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< GetDataGraphsEventsMsg > (this, deep);
}


void
GetDataGraphsEventsMsg::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "GetDataGraphsEventsMsg::load_json_int:: wtf???");
}


void
GetDataGraphsEventsMsg::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  obj["data_graph_ids"] = ::boost::json::value_from (data_graph_ids_);
}


void
GetDataGraphsEventsMsg::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GetDataGraphsEventsMsg > (src);
  super::copy_int (src);
  data_graph_ids_ = dsrc->data_graph_ids_;
}


template< class Archive >
void
GetDataGraphsEventsMsg::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("BaseEventsMsg", super);
  arh& BOOST_SERIALIZATION_NVP (data_graph_ids_);

  self_correct ();
}
}   // namespace libs::events_msg::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_msg::events::GetDataGraphsEventsMsg);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_msg::events::GetDataGraphsEventsMsg);
