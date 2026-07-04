/**
\file       change-graphs-data-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_media
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "change-graphs-data-event.hpp"

namespace libs::events_media::events
{
ChangeGraphsDataEvent::ChangeGraphsDataEvent (
  const Acessor&         ph,
  const GraphActions&    action,
  id_graphs_storage_type folders) :
  action_ (action),
  folders_ (std::move (folders))
{
}


auto
ChangeGraphsDataEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ChangeGraphsDataEvent::gen_get_mid ();
}


auto
ChangeGraphsDataEvent::get_graph_folders () const -> const ChangeGraphsDataEvent::id_graphs_storage_type&
{
  return folders_;
}


void
ChangeGraphsDataEvent::set_graph_folders (ChangeGraphsDataEvent::id_graphs_storage_type& folders)
{
  std::swap (folders_, folders);
}


auto
ChangeGraphsDataEvent::get_action () const -> GraphActions
{
  return action_;
}


void
ChangeGraphsDataEvent::set_action (const GraphActions& action)
{
  action_ = action;
}


auto
ChangeGraphsDataEvent::check () const -> bool
{
  U3_ASSERT (!folders_.empty ());
  return !folders_.empty ();
}


auto
ChangeGraphsDataEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ChangeGraphsDataEvent > (this, deep);
}


void
ChangeGraphsDataEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  action_  = change_graph_action_from_raw_val (::libs::utility::json::get_uint32 (obj.at ("graph_actions")));
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
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_mediaoeventsoBaseDataEvent", super);
  arh& BOOST_SERIALIZATION_NVP (folders_);
  arh& BOOST_SERIALIZATION_NVP (action_);

  self_correct ();
}
}   // namespace libs::events_media::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_media::events::ChangeGraphsDataEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_media::events::ChangeGraphsDataEvent);
