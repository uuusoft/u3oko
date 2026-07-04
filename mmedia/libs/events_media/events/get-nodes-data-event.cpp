/**
\file       get-nodes-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "get-nodes-data-event.hpp"

namespace libs::events_media::events
{
GetNodesDataEvent::GetNodesDataEvent (
  const Acessor&       ph,
  const id_graph_type& id_graph,
  nodes_list_type      nodes) :
  BaseNodesDataEvent (BaseNodesDataEvent::Acessor (0), id_graph),
  nodes_ (std::move (nodes))
{
}


auto
GetNodesDataEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return GetNodesDataEvent::gen_get_mid ();
}


auto
GetNodesDataEvent::get_nodes () const -> const GetNodesDataEvent::nodes_list_type&
{
  return nodes_;
}


void
GetNodesDataEvent::set_nodes (GetNodesDataEvent::nodes_list_type& nodes)
{
  std::swap (nodes_, nodes);
}


auto
GetNodesDataEvent::check () const -> bool
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


auto
GetNodesDataEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_mediaoeventsoBaseNodesDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (nodes_);

  self_correct ();
}
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::GetNodesDataEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::GetNodesDataEvent);
