/**
\file       get-nodes-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_imdata_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "get-nodes-data-event.hpp"

namespace libs::imdata_events::events
{
GetNodesDataEvent::GetNodesDataEvent (
  const Acessor&         ph,
  const id_graph_type&   id_graph,
  const nodes_list_type& nodes) :
  BaseNodesDataEvent (BaseNodesDataEvent::Acessor (0), id_graph),
  nodes_ (nodes)
{
  property_name_ = gen_get_mid ();
}


const GetNodesDataEvent::nodes_list_type&
GetNodesDataEvent::get_nodes () const
{
  return nodes_;
}


void
GetNodesDataEvent::set_nodes (GetNodesDataEvent::nodes_list_type& nodes)
{
  std::swap (nodes_, nodes);
}


bool
GetNodesDataEvent::check () const
{
  U3_ASSERT (super::check ());
  U3_ASSERT (!nodes_.empty ());

  for (const auto& node : nodes_)
  {
    if (!node.check ())
    {
      U3_ASSERT_SIGNAL ("check node GetNodesDataEvent");
      return false;
    }
  }

  return !super::check () || nodes_.empty () ? false : true;
}


::libs::events::IEvent::ptr
GetNodesDataEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< GetNodesDataEvent > (this, deep);
}


void
GetNodesDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  nodes_.clear ();
  nodes_ = ::boost::json::value_to< nodes_list_type > (obj.at ("nodes"));
}


void
GetNodesDataEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["nodes"] = ::boost::json::value_from (nodes_);
}


void
GetNodesDataEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< GetNodesDataEvent > (src);
  super::copy_int (src);
  nodes_ = dsrc->nodes_;
}


template< class Archive >
void
GetNodesDataEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoimdata_eventsoeventsoBaseNodesDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (nodes_);

  self_correct ();
}
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::GetNodesDataEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::GetNodesDataEvent);
