/**
\file       change-node-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_media
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "change-node-data-event.hpp"

namespace libs::events_media::events
{
ChangeNodeDataEvent::ChangeNodeDataEvent (
  const Acessor&            ph,
  const GraphNodeActions&   action,
  const id_graph_type&      id_graph,
  const id_node_graph_type& id_node,
  events_list_type          events) :
  BaseNodesDataEvent (BaseNodesDataEvent::Acessor (0), id_graph),
  action_ (action),
  id_node_ (id_node),
  events_ (std::move (events))
{
}


auto
ChangeNodeDataEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ChangeNodeDataEvent::gen_get_mid ();
}


auto
ChangeNodeDataEvent::get_node () const -> const ChangeNodeDataEvent::id_node_graph_type&
{
  return id_node_;
}


void
ChangeNodeDataEvent::set_node (const id_node_graph_type& node)
{
  id_node_ = node;
}


auto
ChangeNodeDataEvent::get_action () const -> GraphNodeActions
{
  return action_;
}


void
ChangeNodeDataEvent::set_action (const GraphNodeActions& action)
{
  action_ = action;
}


auto
ChangeNodeDataEvent::get_events () const -> const ChangeNodeDataEvent::events_list_type&
{
  return events_;
}


void
ChangeNodeDataEvent::set_events (const ChangeNodeDataEvent::events_list_type& events)
{
  events_ = events;
}


auto
ChangeNodeDataEvent::check () const -> bool
{
  return !super::check () || !id_node_.check () ? false : true;
}


auto
ChangeNodeDataEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ChangeNodeDataEvent > (this, deep);
}


void
ChangeNodeDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  events_.clear ();

  id_node_ = ::boost::json::value_to< id_node_graph_type > (obj.at ("id_node"));
  action_  = ::libs::events_media::events::change_node_graph_action_from_raw_value (::libs::utility::json::get_uint32 (obj.at ("graph_node_actions")));
  // events_  = ::boost::json::value_to< events_list_type > (obj.at ("events"));

  if (obj.at ("events").is_array ())
  {
    auto& events = obj.at ("events").as_array ();
    for (const auto& event : events)
    {
      const auto ievent = event.at ("event_id").as_string ();
      const auto jevent = event.at ("event_info").as_string ();
      const auto oevent = ::libs::iproperties::helpers::get_pure_event_int (ievent.c_str ());
      if (oevent)
      {
        oevent->load_json (jevent.c_str ());
        events_.push_back (oevent);
      }
    }
  }
}


void
ChangeNodeDataEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["id_node"]            = ::boost::json::value_from (id_node_);
  obj["graph_node_actions"] = U3_CAST_UINT32_FORCE (action_);

  auto& events = obj["events"].emplace_array ();
  for (const auto& event : events_)
  {
    const auto jevent = event->save_json ();
    const auto ievent = event->get_mid ();
    events.push_back ({ { "event_id", ievent }, { "event_info", jevent } });
  }
}


void
ChangeNodeDataEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ChangeNodeDataEvent > (src);
  super::copy_int (src);

  id_node_ = dsrc->id_node_;
  action_  = dsrc->action_;
  events_  = dsrc->events_;
}


template< class Archive >
void
ChangeNodeDataEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_mediaoeventsoBaseNodesDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (id_node_);
  arh& BOOST_SERIALIZATION_NVP (action_);
  arh& BOOST_SERIALIZATION_NVP (events_);

  self_correct ();
}
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::ChangeNodeDataEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::ChangeNodeDataEvent);
