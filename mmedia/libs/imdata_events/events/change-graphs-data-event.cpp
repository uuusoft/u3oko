/**
\file       change-graphs-data-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_imdata_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "change-graphs-data-event.hpp"

namespace libs::imdata_events::events
{
ChangeGraphsDataEvent::ChangeGraphsDataEvent (
  const Acessor&                ph,
  const GraphActions&           action,
  const id_graphs_storage_type& folders) :
  action_ (action),
  folders_ (folders)
{
  property_name_ = gen_get_mid ();
}


const ChangeGraphsDataEvent::id_graphs_storage_type&
ChangeGraphsDataEvent::get_graph_folders () const
{
  return folders_;
}


void
ChangeGraphsDataEvent::set_graph_folders (ChangeGraphsDataEvent::id_graphs_storage_type& folders)
{
  std::swap (folders_, folders);
}


GraphActions
ChangeGraphsDataEvent::get_action () const
{
  return action_;
}


void
ChangeGraphsDataEvent::set_action (const GraphActions& action)
{
  action_ = action;
}


bool
ChangeGraphsDataEvent::check () const
{
  U3_ASSERT (!folders_.empty ());
  return !folders_.empty ();
}


::libs::events::IEvent::ptr
ChangeGraphsDataEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< ChangeGraphsDataEvent > (this, deep);
}


void
ChangeGraphsDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  action_  = change_graph_action_from_raw_val (::libs::helpers::json::get_uint32 (obj.at ("graph_actions")));
  folders_ = ::boost::json::value_to< ChangeGraphsDataEvent::id_graphs_storage_type > (obj.at ("folders"));
}


void
ChangeGraphsDataEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["graph_actions"] = U3_CAST_UINT32_FORCE (action_);
  obj["folders"]       = ::boost::json::value_from (folders_);
}


void
ChangeGraphsDataEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ChangeGraphsDataEvent > (src);
  super::copy_int (src);

  folders_ = dsrc->folders_;
  action_  = dsrc->action_;
}


template< class Archive >
void
ChangeGraphsDataEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoimdata_eventsoeventsoBaseDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (folders_);
  arh& BOOST_SERIALIZATION_NVP (action_);

  self_correct ();
}
}   // namespace libs::imdata_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::imdata_events::events::ChangeGraphsDataEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::imdata_events::events::ChangeGraphsDataEvent);
